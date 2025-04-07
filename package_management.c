#include "package.h"
#include "billing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#pragma warning(disable:4996)
extern struct account* ptmp;
extern struct package* phead;
char* assign_position_code(struct package* pkg, enum user_type user_type);
// 创建包裹节点
Package* create_package(long id, char position_code[51], Pack_category category, long pickup_code, const char* user_name, PackageStatus status, time_t take_time) {
    Package* new_pkg = (Package*)malloc(sizeof(Package));
    if (!new_pkg) {
        fprintf(stderr, "错误：内存分配失败\n");
        return NULL;
    }
    new_pkg->id = id;
    strncpy(new_pkg->position_code, position_code, 50);
    new_pkg->position_code[50] = '\0'; // 防止溢出
    new_pkg->category = category;
    new_pkg->pickup_code = pickup_code;
    strncpy(new_pkg->user_name, user_name, 50);
    new_pkg->user_name[50] = '\0';
    new_pkg->state = status;
    new_pkg->take_time = take_time;
    new_pkg->pnext = NULL;
    return new_pkg;
}




// 添加包裹到链表尾部
void add_package(Package** phead, Package* new_pkg) {
    if (*phead == NULL) {
        *phead = new_pkg;
    }
    else if (new_pkg != *phead) {
        Package* current = *phead;
        while (current->pnext != NULL) {
            current = current->pnext;
        }
        current->pnext = new_pkg;
    }

}





// 根据ID删除包裹（返回是否成功）
bool delete_package(Package** phead, long id) {
    Package* prev = NULL, * current = *phead;
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->pnext;
    }
    if (current == NULL) {
        fprintf(stderr, "错误：未找到包裹 %ld\n", id);
        return false;
    }
    if (prev == NULL) {
        *phead = current->pnext; // 删除头节点
    }
    else {
        prev->pnext = current->pnext; // 删除中间或尾节点
    }
    save_to_file(*phead);
    free(current);
    return true;
}




// 根据ID查找包裹
Package* find_package_by_package_id(Package* phead, long id) {
    Package* current = phead;
    while (current != NULL) {
        if (current->id == id) return current;
        current = current->pnext;
    }
    return NULL;
}




// 根据取件码查找包裹
Package* find_package_by_pickup_code(Package* phead, long pickup_code) {
    Package* current = phead;
    while (current != NULL) {
        if (current->pickup_code == pickup_code) return current;
        current = current->pnext;
    }
    return NULL;
}

// 根据用户名查找包裹
/*
Package* find_package(Package* phead, char* user_name) {
    Package* current = phead;
    while (current != NULL) {
        if (strcmp(current->user_name, user_name)) return current;
        current = current->pnext;
    }
    return NULL;
}*/




// 根据驿站货架查找包裹       
Package** find_packages_by_package_shelf(Package* phead, const char* position_shelf, int* count) {
    Package* current = phead;
    int n = 0;
    while (current != NULL) {
        char package_shelf[3];
        strncpy(package_shelf, current->position_code, 1);
        package_shelf[1] = '\0';
        if (strcmp(package_shelf, position_shelf) == 0) {
            n++;
        }
        current = current->pnext;
    }
    if (n == 0) {
        *count = 0;
        return NULL;
    }
    Package** packages = (Package**)malloc(n * sizeof(Package*));
    if (!packages) {
        fprintf(stderr, "分配指针数组内存失败\n");
        return NULL;
    }
    current = phead;
    n = 0;
    while (current != NULL) {
        char package_shelf[3];
        strncpy(package_shelf, current->position_code, 1);
        package_shelf[1] = '\0';
        if (strcmp(package_shelf, position_shelf) == 0) {
            packages[n++] = current;
        }
        current = current->pnext;
    }
    *count = n;
    return packages;
}




