#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "struct.h"
#pragma warning (disable:4996)

extern struct account* ahead;
extern struct account* ap;
extern struct account* atmp;
extern struct package* phead;
void signlog();
void encryptpassword2(int choice, char password[51])
{
     
    int i = 0;
    char ch;
    if (choice == 1)printf("请输入密码        ：");
    else if (choice == 2)printf("\n请再次输入密码确认: ");
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
            printf("密码长度超过50 请重新输入");
            i = 0;
        }
    }
     
}
void query_package(struct account* user)//查询用户包裹
{
    char* name = user->user_name;
    struct package* current = phead;
    while (current != NULL) {
        if (strcmp(current->user_name, name))
        {
            print_package(current);
        }
        current = current->pnext;
    }
    find_package(name);

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
                printf("\t\t           请输入退还的包裹单号                 \n");
                printf("\t\t                                              \n");
                printf("\t\t                                              \n");
                printf("\t\t                                              \n");
                printf("\t\t==============================================\n");
                printf("包裹单号格式错误\n");
                printf("单号: ");
            }
            else
            {
                printf("\n\n\n\n\n\n\n\n\n");
                printf("\t\t==============================================\n");
                printf("\t\t                                              \n");
                printf("\t\t                退还包裹                       \n");
                printf("\t\t                                              \n");
                printf("\t\t                                              \n");
                printf("\t\t           请输入退还的包裹单号                 \n");
                printf("\t\t                                              \n");
                printf("\t\t                                              \n");
                printf("\t\t                                              \n");
                printf("\t\t==============================================\n");
                printf("单号: ");
            }
            scanf("%ld", &user_package);
            struct account* package_p=NULL;
            //struct account *package_p=find_package_by_id(user_package);
            if (package_p == NULL) {
                flag++;
                continue;
            }
            else {
                package_p->state = returned;
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
        char ch;
        while (ch!='/n') {
            ch = getchar();

        }
        return;


     
}
void manage_account( )
{
    int flag = 0;
    struct account* account=NULL;
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
    char ch;
    while (flag!=-1)
    {
        ch = getchar();
        if (ch == '\n')
        {
            system("cls");
                printf("\n\n\n\n\n\n\n\n\n");
                printf("\t\t==============================================\n");
                printf("\t\t                                              \n");                
                printf("\t\t             请输入（用户名 密码）             \n");
                printf("\t\t                                              \n");
                printf("\t\t                                              \n");
                printf("\t\t                                              \n");
                printf("\t\t                                              \n");
                printf("\t\t==============================================\n");
                if (flag == 1) {
                    printf("用户名格式错误\n");
                }
                else if (flag == 2) {
                    printf("输入格式不符要求（要求：用户名 密码）\n");
                }
                else if (flag == 3) {
                    printf("用户名长度不符\n");
                }
                else if (flag == 4) {
                    printf("密码长度不符\n");
                }
                else if (flag == 5) {
                    printf("密码错误！\n");
                }
                else if (flag == 6) {
                    printf("\n用户不存在！\n");
                }
                else;
                printf("请输入:");
            
            
      
            char input_password[51];
            char input_username[51];
            char input_tmp[102] = { 0 };

            int i = 0;
            int indicator = 0;
            for (; i < 102; )
            {
                char c = getch();
                if (c == ' ' && i == 0) {
                    system("cls");
                    
                    flag = 1;
                    continue;
                }
                if (c != ' ' && indicator == 0) {
                    if (c == '\b' && i > 0) {
                        i--;
                        printf("\b \b");
                        continue;
                    }
                    else if (c == '\r' && indicator == 0) {
                         
                         
                        flag = 2;
                        continue;
                    }
                    else if (c != '\b' && i < 50) {
                        input_tmp[i++] = c;
                        printf("%c", c);
                        continue;
                    }
                    else if (i == 50) {
                         
                        
                        flag = 3;
                        continue;
                    }

                }

                if (c == ' ' && i != 0) {
                    indicator = 1;
                    input_tmp[i] = '\0';
                    printf(" ");
                    strcpy(input_username, input_tmp);
                    i = 0;
                    continue;
                }
                if (c == '\r') {
                    input_password[i] = '\0';
                    break;
                }
                else if (c == '\b' && i > 0 && indicator == 1) {
                    i--;
                    printf("\b \b");
                }
                else if (c != '\b' && i < 50 && indicator == 1) {
                    input_password[i++] = c;
                    printf("*");
                }
                else if (i == 50) {
                    
                    flag = 4;
                    continue;
                }
            }

            //分开用户名 密码
            //printf("用户名：%s password:%s\n", input_username,input_password);
            struct account* pp = NULL;
            while (pp != NULL)
            {
                if (strcmp(pp->user_name, input_username) == 0)
                {

                    if (strcmp(pp->password, input_password) == 0)
                    {
                        flag = -1;
                        account = pp;
                        break;
                    }
                    else {
                        
                        flag = 5;
                    }
                }
                pp = pp->next;
            }
            if(i==NULL)flag = 6;

        }
        else if(ch=='0'){
            return;
        }
         

    }
    if (flag == -1) {
        while (1) {
            system("cls");
            char* password1[51];
            char* password2[51];
            encryptpassword2(1, password1[51]);
            encryptpassword2(2, password2[51]);
            if (strcmp(password1, password2) == 0) {
                strcpy(account->password, password2);
                break;
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
        char ch;
        while (ch != '/n') {
            ch = getchar();

        }
        return;
    }


}
 





void student_main_menu(struct account* user) {
    int choice;
    do {
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t==============================================\n");
        printf("\t\t              菜鸟驿站学生主界面               \n");
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
        case 1: query_package(user); break;//查询包裹功能
        case 2: /* send_package() */ break;//寄包裹功能
        case 3: return_package(user); break;//退包裹功能
        case 4: /* store_package() */ break; // 存包裹功能
        case 5: /* manage_account() */ break;//账号管理功能
        case 6: /* feedback() */ break;//反馈功能
        case 0: exit(0);
        default: printf("无效输入！\n");
        }
    } while (choice != 0);
}

void teacher_main_menu(struct account* user) {
    int choice;
    do {
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
        case 1: query_package(user); break;//查询包裹功能
        case 2: /* send_package() */ break;//寄包裹功能
        case 3: /* return_package() */ break;//退包裹功能
        case 4: /* store_package() */ break; // 存包裹功能
        case 5: /* manage_account() */ break;//账号管理功能
        case 6: /* feedback() */ break;//反馈功能
        case 0: exit(0);
        default: printf("无效输入！\n");
        }
    } while (choice != 0);
}

