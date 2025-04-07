#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "struct.h"
#include"package.h"
#pragma warning (disable:4996)
char* encryptpassword();
extern struct account* ahead;
extern struct account* ap;
extern struct account* atmp;
extern struct package* phead;
extern struct message* mhead;
extern struct message* mtmp;
extern struct message* mp;
struct account* user;
void signlog();
void load_from_file();
extern void user_home(char user_name[51]);
void store_package(Package* phead, struct account* user);
void savemessagetofile(struct message* mhead)
{
    FILE* fp;
    fp = fopen("message.txt", "w");
    if (fp == NULL)
    {
        printf("文件打开失败\n");
        exit(1);
    }
    struct message* i = mhead;
    while (i != NULL)
    {
        fputc(',', fp);
        fprintf(fp, "%s", i->user_name);
        fputc(',', fp);
        fprintf(fp, "%s", i->note);
        fputc(',', fp);
        fprintf(fp, "%lld\n", i->time);
        i = i->next;
    }
    fclose(fp);

}
struct message* loadmessagefromfile()
{
    FILE* fp;
    fp = fopen("message.txt", "r");
    if (fp == NULL)
    {
        printf("文件打开失败\n");
        exit(0);
    }
    char line[400];
    struct message* current = NULL;
    struct message* previous = NULL;
    char user_name[51];
    char note[300];
    struct message* next;
    struct message* pre;
    time_t time;
    mhead = NULL;
    while (fgets(line, sizeof(line), fp) != NULL && line[0] == ',')
    {

        line[strcspn(line, "\n")] = '\0';
        char* pline = line + 1;
        char* first = strstr(pline, ",");
        char* second = strstr(first + 1, ",");
        strncpy(user_name, pline, first - pline);
        user_name[first - pline] = '\0';
        strncpy(note, first + 1, second - first - 1);
        note[second - first - 1] = '\0';
        sscanf(second + 1, "%lld", &time);



        current = (struct message*)malloc(sizeof(struct message));

        if (!current) {
            printf("内存分配失败");
            return;
        }

        strcpy(current->user_name, user_name);
        strcpy(current->note, note);
        current->time = time;


        if (mhead == NULL) { // 空链表情况
            current->next = NULL;
            current->pre = NULL;
            mhead = current;
        }
        else
        {
            struct message* i = mhead;
            struct message* prev = NULL;



            while (current && difftime(i->time, current->time) > 0) {
                prev = i;
                i = i->next;
                if (i == NULL)break;
            }

            if (prev == NULL) {//head
                current->next = mhead;
                current->pre = NULL;
                mhead->pre = current;
                mhead = current;
            }
            else {
                prev->next = current;
                current->pre = prev;
                current->next = i;
                if (i) {
                    i->pre = current;
                }
            }
        }

    }
    fclose(fp);
    return mhead;
}
void query_package(struct account* user, int i)//查询用户包裹
{
    load_from_file(phead);

    char* name = user->user_name;
    struct package* current = phead;
    int count = 0;
    while (current != NULL) {
        if (!strcmp(current->user_name, name))
        {
            count++;
            print_package_for_user(current);
        }
        current = current->pnext;
    }
    if (i == 1) getchar();
    printf("查询到%d个包裹\n", count);
    if (i == 1) {
        printf("按enter键返回回到用户主页...");
        if (getchar() == '\n') {
            system("cls");
            user_home(user->user_name);
        }
    }
}
void return_package(struct account* user)
{

    system("cls");
    getchar();
    int flag = 1;
    long user_package;
    while (flag) {
        system("cls");
        if (flag > 1) {
            printf("\n\n\n\n\n\n\n\n\n");
            printf("\t\t==============================================\n");
            printf("\t\t                                              \n");
            printf("\t\t                退还包裹                       \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t           请输入退还的包裹ID              \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t==============================================\n");
            printf("包裹ID错误或不存在\n");
            printf("ID: ");
        }
        else
        {
            printf("\n\n\n\n\n\n\n\n\n");
            printf("\t\t==============================================\n");
            printf("\t\t                                              \n");
            printf("\t\t                退还包裹                       \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t           请输入退还的包裹ID                  \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t==============================================\n");
            printf("ID: ");
        }
         
        scanf("%ld", &user_package);

        struct package* package_p = find_package_by_package_id(phead, user_package);
        if (package_p == NULL) {
            flag++;
            continue;
        }
        else {
            package_p->state = 3;
            flag = 0;
        }
    }
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\t\t==============================================\n");
    printf("\t\t                                              \n");
    printf("\t\t                                              \n");
    printf("\t\t               退回操作成功                    \n");
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
    save_to_file(phead);
    return;



}
void manage_account(struct account* user)
{
    int flag = 0;
    struct account* account = NULL;

    char ch;
    char password[51];


    while (1) {

        system("cls");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t==============================================\n");
        printf("\t\t                 账号管理                      \n");
        printf("\t\t                                              \n");
        printf("\t\t             按enter健修改密码                 \n");
        printf("\t\t                                              \n");
        printf("\t\t                                              \n");
        printf("\t\t                                              \n");
        printf("\t\t                0---返回                      \n");
        printf("\t\t                                              \n");
        printf("\t\t==============================================\n");
        getchar();
        ch = getchar();
        if (ch == '\n')break;
        else if (ch == '0') return;
        else {
            while (getchar() != '\n') {
                ;
            }
            system("cls");
        }
    }
    if (ch == '\n')
    {
        while (flag != 1) {
            system("cls");
            printf("\n\n\n\n\n\n\n\n\n");
            printf("\t\t==============================================\n");
            printf("\t\t                                              \n");
            printf("\t\t             请输入初始密码                    \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t==============================================\n");
            printf("请输入: ");
            int i = 0;
            char password[51];
            char ch;
            while (1) {
                ch = getch();
                if (ch == '\r') {
                    password[i] = '\0';
                    break;
                }
                else if (ch == '\b' && i > 0) {
                    i--;
                    printf("\b \b");
                }
                else if (i < 50) {
                    password[i++] = ch;
                    printf("*");
                }
                else if (i >= 50) {
                    system("cls");
                    printf("\n\n\n\n\n\n\n\n\n");
                    printf("\t\t==============================================\n");
                    printf("\t\t                                              \n");
                    printf("\t\t          密码长度超过50 请重新输入             \n");
                    printf("\t\t                                              \n");
                    printf("\t\t                                              \n");
                    printf("\t\t                                              \n");
                    printf("\t\t                                              \n");
                    printf("\t\t==============================================\n");
                    printf("请输入: ");
                    i = 0;
                }
            }
            if (strcmp(user->password, password) == 0)
            {
                flag = 1;

            }

        }
        system("cls");
        if (flag == 1)
        {
            int flag2 = 0;
            while (flag2 != 1) {
                system("cls");
                printf("\n\n\n\n\n\n\n\n\n");
                if (flag2 == 2)
                {
                    printf("两次输入的密码不一致\n");
                }

                char p1[51];
                strcpy(p1, encryptpassword(1));


                char p2[51];
                strcpy(p2, encryptpassword(2));
                if (strcmp(p1, p2) == 0)
                {
                    strcpy(user->password, p1);
                    flag2 = 1;
                }
                else {
                    flag2 = 2;
                }
                 
                saveaccounttofile(ahead);
            }
        }



    }






    system("cls");
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\t\t==============================================\n");
    printf("\t\t                                              \n");
    printf("\t\t                                              \n");
    printf("\t\t               密码修改成功                    \n");
    printf("\t\t                                              \n");
    printf("\t\t               按enter键返回                   \n");
    printf("\t\t                                              \n");
    printf("\t\t                                              \n");
    printf("\t\t                                              \n");
    printf("\t\t==============================================\n");

    getchar();
    while (ch != '\n') {
        ch = getchar();

    }
    system("cls");
    return;

}


