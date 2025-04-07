#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "struct.h"
#include "package.h"
#pragma warning (disable:4996)
struct package* phead;
struct package* pp;
struct package* ptmp;
struct message* mhead;
struct message* mtmp;
extern struct account* ahead;
int idx = 1;
int hash[1000000];
void package_print();
void account_management();
void package_management();
void package_in();
void package_out();
void account_print();
void print_messages_chronological();
struct account* loadaccountfromfile();
void alarm();
void savemessagetofile(struct message* mhead);
extern char* assign_position_code(struct package* pkg, enum user_type user_type);
void administrator_main_menu()
{
    delete_package_time(&phead);
    struct package* pkg = (Package*)malloc(sizeof(Package));
    int choice_administrator = 0;
    int flag_error = 0;
    int abnormal_indicator = 0;//0表示无异常，1表示有货架已满
    do {
        if (flag_error == 0) {
            system("cls");
            //char* code = assign_position_code(pkg, student);
            printf("\n\n\n\n\n\n\n\n\n");
            printf("\t\t==============================================\n");
            printf("\t\t              菜鸟驿站管理员主界面              \n");
            printf("\t\t              1---账号管理                     \n");
            printf("\t\t              2---包裹管理                     \n");
            printf("\t\t              3---用户反馈                     \n");
            printf("\t\t              0---退出                         \n");
            printf("\t\t==============================================\n");
            printf("请输入选项前的序号: ");
        }
        else {
            //char* code = assign_position_code(pkg, student);
            printf("\n\n\n\n\n\n\n\n\n");
            printf("\t\t==============================================\n");
            printf("\t\t              菜鸟驿站管理员主界面              \n");
            printf("\t\t              1---账号管理                     \n");
            printf("\t\t              2---包裹管理                     \n");
            printf("\t\t              3---用户反馈                     \n");
            printf("\t\t              0---退出                         \n");
            printf("\t\t==============================================\n");
            printf("请输入正确的序号: ");
        }

        scanf("%d", &choice_administrator);
        system("cls");

        switch (choice_administrator) {
        case 1: account_management(); break; //账号管理功能
        case 2: package_management(); break;  //包裹管理功能
        case 3: print_messages_chronological(); break;
        case 0: exit(0);
        default: flag_error = 1;
        }
        system("cls");
    } while (choice_administrator == 0 || flag_error == 1);
}
void alarm(int abnormal_indicator)
{
    if (abnormal_indicator == 1)
    {
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t==============================================\n");
        printf("\t\t                                              \n");
        printf("\t\t                                              \n");
        printf("\t\t                货架已满，请及时处理             \n");
        printf("\t\t                                              \n");
        printf("\t\t                                              \n");
        printf("\t\t                                              \n");
        printf("\t\t==============================================\n");
        printf("\t\t-----^-^-----------------------------^-^------\n");
        printf("按enter键返回管理员主页");
        printf("\n");
        printf("按p进入包裹管理\n");
        char choice;
        while (1)
        {
            choice = getchar();
            if (choice == '\n') {
                system("cls");
                administrator_main_menu();
                break;
            }
            else if (choice == 'p') {
                system("cls");
                package_management();
                break;
            }
        }
    }
    else
    {
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t==============================================\n");
        printf("\t\t                                              \n");
        printf("\t\t                                              \n");
        printf("\t\t                暂无异常情况                   \n");
        printf("\t\t                                              \n");
        printf("\t\t                                              \n");
        printf("\t\t                                              \n");
        printf("\t\t==============================================\n");
        printf("\t\t-----^-^-----------------------------^-^------\n");
        printf("按enter键返回");
        char choice;
        while (1)
        {
            choice = getchar();
            if (choice == '\n') {
                system("cls");
                administrator_main_menu();
                break;
            }
        }
    }
}


// 正向打印（从新到旧）
void print_messages_chronological() {
    struct message* current = mhead;
    int count = 1;
    int choice = 3;
    printf("按1返回");
    printf("\n====== 消息列表（最新在前）======\n");
    while (current) {
        char timeprintf[20];
        struct tm time;
        localtime_s(&time, &current->time);
        strftime(timeprintf, sizeof(timeprintf), "%Y-%m-%d %H:%M:%S", &time);
        printf("[%s]", timeprintf);

        printf("@%s\n   %s\n", current->user_name, current->note);
        current = current->next;
        count++;
    }
    printf("======== 共%d条消息 ========\n", count - 1);
    scanf("%d", &choice);
    while (1)
    {
        if (choice == 1)break;
    }
    administrator_main_menu();
}