void civilian_main_menu(struct account* user) {
    int choice;
    do {
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
        case 1: /* query_package() */ break;//查询包裹功能
        case 2: /* send_package() */ break;//寄包裹功能
        case 3: /* return_package() */ break;//退包裹功能
        case 4: /* store_package() */ break; // 存包裹功能
        case 5: /* manage_account() */ break;//账号管理功能
        case 6: /* feedback() */ break;//反馈功能
        case 0: exit(0);
        default: printf("无效输入！\n");
        }
    } while (choice != 0);
}

void business_main_menu(struct account* user) {
    int choice;
    do {
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
        case 1: /* query_package() */ break;//查询包裹功能
        case 2: /* more_send_package() */ break;//批量寄包裹功能
        case 3: /* return_package() */ break;//退包裹功能
        case 4: /* store_package() */ break; // 存包裹功能
        case 5: /* manage_account() */ break;//账号管理功能
        case 6: /* feedback() */ break;//反馈功能
        case 0: exit(0);
        default: printf("无效输入！\n");
        }
    } while (choice != 0);
}


// 残疾关照子菜单
void disability_support_menu(struct account* user) {
    int choice;
    do {
        printf("\n\n\n\n\n\n\n\n\n");
        printf("\t\t==============================================\n");
        printf("\t\t             菜鸟驿站残疾关照服务             \n");
        printf("\t\t              1---上门寄货                    \n");
        printf("\t\t              2---上门退货                    \n");
        printf("\t\t              3---上门送货                    \n");
        printf("\t\t              4---上门存货                    \n");
        printf("\t\t              0---返回主菜单                  \n");
        printf("\t\t==============================================\n");
        printf("请输入选项前的序号: ");

        scanf("%d", &choice);
        system("cls");

        switch (choice) {
        case 1: /* door_to_door_send() */ break;
        case 2: /* door_to_door_return() */ break;
        case 3: /* door_to_door_deliver() */ break;
        case 4: /* door_to_door_store() */ break;
        case 0: return;  // 返回主菜单
        default: printf("无效输入！\n");
        }
    } while (choice != 0);
}

// 残障人士主界面
void disabled_main_menu(struct account* user) {
    int choice;
    do {
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
        case 1: /* query_package() */ break;
        case 2: /* send_package() */ break;
        case 3: /* return_package() */ break;
        case 4: /* store_package() */ break;
        case 5: /*disability_support_menu(); */ break;  // 进入子菜单
        case 6: /* manage_account() */ break;
        case 7: /* feedback() */ break;
        case 0: exit(0);
        default: printf("无效输入！\n");
        }
    } while (choice != 0);
}

void user_home(char user_name[51]) {

    // 根据用户类型选择启动哪个界面
    system("cls");
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
    printf("%d", user->type);
    switch (result) {
    case 1: business_main_menu(user); break;
    case 2: student_main_menu(user); break;
    case 3: disabled_main_menu(user); break;
    case 4: teacher_main_menu(user); break;
    case 5: civilian_main_menu(user); break;
    default:printf("用户类型错误");
    }





}