//1就是正常留言，2就是异常反馈，3就是管理员留言，4是残障关照服务
void take_message(struct account* user, int type) {
    // 创建新节点
    struct message* mp = (struct message*)malloc(sizeof(struct message));
    if (!mp) {
        perror("内存分配失败");
        return;
    }

    // 初始化节点数据
    strncpy(mp->user_name, user->user_name, 50);
    mp->user_name[50] = '\0'; // 确保字符串终止
    mp->time = time(NULL);    // 直接获取当前时间
    if (type != 4) {
        system("cls");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t==============================================\n");
        printf("\t\t                                              \n");
        printf("\t\t                                              \n");
        printf("\t\t                                              \n");
        printf("\t\t                请输入留言内容                \n");
        printf("\t\t                                              \n");
        printf("\t\t                                              \n");
        printf("\t\t                                              \n");
        printf("\t\t                                              \n");
        printf("\t\t==============================================\n");
        printf("请输入（最多299字符）: ");
        getchar();
        fgets(mp->note, 299, stdin);
        mp->note[strcspn(mp->note, "\n")] = '\0'; // 去除换行符
    }
    else if (type == 4) {
        strcpy(mp->note, "需要残障关照服务");
        system("cls");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t==============================================\n");
        printf("\t\t                                              \n");
        printf("\t\t                                              \n");
        printf("\t\t                                              \n");
        printf("\t\t                已向驿站发出提醒              \n");
        printf("\t\t                 按entre键返回                \n");
        printf("\t\t                                              \n");
        printf("\t\t                                              \n");
        printf("\t\t                                              \n");
        printf("\t\t==============================================\n");
        getchar();
        char ch;
        while (1) {
            ch = getchar();
            if (ch == '\n')break;
        }

    }
    // 链表插入操作
    if (mhead == NULL) { // 空链表情况
        mp->next = NULL;
        mp->pre = NULL;
        mhead = mp;
    }
    else {
        struct message* current = mhead;
        struct message* prev = NULL;


        while (current && difftime(current->time, mp->time) > 0) {
            prev = current;
            current = current->next;
        }

        if (prev == NULL) {
            mp->next = mhead;
            mp->pre = NULL;
            mhead->pre = mp;
            mhead = mp;
        }
        else {
            prev->next = mp;
            mp->pre = prev;
            mp->next = current;
            if (current) {
                current->pre = mp;
            }
        }
    }
    savemessagetofile(mhead);
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\t\t==============================================\n");
    printf("\t\t                                              \n");
    printf("\t\t                                              \n");
    printf("\t\t                  留言成功                    \n");
    printf("\t\t                                              \n");
    printf("\t\t               按enter键返回                   \n");
    printf("\t\t                                              \n");
    printf("\t\t                                              \n");
    printf("\t\t                                              \n");
    printf("\t\t==============================================\n");
    char ch='0';
     
    while (ch != '\n') {
        ch = getchar();

    }
    system("cls");
     

 
    return;

}