void account_management()
{
    int flag_error = 0;
do {
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\t\t==============================================\n");
    printf("\t\t              账号管理界面                     \n");
    printf("\t\t              1---查看账号                     \n");
    printf("\t\t              2---账号禁用                     \n");
    printf("\t\t              3---账号解禁                     \n");
    printf("\t\t              0---返回                         \n");
    printf("\t\t                                              \n");
    printf("\t\t==============================================\n");
    printf("请输入选项前的序号: ");
    int choice_account_management;
    if(scanf("%d", &choice_account_management) != 1) {
        // 清空输入缓冲区
        while (getchar() != '\n');
		system("cls");
        printf("无效输入，请输入一个有效的数字。\n");
        flag_error = 1;
        continue;
    }
    char target[51];
    switch (choice_account_management) {
    case 1:
        account_print();
        break;
    case 2:
        printf("请输入要禁用的用户名: ");
        scanf("%50s", target);
        disable_account(target);
        break;
    case 3:
        printf("请输入要解禁的用户名: ");
        scanf("%50s", target);
        enable_account(target);
        break;
    case 0: administrator_main_menu(); break;
	default: flag_error = 1;
		system("cls");
    }
} while (flag_error == 1);
}
void account_print()
{
    struct account* current = loadaccountfromfile(); // 加载账户链表
    if (current == NULL) {
        printf("当前没有注册账户！\n");
        return;
    }

    // 用户类型映射表
    const char* user_type_str[] = {
         "0","商家", "学生", "残障人士", "教职工", "居民"
    };
    system("cls");
    printf("\n%-20s %-12s %-15s %-12s %-8s\n",
        "用户名", "用户类型", "电话号码", "密码", "状态");
    printf("---------------------------------------------------------------------\n");

    while (current != NULL) {
        // 转换状态为可读字符串
        const char* state_str = current->state ? "启用" : "禁用";

        printf("%-20s %-12s %-15s %-12s %-8s\n",
            current->user_name,
            user_type_str[current->type], // 直接通过枚举值索引
            current->phone_number,
            current->password,
            state_str);

        current = current->next;
    }
    printf("---------------------------------------------------------------------\n");
    printf("输入回车结束,输入esc返回:");
    while (1) {
        char c = getch();
        if (c == 13) { // Enter 键的ASCII码是13
            break;
        }
        else if (c == 27) { // Esc 键的ASCII码是27
            system("cls");
            account_management();
        }
        else {
			system("cls");
			struct account* current = loadaccountfromfile(); // 加载账户链表
            printf("\n%-20s %-12s %-15s %-12s %-8s\n",
                "用户名", "用户类型", "电话号码", "密码", "状态");
            printf("---------------------------------------------------------------------\n");

            while (current != NULL) {
                // 转换状态为可读字符串
                const char* state_str = current->state ? "启用" : "禁用";

                printf("%-20s %-12s %-15s %-12s %-8s\n",
                    current->user_name,
                    user_type_str[current->type], // 直接通过枚举值索引
                    current->phone_number,
                    current->password,
                    state_str);

                current = current->next;
            }
            printf("---------------------------------------------------------------------\n");
            printf("无效输入！输入回车结束,输入esc返回:\n");
        }
    }
}



// 禁用账号函数（返回1成功，0用户不存在）
int disable_account(const char* target_username)
{
    struct account* current = loadaccountfromfile(); // 加载最新数据
    int found_flag = 0;

    // 遍历链表查找用户
    while (current != NULL) {
        if (strcmp(current->user_name, target_username) == 0) {
            if (current->state == false) {
                printf("账号 [%s] 已经是禁用状态！\n", target_username);
            }
            else {
                current->state = false; // 设置为禁用
                saveaccounttofile(current); // 保存修改
                printf("账号 [%s] 已禁用！\n", target_username);
            }
            found_flag = 1;
            break;
        }
        current = current->next;
    }

    if (!found_flag) {
        printf("错误：用户名 [%s] 不存在！\n", target_username);
    }
    printf("输入回车结束,输入esc返回:");
    while (1) {
        char c = getch();
        if (c == 13) { // Enter 键的ASCII码是13
            break;
        }
        else if (c == 27) { // Esc 键的ASCII码是27
            system("cls");
            account_management();
        }
        else {
			system("cls");
            printf("无效输入！输入回车结束, 输入esc返回:""\n");
        }
    }
}

// 解禁账号函数（返回1成功，0用户不存在）
int enable_account(const char* target_username)
{
    struct account* current = loadaccountfromfile(); // 加载最新数据
    int found_flag = 0;

    // 遍历链表查找用户
    while (current != NULL) {
        if (strcmp(current->user_name, target_username) == 0) {
            if (current->state == true) {
                printf("账号 [%s] 已经是启用状态！\n", target_username);
            }
            else {
                current->state = true; // 设置为启用
                saveaccounttofile(current); // 保存修改
                printf("账号 [%s] 已解禁！\n", target_username);
            }
            found_flag = 1;
            break;
        }
        current = current->next;
    }

    if (!found_flag) {
        printf("错误：用户名 [%s] 不存在！\n", target_username);
    }
    printf("输入回车结束,输入esc返回:");
    while (1) {
        char c = getch();
        if (c == 13) { // Enter 键的ASCII码是13
            break;
        }
        else if (c == 27) { // Esc 键的ASCII码是27
            system("cls");
            account_management();
        }
        else {
			system("cls");
            printf("无效输入！请输入回车结束,输入esc返回:\n");
        }
    }
}


