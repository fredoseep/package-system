#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "struct.h"
#pragma warning (disable:4996)
struct package* phead;
struct package* pp;
struct package* ptmp;
int idx = 1;
int hash[1000000];
void package_print();
void account_management();
void package_management();
void package_in();
void package_out();
void account_print();
void administrator_main_menu()
{
    int choice_administrator = 0;
    int flag_error = 0;
    do {
        if (flag_error == 0) {

            printf("\n\n\n\n\n\n\n\n\n");
            printf("\t\t==============================================\n");
            printf("\t\t              菜鸟驿站管理员主界面              \n");
            printf("\t\t              1---账号管理                     \n");
            printf("\t\t              2---包裹管理                     \n");
            printf("\t\t              3---提醒                        \n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t==============================================\n");
            printf("请输入选项前的序号: ");
        }
        else {

            printf("\n\n\n\n\n\n\n\n\n");
            printf("\t\t==============================================\n");
            printf("\t\t              菜鸟驿站管理员主界面              \n");
            printf("\t\t              1---账号管理                     \n");
            printf("\t\t              2---包裹管理                     \n");
            printf("\t\t              3---提醒                        \n");
            printf("\t\t              0---退出                        \n");
            printf("\t\t                                              \n");
            printf("\t\t==============================================\n");
            printf("请输入正确的序号: ");
        }

        scanf("%d", &choice_administrator);
        system("cls");

        switch (choice_administrator) {
        case 1: account_management(); break; //账号管理功能
        case 2: package_management(); break;  //包裹管理功能
        case 3:   break;//提醒功能
        case 0: administrator_main_menu();
        default: flag_error = 1;
        }
        system("cls");
    } while (choice_administrator == 0 || flag_error == 1);
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
        int choice_account_management = 0;
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
        case 0: exit(0);
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
            "管理员", "商家", "学生", "残障人士", "教师", "居民"
        };

        printf("\n%-20s %-12s %-15s %-8s\n",
            "用户名", "用户类型", "电话号码", "状态");
        printf("------------------------------------------------------------\n");

        while (current != NULL) {
            // 转换状态为可读字符串
            const char* state_str = current->state ? "启用" : "禁用";

            printf("%-20s %-12s %-15s %-8s\n",
                current->user_name,
                user_type_str[current->type], // 直接通过枚举值索引
                current->phone_number,
                state_str);

            current = current->next;
        }
        printf("------------------------------------------------------------\n");
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
        return found_flag;
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
        return found_flag;
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
            int choice_package_management = 0;
            scanf("%d", &choice_package_management);
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
                else administrator_main_menu();
            }
            else
            {
                if (phead == NULL)
                {
                    pp = (struct package*)malloc(sizeof(struct package));
                    pp->category.size = pchoice;
                    pp->id = idx++;
                    phead = pp;
                    ptmp = pp;
                    pp->pnext = NULL;

                }
                else
                {
                    pp = (struct account*)malloc(sizeof(struct account));
                    pp->category.size = pchoice;
                    pp->id = idx++;
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
                else administrator_main_menu();

            }

            else
            {
                pp->category.delicacy = pchoice;
                break;
            }
        }
        system("cls");

        getchar();
        int flag = 1;
        char user_name_package_p[60];
        while (flag) {
            if (flag > 1) {
                printf("\n\n\n\n\n\n\n\n\n");
                printf("用户名长度超过50，请重新输入: ");
            }
            else
            {
                printf("\n\n\n\n\n\n\n\n\n");
                printf("请输入包裹的用户名: ");
            }
            fgets(user_name_package_p, 60, stdin);

            if (strlen(user_name_package_p) > 50)
            {
                while (getchar() != '\n');
                flag++;
            }
            else {
                strcpy(pp->user_name, user_name_package_p);
                flag = 0;
            }
            system("cls");
        }

        pp->state = already;
        pp->pickup_code = rnumber();
        //pp->position_code=
        while (1) {
            printf("\n\n\n\n\n\n\n\n\n");
            printf("\t\t==============================================\n");
            printf("\t\t                                              \n");
            printf("\t\t                                              \n");
            printf("\t\t                   成功入库                    \n");
            printf("\t\t                                              \n");
            printf("\t\t                 按enter键返回                \n");
            printf("\t\t                                              \n");
            printf("\t\t==============================================\n");
            scanf("%c", &pchoice);
            if (pchoice == '\n') {
                system("cls");
                administrator_main_menu();
                break;
            }
            system("cls");
        }
        return;
    }
    void package_out()
    {

    }