void feedback(struct account* user)
{
    int choice;

    do {
        system("cls");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t==============================================\n");
        printf("\t\t                 异常反馈                     \n");
        printf("\t\t                                             \n");
        printf("\t\t                1---包裹丢失                  \n");
        printf("\t\t                2---包裹破损                  \n");
        printf("\t\t                3---误领包裹                  \n");
        printf("\t\t                4---用户留言                  \n");
        printf("\t\t                5---返回                      \n");
        printf("\t\t                0---退出                      \n");
        printf("\t\t==============================================\n");
        printf("请输入:");

        scanf("%d", &choice);
        while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 0) {
            printf("输入错误，请重新输入\n");
            getchar(); scanf("%d", &choice);



        }
        system("cls");

        switch (choice) {
        case 1:  package_lose_feedback(user); break;
        case 2:  package_break_feedback(user); break;
        case 3:  package_mistake(user); break;
        case 4:  take_message(user, 1); break;
        case 5:  return;
        case 0: exit(0);
        default: printf("无效输入！\n");
        }
    } while (choice != 0);

}
int package_lose_feedback(struct account* user)
{
    system("cls");
    getchar();
    int flag = 1;
    long user_package;
    while (flag) {
        system("cls");
        if (flag > 1) {
            query_package(user, 0);
            printf("\n\n\n\n\n\n\n\n\n");
            printf("\t\t==============================================\n");
            printf("\t\t                                              \n");
            printf("\t\t               包裹异常反馈                       \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t           请输入丢失的的包裹ID              \n");
            printf("\t\t                                               \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t==============================================\n");
            printf("包裹ID错误或不存在\n");
            printf("ID: ");
        }
        else
        {
            query_package(user, 0);
            printf("\n\n\n\n\n\n\n\n\n");
            printf("\t\t==============================================\n");
            printf("\t\t                                              \n");
            printf("\t\t               包裹异常反馈                       \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t            请输入丢失的包裹ID               \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t==============================================\n");
            printf("ID: ");
        }
        scanf("%ld", &user_package);

        struct package* package_p = find_package_by_package_id(phead, user_package);
        if (package_p == NULL) {
            flag++;
            continue;
        }
        else {
            package_p->state = lose;
            flag = 0;
        }
    }
    save_to_file(phead);
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\t\t==============================================\n");
    printf("\t\t                                              \n");
    printf("\t\t                                              \n");
    printf("\t\t                 反馈成功                    \n");
    printf("\t\t                                              \n");
    printf("\t\t               按enter键返回                   \n");
    printf("\t\t                                              \n");
    printf("\t\t                                              \n");
    printf("\t\t                                              \n");
    printf("\t\t==============================================\n");
    getchar();
    char ch = '\n';
    while (ch != '\n') {
        ch = getchar();

    }
    return 1;
}
int package_break_feedback(struct account* user)
{
    system("cls");
    getchar();
    int flag = 1;
    long user_package;
    while (flag) {
        system("cls");
        if (flag > 1) {
            query_package(user, 0);
            printf("\n\n\n\n\n\n\n\n\n");
            printf("\t\t==============================================\n");
            printf("\t\t                                              \n");
            printf("\t\t               包裹异常反馈                       \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t           请输入破损的的包裹ID               \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t==============================================\n");
            printf("包裹ID错误或不存在\n");
            printf("ID: ");
        }
        else
        {
            query_package(user, 0);
            printf("\n\n\n\n\n\n\n\n\n");
            printf("\t\t==============================================\n");
            printf("\t\t                                              \n");
            printf("\t\t               包裹异常反馈                       \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t            请输入破损的包裹ID              \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t==============================================\n");
            printf("ID: ");
        }
        scanf("%ld", &user_package);

        struct package* package_p = find_package_by_package_id(phead, user_package);
        if (package_p == NULL) {
            flag++;
            continue;
        }
        else {
            package_p->state = broken;
            flag = 0;
        }
    }
    save_to_file(phead);
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\t\t==============================================\n");
    printf("\t\t                                              \n");
    printf("\t\t                                              \n");
    printf("\t\t                 反馈成功                    \n");
    printf("\t\t                                              \n");
    printf("\t\t               按enter键返回                   \n");
    printf("\t\t                                              \n");
    printf("\t\t                                              \n");
    printf("\t\t                                              \n");
    printf("\t\t==============================================\n");
    getchar();
    char ch = '\n';
    while (ch != '\n') {
        ch = getchar();

    }
    return 1;
}
int package_mistake(struct account* user)
{
    system("cls");
    getchar();
    int flag = 1;
    long user_package;
    while (flag) {
        system("cls");
        if (flag > 1) {
            printf("\n\n\n\n\n\n\n\n\n");
            printf("\t\t==============================================\n");
            printf("\t\t                                              \n");
            printf("\t\t               包裹异常反馈                    \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t            请输入误领的包裹ID               \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t==============================================\n");
            printf("包裹ID错误或不存在\n");
            printf("ID: ");
        }
        else
        {
            printf("\n\n\n\n\n\n\n\n\n");
            printf("\t\t==============================================\n");
            printf("\t\t                                              \n");
            printf("\t\t               包裹异常反馈                       \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t            请输入误领的包裹ID               \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t==============================================\n");
            printf("ID: ");
        }
        scanf("%ld", &user_package);

        struct package* package_p = find_package_by_package_id(phead, user_package);
        if (package_p == NULL) {
            flag++;
            continue;
        }
        else {
            package_p->state = mistaken;
            flag = 0;
        }
    }
    save_to_file(phead);
    system("cls");
    printf("\n\n\n\n\n\n\n\n\n");
    printf("\t\t==============================================\n");
    printf("\t\t                                              \n");
    printf("\t\t                                              \n");
    printf("\t\t                 反馈成功                     \n");
    printf("\t\t                                              \n");
    printf("\t\t               按enter键返回                   \n");
    printf("\t\t                                              \n");
    printf("\t\t                                              \n");
    printf("\t\t                                              \n");
    printf("\t\t==============================================\n");
    getchar();
    char ch = '\n';
    while (ch != '\n') {
        ch = getchar();

    }
    return 1;
}