// 根据包裹状态查找包裹
Package** find_packages_by_package_state(Package* phead, PackageStatus state, int* found_count) {
    int count = 0;
    Package* current = phead;

    // 第一遍遍历链表，统计匹配的包裹数量
    while (current != NULL) {
        if (current->state == state) {
            count++;
        }
        current = current->pnext;
    }

    if (found_count) {
        *found_count = count;
    }

    if (count == 0) {
        return NULL;
    }

    // 动态分配一个指针数组，数组大小为count
    Package** packages_array = (Package**)malloc(count * sizeof(Package*));
    if (packages_array == NULL) {
        perror("分配包裹指针数组内存失败");
        return NULL;
    }

    // 第二遍遍历链表，将匹配的包裹地址存入数组
    current = phead;
    int index = 0;
    while (current != NULL) {
        if (current->state == state) {
            packages_array[index++] = current;
        }
        current = current->pnext;
    }

    return packages_array;
}




// 保存链表数据到文件
void save_to_file(Package* phead) {
    FILE* file = fopen("package.txt", "w");
    if (!file) {
        perror("错误：文件打开失败");
        return;
    }
    Package* current = phead;
    while (current != NULL) {
        fprintf(file, "%ld %s %d %d %d %f %d %ld %s %d %lld\n",
            current->id,
            current->position_code,
            current->category.size,
            current->category.delicacy,
            current->category.urgency,
            current->category.weight,
            current->category.insurance,
            current->pickup_code,
            current->user_name,
            current->state,
            current->take_time);
        current = current->pnext;
    }
    fclose(file);
}




// 从文件加载数据到链表
void load_from_file() {
    phead = NULL;
    FILE* file = fopen("package.txt", "r");
    if (!file) {
        perror("错误：文件打开失败");
        return;
    }
    long id, pickup_code;
    char position_code[5], user_name[51];
    Pack_category category;
    int size, state;
    time_t take_time;
    while (fscanf(file, "%ld %s %d %d %d %f %d %ld %s %d %lld\n",
        &id,
        position_code,
        &size,
        &category.delicacy,
        &category.urgency,
        &category.weight,
        &category.insurance,
        &pickup_code,
        user_name,
        &state,
        &take_time) == 11) {
        category.size = (enum size)size;
        Package* pkg = NULL;
        if (phead == NULL)
        {
            phead = create_package(id, position_code, category, pickup_code, user_name, (PackageStatus)state, take_time);
            pkg = phead;
        }
        else {
            pkg = create_package(id, position_code, category, pickup_code, user_name, (PackageStatus)state, take_time);
        }
        add_package(&phead, pkg);
        ptmp = pkg;
    }
    fclose(file);
}



// 管理员 打印单个包裹信息
void print_package_for_administrator(Package* pkg) {
    if (!pkg) {
        printf("错误：包裹不存在\n");
        return;
    }
    const char* size_str[] = { "小件", "中件", "大件" };
    const char* state_str[] = { "在途（用户）", "在库", "已取件", "退回", "误领", "丢失","损坏","在途（其他）" };
    printf("--------------------\n");
    printf("包裹ID: %ld\n", pkg->id);
    printf("驿站位置: %s\n", pkg->position_code);
    printf("用户ID: %s\n", pkg->user_name);
    printf("取件码: %ld\n", pkg->pickup_code);
    printf("尺寸: %s | 重量: %.2fkg\n", size_str[pkg->category.size], pkg->category.weight);
    printf("易碎: %s \n", pkg->category.delicacy ? "是" : "否");
    printf("状态: %s\n", state_str[pkg->state]);
    printf("--------------------\n");
}


// 用户 打印单个包裹信息
void print_package_for_user(Package* pkg) {
    if (!pkg) {
        printf("错误：包裹不存在\n");
        return;
    }
    const char* size_str[] = { "小件", "中件", "大件" };
    const char* state_str[] = { "在途（用户）", "在库", "已取件", "退回", "误领", "丢失","损坏","在途（其他）" };
    printf("--------------------\n");
    printf("包裹ID: %ld\n", pkg->id);
    printf("驿站位置: %s\n", pkg->position_code);
    printf("取件码: %ld\n", pkg->pickup_code);
    printf("状态: %s\n", state_str[pkg->state]);
    printf("--------------------\n");


}