void package_management()
{
    int flag_error = 0;
    do {
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t==============================================\n");
        printf("\t\t              包裹管理界面                     \n");
        printf("\t\t              1---包裹列表                     \n");
        printf("\t\t              2---入库                        \n");
        printf("\t\t              3---出库                        \n");
        printf("\t\t              0---返回                        \n");
        printf("\t\t                                              \n");
        printf("\t\t==============================================\n");
        printf("请输入选项前的序号: ");
        int choice_package_management = 5;
        scanf("%d", &choice_package_management);
        while (choice_package_management != 1 && choice_package_management != 2 && choice_package_management != 3&& choice_package_management!=0) {
            printf("输入错误，请重新输入\n");
            getchar(); scanf("%d", &choice_package_management);



        }
        switch (choice_package_management) {
        case 1: package_print(); break;
        case 2: package_in(); break;
        case 3: package_out(); break;
        case 0: administrator_main_menu();
        default: flag_error = 1;
        }
        system("cls");
    } while (flag_error == 1);
}

void package_print()
{
    print_all_packages(phead);
    int c = 0;
    printf("输入回车结束,输入esc返回:");
    while (1) {
        char c = getch();
        if (c == 13) { // Enter 键的ASCII码是13
            break;
        }
        else if (c == 27) { // Esc 键的ASCII码是27
            system("cls");
            package_management();
        }
        else {
            printf("无效输入！请重新输入！\n");
        }

    }

}
long rnumber()
{
    srand(time(NULL));
    long rnum = rand();
    while (hash[rnum] != 0) {
        rnum = rnum * (rnum + 11) % 11 + rnum;
    }
    return rnum;

}
void package_in()
{
    pp = (struct package*)malloc(sizeof(struct package));
    int ff = 1;
    getchar();
    while (ff) {
        system("cls");

        int flag = 1;
        char user_name_package_p[60];
        while (flag) {
            if (ff > 1) {
                printf("\n\n\n\n\n\n\n\n\n");
                printf("用户名不存在，请重新输入: ");
            }
            else {
                if (flag > 1) {

                }
                else
                {
                    printf("\n\n\n\n\n\n\n\n\n");
                    printf("请输入包裹的用户名: ");
                }
            }
            fgets(user_name_package_p, 60, stdin);
            user_name_package_p[strcspn(user_name_package_p, "\n")] = '\0';
            if (strlen(user_name_package_p) > 50)
            {
                while (getchar() != '\n');
                flag++;
            }
            else {
                strcpy(pp->user_name, user_name_package_p);
                flag = 0;
                struct account* current = ahead;
                while (current != NULL) {
                    if (strcmp(current->user_name, pp->user_name) == 0) break;
                    current = current->next;
                }
                if (current != NULL) {
                    system("cls");
                    char* code = assign_position_code(pp, current->type);
                    if (code == NULL) {
                        printf("\n\n\n\n\n\n\n\n\n");
                        printf("\t\t==============================================\n");
                        printf("\t\t                                              \n");
                        printf("\t\t                                              \n");
                        printf("\t\t                 货架已满                      \n");
                        printf("\t\t                                              \n");
                        printf("\t\t               按enter键返回                   \n");
                        printf("\t\t                                              \n");
                        printf("\t\t                                              \n");
                        printf("\t\t                                              \n");
                        printf("\t\t==============================================\n");
                        getchar();
                        char ch = '0';
                        while (ch != '\n') {
                            ch = getchar();

                        }
                        break;
                     }
                        
                    strcpy(pp->position_code, code);
                    ff = 0;
                    free(code);
                }
                else {
                    ff++;
                }
            }
            system("cls");
        }

    }


    int pchoice = 0;
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\t\t==============================================\n");
    printf("\t\t             请选择入库包裹尺寸                 \n");
    printf("\t\t                1---较小                      \n");
    printf("\t\t                2---中等                      \n");
    printf("\t\t                3---较大                      \n");
    printf("\t\t                                              \n");
    printf("\t\t                0---返回                       \n");
    printf("\t\t==============================================\n");
    printf("请输入选项前的序号: ");
    while (1) {
        scanf("%d", &pchoice);
        if (pchoice != 1 && pchoice != 2 && pchoice != 3) {
            if (pchoice != 0);
            else {
                system("cls");
                administrator_main_menu();
            }
        }
        else
        {
            if (phead == NULL)
            {

                pp->category.size = pchoice-1;
                pp->id = idx++;
                phead = pp;
                ptmp = pp;
                pp->pnext = NULL;

            }
            else
            {

                pp->category.size = pchoice-1;
                ptmp->pnext = pp;
                ptmp = pp;
                pp->pnext = NULL;
            }
            break;
        }
    }
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\t\t==============================================\n");
    printf("\t\t               特殊包裹类型                    \n");
    printf("\t\t               是否为易碎品                    \n");
    printf("\t\t                1---是                        \n");
    printf("\t\t                2---否                        \n");
    printf("\t\t                                              \n");
    printf("\t\t                0---返回                      \n");
    printf("\t\t==============================================\n");
    printf("请输入选项前的序号: ");
    while (1) {
        scanf("%d", &pchoice);
        if (pchoice != 1 && pchoice != 2) {
            if (pchoice != 0);
            else
            {
                system("cls");
                administrator_main_menu();
            }

        }

        else
        {
            pp->category.delicacy = pchoice;
            break;
        }
    }

     

    pp->category.urgency = 0;
    pp->category.insurance = 0;
    pp->category.weight = 5;
    pp->state = storage;
    pp->pickup_code = random_code(phead, ahead);
    pp->id = pp->pickup_code;
    pp->take_time = -1;
    char ch;
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\t\t==============================================\n");
    printf("\t\t                                              \n");
    printf("\t\t                                              \n");
    printf("\t\t                   成功入库                    \n");
    printf("\t\t                                              \n");
    printf("\t\t                 按enter键返回                \n");
    printf("\t\t                                              \n");
    printf("\t\t==============================================\n");
    getchar();
    while (1) {
        ch = getchar();
        if (ch == '\n') {

            break;
        }

    }
    system("cls");
    administrator_main_menu();
    return;
}
void package_out()
{
    int flag = 0;
    long code;
    while (flag != 1) {
        if (flag == 0) {
            system("cls");
            printf("\n\n\n\n\n\n\n\n\n");
            printf("\t\t==============================================\n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t                请输入包裹取件码               \n");
            printf("\t\t                                              \n");
            printf("\t\t                  0---返回                     \n");
            printf("\t\t                                              \n");
            printf("\t\t==============================================\n");
        }
        else if (flag == 2 || flag == 3) {
            system("cls");
            printf("\n\n\n\n\n\n\n\n\n");
            printf("\t\t==============================================\n");
            printf("\t\t                                              \n");
            printf("\t\t                  取件码错误                   \n");
            printf("\t\t              请再次输入包裹取件码              \n");
            printf("\t\t                                              \n");
            printf("\t\t                  0---返回                     \n");
            printf("\t\t                                              \n");
            printf("\t\t==============================================\n");
        }
        else if (flag == 4)
        {
            system("cls");
            printf("\n\n\n\n\n\n\n\n\n");
            printf("\t\t==============================================\n");
            printf("\t\t                                              \n");
            printf("\t\t                 此包裹不在库中。。。         \n");
            printf("\t\t              如果需要请再次输入包裹取件码     \n");
            printf("\t\t                                              \n");
            printf("\t\t                  按0---返回                   \n");
            printf("\t\t                                              \n");
            printf("\t\t==============================================\n");

        }
        int res;
        do {
            res = scanf("%ld", &code);
            if (res != 1) {
                while (getchar() != '\n');
                printf("无效输入！请重新输入！\n");
            }
        } while (res != 1);
        if (code == 0)break;
        if (code % 9999 != 0)
        {
            struct package* package = NULL;
            package = find_package_by_package_id(phead, code);
            if (package != NULL && (package->state == 1 || package->state == 6)) {
                if (package) {
                    bool flag_d = 0;
                    flag_d = 1;
                    package->state = 2;
                    package->take_time = time(NULL);
                    save_to_file(phead);
                    if (flag_d == 1)
                    {
                        char choice;
                        system("cls");
                        printf("\n\n\n\n\n\n\n\n\n");
                        printf("\t\t==============================================\n");
                        printf("\t\t                                              \n");
                        printf("\t\t                  包裹出库成功                 \n");
                        printf("\t\t                  按enter键返回                \n");
                        printf("\t\t                                              \n");
                        printf("\t\t                                              \n");
                        printf("\t\t                   0---退出                   \n");
                        printf("\t\t==============================================\n");
                        flag = 1;
                        getchar();
                        while (1)
                        {
                            choice = getchar();
                            if (choice == '\n')break;
                            else if (choice == '0')exit(0);

                        }
                    }
                    else {
                        printf("删除失败\n");
                    }

                }
                else { flag = 2; }
            }
            else {
                flag = 4;
                continue;
            }
        }
        else {
            flag = 3;
        }

    }

    administrator_main_menu();

}