void student_main_menu(struct account* user) {
    int choice;
    do {
        system("cls");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t==============================================\n");
        printf("\t\t              菜鸟驿站学生主界面               \n");
        printf("\t\t              1---查询包裹                    \n");
        printf("\t\t              2---寄包裹                      \n");
        printf("\t\t              3---退还包裹                    \n");
        printf("\t\t              4---存包裹                      \n");
        printf("\t\t              5---账号管理                    \n");
        printf("\t\t              6---反馈                        \n");
        printf("\t\t              7---返回                        \n");
        printf("\t\t              0---退出                        \n");
        printf("\t\t==============================================\n");
        printf("请输入选项前的序号: ");


        scanf("%d", &choice);
        
        while (choice != 1 && choice != 2 && choice != 3&&choice!=4 && choice != 5 && choice != 6 && choice != 7 && choice != 0) {
            printf("输入错误，请重新输入\n");
            getchar();scanf("%d", &choice);
            
             
             
        }
        system("cls");
        switch (choice) {
        case 1: query_package(user, 1); break;//查询包裹功能
        case 2: send_package(phead, user); break;//寄包裹功能
        case 3: return_package(user); break;//退包裹功能
        case 4: store_package(phead, user); break; // 存包裹功能
        case 5:  manage_account(user); break;//账号管理功能
        case 6:  feedback(user); break;//反馈功能
        case 7:  return;
        case 0: exit(0);
        default: printf("无效输入！\n");
        }
    } while (choice != 0);
}