// 打印所有包裹
void print_all_packages(Package* phead) {
    Package* current = phead;

    if (!current) {
        printf("包裹列表为空\n");
        return;
    }
    printf("======= 所有包裹 =======\n");
    while (current != NULL) {
        print_package_for_administrator(current);
        current = current->pnext;
    }
    printf("=======================\n");
}

void store_package(Package* phead, struct account* user) {
    Package* new_pkg = (Package*)malloc(sizeof(Package));
    strcpy(new_pkg->user_name, user->user_name);
    printf("请输入包裹重量(kg)：");
    scanf("%f", &new_pkg->category.weight);

    printf("请输入包裹尺寸（1-小件，2-中件，3-大件）：");
    int size;
    do {
        scanf("%d", &size);
        if (size < 1 || size > 3) {
            printf("输入错误，请重新输入（1-3）：");
        }
    } while (size < 1 || size > 3);

    new_pkg->category.size = size - 1;
    new_pkg->category.delicacy = 0;
    new_pkg->category.urgency = 0;
    new_pkg->category.insurance = 0;
    new_pkg->state = storage;
    new_pkg->take_time = -1;

    char position_code[5];
    char* code = assign_position_code(new_pkg, user->type);
    if (code == NULL) {

    }
    else {
        strcpy(position_code, code);
        if (position_code) {
            strcpy(new_pkg->position_code, position_code);
        }
        else {
            printf("驿站已满，请稍后再试\n");
            printf("按enter键继续");
            getchar();
            if (getchar() == '\n')system("cls");
            user_home(user->user_name);
        }

        new_pkg->pickup_code = random_code(phead, user);
        new_pkg->id = new_pkg->pickup_code;
        new_pkg->pnext = NULL;
        load_from_file(&phead);
        add_package(&phead, new_pkg);
        save_to_file(phead);
        printf("包裹已存贮\n");
    }
    free(code);
    printf("按enter键继续");
    getchar();
    if (getchar() == '\n')system("cls");
    user_home(user->user_name);
}

void send_package(Package* phead, struct account* user) {
    Package* new_pkg = (Package*)malloc(sizeof(Package));
    strcpy(new_pkg->user_name, user->user_name);
    int right = 0;
    printf("请输入包裹重量(kg)：");
    scanf("%f", &new_pkg->category.weight);
    printf("请输入包裹尺寸（1-小件，2-中件，3-大件）：");
    int size;
    do {
        scanf("%d", &size);
        if (size < 1 || size > 3) {
            printf("输入错误，请重新输入（1-3）：");
        }
    } while (size < 1 || size > 3);
    new_pkg->category.size = size - 1;

    printf("是否易碎（1-是，0-否）：");
    int delicacy;
    while (right == 0) {
        scanf("%d", &delicacy);
        if (delicacy == 1 || delicacy == 0) {
            right = 1;
        }
        else {
            printf("输入错误，请重新输入：");
        }
    }
    right = 0;
    new_pkg->category.delicacy = delicacy;
    printf("是否加急（1-是，0-否）：");
    int urgency;
    while (right == 0) {
        scanf("%d", &urgency);
        if (urgency == 1 || urgency == 0) {
            right = 1;
        }
        else {
            printf("输入错误，请重新输入：");
        }
    }
    right = 0;
    new_pkg->category.urgency = urgency;
    printf("是否保险（1-是，0-否）：");
    int insurance;
    while (right == 0) {
        scanf("%d", &insurance);
        if (insurance == 1 || insurance == 0) {
            right = 1;
        }
        else {
            printf("输入错误，请重新输入：");
        }
    }
    right = 0;
    new_pkg->category.insurance = insurance;
    new_pkg->state = wayto_others;
    strcpy(new_pkg->position_code, "Z001");
    new_pkg->pickup_code = random_code(phead, user);
    new_pkg->id = new_pkg->pickup_code;
    new_pkg->pnext = NULL;
    new_pkg->take_time = -1;
    printf("请输入目的地：");
    getchar();
    while (getchar() != '\n') {
        continue;
    }

    add_package(&phead, new_pkg);
    save_to_file(phead);
    float fee = total_fee(&new_pkg->category, user->type);
    printf("\n包裹已发送\n");
    printf("费用：%.2f元\n", fee);
    printf("按enter键继续");
    if (getchar() == '\n')system("cls");
    user_home(user->user_name);
}