void teacher_main_menu(struct account* user) {
    int choice;
    do {
        system("cls");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t==============================================\n");
        printf("\t\t              菜鸟驿站教职工主界面            \n");
        printf("\t\t              1---查询包裹                    \n");
        printf("\t\t              2---寄包裹                      \n");
        printf("\t\t              3---退还包裹                    \n");
        printf("\t\t              4---存包裹                      \n");
        printf("\t\t              5---账号管理                    \n");
        printf("\t\t              6---反馈                        \n");
        printf("\t\t              0---退出                        \n");
        printf("\t\t==============================================\n");
        printf("请输入选项前的序号: ");
        scanf("%d", &choice);
        system("cls");

        switch (choice) {
        case 1: query_package(user, 1); break;//查询包裹功能
        case 2: send_package(phead, user); break;//寄包裹功能
        case 3: return_package(user); break;//退包裹功能
        case 4: store_package(phead, user); break; // 存包裹功能
        case 5: manage_account(user);  break;//账号管理功能
        case 6:  feedback(user); break;//反馈功能
        case 0: exit(0);
        default: printf("无效输入！\n");
        }
    } while (choice != 0);
}

void civilian_main_menu(struct account* user) {
    int choice;
    do {
        system("cls");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t==============================================\n");
        printf("\t\t              菜鸟驿站市民主界面              \n");
        printf("\t\t              1---查询包裹                    \n");
        printf("\t\t              2---寄包裹                      \n");
        printf("\t\t              3---退还包裹                    \n");
        printf("\t\t              4---存包裹                      \n");
        printf("\t\t              5---账号管理                    \n");
        printf("\t\t              6---反馈                        \n");
        printf("\t\t              0---退出                        \n");
        printf("\t\t==============================================\n");
        printf("请输入选项前的序号: ");

        scanf("%d", &choice);
        system("cls");

        switch (choice) {
        case 1:  query_package(user, 1); break;//查询包裹功能
        case 2:  send_package(phead, user); break;//寄包裹功能
        case 3:  return_package(user); break;//退包裹功能
        case 4: store_package(phead, user); break; // 存包裹功能
        case 5:  manage_account(user); break;//账号管理功能
        case 6:  feedback(user);  break;//反馈功能
        case 0: exit(0);
        default: printf("无效输入！\n");
        }
    } while (choice != 0);
}

void business_main_menu(struct account* user) {
    int choice;
    do {
        system("cls");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t==============================================\n");
        printf("\t\t              菜鸟驿站商家主界面              \n");
        printf("\t\t              1---查询包裹                    \n");
        printf("\t\t              2---批量寄包裹                  \n");
        printf("\t\t              3---退还包裹                    \n");
        printf("\t\t              4---存包裹                      \n");
        printf("\t\t              5---账号管理                    \n");
        printf("\t\t              6---反馈                        \n");
        printf("\t\t              0---退出                        \n");
        printf("\t\t==============================================\n");
        printf("请输入选项前的序号: ");

        scanf("%d", &choice);
        system("cls");

        switch (choice) {
        case 1:  query_package(user, 1); break;//查询包裹功能
        case 2: send_more_package(phead, user);
            load_from_file(phead); break;//批量寄包裹功能
        case 3:  return_package(user); break;//退包裹功能
        case 4: store_package(phead, user); break; // 存包裹功能
        case 5: manage_account(user); break;//账号管理功能
        case 6: feedback(user); break;//反馈功能
        case 0: exit(0);
        default: printf("无效输入！\n");
        }
    } while (choice != 0);
}


// 残疾关照子菜单
void disability_support_menu(struct account* user) {
    take_message(user, 4);
}

// 残障人士主界面
void disabled_main_menu(struct account* user) {
    int choice;
    do {
        system("cls");
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t==============================================\n");
        printf("\t\t           菜鸟驿站残障人士主界面             \n");
        printf("\t\t              1---查询包裹                    \n");
        printf("\t\t              2---寄包裹                      \n");
        printf("\t\t              3---退还包裹                    \n");
        printf("\t\t              4---存包裹                      \n");
        printf("\t\t              5---残疾关照功能                \n");  // 内部含子菜单
        printf("\t\t              6---账号管理                    \n");
        printf("\t\t              7---反馈                        \n");
        printf("\t\t              0---退出                        \n");
        printf("\t\t==============================================\n");
        printf("请输入选项前的序号: ");

        scanf("%d", &choice);
        system("cls");

        switch (choice) {
        case 1:  query_package(user, 1); break;
        case 2: send_package(phead, user); break;
        case 3:  return_package(user); break;
        case 4: store_package(phead, user); break;
        case 5: disability_support_menu(user);  break;  // 进入子菜单
        case 6:  manage_account(user); break;
        case 7: feedback(user); break;
        case 0: exit(0);
        default: printf("无效输入！\n");
        }
    } while (choice != 0);
}

void user_home(char user_name[51]) {

    // 根据用户类型选择启动哪个界面

    struct account* i = ahead;
    struct account* user = NULL;
    while (i != NULL)
    {
        if (!(strcmp(i->user_name, user_name)))
        {
            user = i;
        }
        i = i->next;

    }
    int result = user->type;

    switch (result) {
    case 1: business_main_menu(user); break;
    case 2: student_main_menu(user); break;
    case 3: disabled_main_menu(user); break;
    case 4: teacher_main_menu(user); break;
    case 5: civilian_main_menu(user); break;
    default:printf("用户类型错误");
    }

    return;
}