void send_more_package(Package* phead, struct account* user) {
    printf("请问您要邮寄几种包裹：");
    int sort = 0;
    int count = 0;
    scanf("%d", &sort);

    // 校验输入合法性
    if (sort <= 0 || sort > 999) {
        printf("错误：包裹种类数过多\n");
        return;
    }

    // 动态分配内存避免越界
    int* specific = (int*)malloc(sort * sizeof(int));
    float* total_specific_fee_for_one_sort = (float*)calloc(sort, sizeof(float)); // 自动初始化为0

    printf("请分别输入各种包裹要寄送多少份、重量、尺寸、急迫、保险和目的地：\n");

    for (int i = 0; i < sort; i++) {
        printf("第%d种包裹数量：", i + 1);
        scanf("%d", &specific[i]);

        // 校验单种包裹数量
        if (specific[i] <= 0 || specific[i] > 999) {
            printf("错误：单种包裹数量过多\n");
            free(specific);
            free(total_specific_fee_for_one_sort);
            return;
        }

        // 动态分配单种包裹费用数组
        float* specific_fee_for_one_sort = (float*)malloc(specific[i] * sizeof(float));

        printf("请输入第%d种包裹重量(kg)：", i + 1);
        float weight1[999];
        scanf("%f", &weight1[i]);
        printf("请输入第%d种包裹尺寸（1-小件，2-中件，3-大件）：", i + 1);
        int size[999];
        int right = 0;
        while (right == 0) {
            scanf("%d", &size[i]);
            if (size[i] == 1 || size[i] == 2 || size[i] == 3) {
                right = 1;
            }
            else {
                printf("输入错误，请重新输入：");
            }
        }
        right = 0;
        printf("第%d种包裹是否易碎（1-是，0-否）：", i + 1);
        int delicacy[999];
        while (right == 0) {
            scanf("%d", &delicacy[i]);
            if (delicacy[i] == 1 || delicacy[i] == 0) {
                right = 1;
            }
            else {
                printf("输入错误，请重新输入：");
            }
        }
        right = 0;
        printf("第%d种包裹是否加急（1-是，0-否）：", i + 1);
        int urgency[999];
        while (right == 0) {
            scanf("%d", &urgency[i]);
            if (urgency[i] == 1 || urgency[i] == 0) {
                right = 1;
            }
            else {
                printf("输入错误，请重新输入：");
            }
        }
        right = 0;
        printf("第%d种包裹是否保险（1-是，0-否）：", i + 1);
        int insurance[999];
        while (right == 0) {
            scanf("%d", &insurance[i]);
            if (insurance[i] == 1 || insurance[i] == 0) {
                right = 1;
            }
            else {
                printf("输入错误，请重新输入：");
            }
        }
        right = 0;
        printf("请输入目的地：");
        getchar();
        while (getchar() != '\n') {
            continue;
        }
        for (int i1 = 0; i1 < specific[i]; i1++) {
            Package* new_pkg = (Package*)malloc(sizeof(Package));
            strcpy(new_pkg->user_name, user->user_name);
            new_pkg->category.weight = weight1[i];
            new_pkg->category.size = size[i] - 1;
            new_pkg->category.delicacy = delicacy[i];
            new_pkg->category.urgency = urgency[i];
            new_pkg->take_time = -1;
            new_pkg->category.insurance = insurance[i];
            new_pkg->state = wayto_others;
            strcpy(new_pkg->position_code, "Z001");
            new_pkg->pickup_code = random_code(phead, user);
            new_pkg->id = new_pkg->pickup_code;
            new_pkg->pnext = NULL;
            add_package(&phead, new_pkg);
            save_to_file(phead);
            // 计算单包裹费用
            specific_fee_for_one_sort[i1] = total_fee(&new_pkg->category, user->type);
            total_specific_fee_for_one_sort[i] += specific_fee_for_one_sort[i1];
            count++;
        }

        printf("共计%d份包裹已发送\n", count);
        printf("当前种类包裹总费用：%.2f元\n", total_specific_fee_for_one_sort[i]);
        free(specific_fee_for_one_sort); // 释放单种包裹费用数组

    }
    // 计算总费用
    float total_fee_for_all_sort = 0;
    for (int i = 0; i < sort; i++) {
        total_fee_for_all_sort += total_specific_fee_for_one_sort[i];
    }
    printf("所有包裹已发送\n总费用：%.2f元\n", total_fee_for_all_sort);

    // 释放内存
    free(specific);
    free(total_specific_fee_for_one_sort);

    printf("按enter键继续");
    while (getchar() != '\n'); // 等待用户按键
    system("cls");

}

//随机生成取件码
long random_code(Package* phead, struct account* ahead) {
    srand(time(NULL));
    long pickup_code;
    do {
        pickup_code = rand() % 10000;
    } while (find_package_by_pickup_code(phead, pickup_code) != NULL);
    return pickup_code;
}


// 释放链表内存
void free_package_list(Package* phead) {
    Package* tmp;
    while (phead != NULL) {
        tmp = phead;
        phead = phead->pnext;
        free(tmp);
    }
}

void delete_package_time()
{

    Package* prev = NULL, * current = phead;

    while (current != NULL)
    {
        if (current->take_time != -1) {
            struct tm timet;
            localtime_s(&timet, &current->take_time);
            // 转换为本地时间的 tm 结构体
            int year = timet.tm_year + 1900; // 年份从 1900 开始计数
            int month = timet.tm_mon + 1;    // 月份范围 0-11 → 需 +1
            int day = timet.tm_mday;         // 日期直接使用

            time_t nowtime = time(NULL);
            struct tm* timen = localtime(&nowtime);
            int nowyear = timen->tm_year + 1900; // 年份从 1900 开始计数
            int nowmonth = timen->tm_mon + 1;    // 月份范围 0-11 → 需 +1
            int nowday = timen->tm_mday;         // 日期直接使用

            int flag = -1;
            int f = -1;

            int tt = year * 365 + month * 30 + day;
            int nt = nowyear * 365 + nowmonth * 30 + nowday;
            if (nt - tt >= 60)f = 1;
            else {
                f = 0;
            }
            if (f == 1)
            {

                if (prev == NULL) {
                    phead = current->pnext; // 删除头节点
                    current = NULL;
                }
                else {
                    prev->pnext = current->pnext;
                    current = prev->pnext;
                }
                free(current);
            }
            else {
                prev = current;
                current = current->pnext;
            }
        }
        else {
            prev = current;
            current = current->pnext;
        }


    }
    save_to_file(phead);


}
//7839 Q001 1 1 0 -1.000000 0 7839 jhr 1 1711387562
/*time_t times = 1711387562;
    printf("%lld", times);
    char timeprintf[20];
    struct tm time;
    localtime_s(&time, &times);
    strftime(timeprintf, sizeof(timeprintf), "%Y-%m-%d %H:%M:%S", &time);
    printf("[%s]", timeprintf);*/