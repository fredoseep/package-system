#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include "struct.h"
#pragma warning(disable:4996)

extern struct account* build();
char* encryptpassword(int choice);
extern struct account* ahead;
extern struct account* ap;
extern struct account* atmp;
char administrator_password[50];
extern void login();
char* input_password;
char* input_username;
char* input_tmp;
struct account* login_ap;
extern struct account user_account;
struct account* loadaccountfromfile();

/*void read()
{
	FILE* file = fopen("account.txt", "r");
	if (!file)
	{
		printf("打开错误");
		return;
	}
	char line[256];
	char Ruser_name[51];
	enum user_type Rtype;
	char Rpassword[51];
	char Rphone_number[51];
	bool Rstate;
	struct account* Rnext;
	while (fgets(line, sizeof(line), file) != NULL) {
		sscanf(line, "%50[^,],%d,%50[^,],%[50^,],%d，%p", Ruser_name, &Rtype, Rpassword, Rphone_number, &Rstate, &Rnext);
		if (ahead == NULL)
		{
			ap = (struct account*)malloc(sizeof(struct account));
			strcpy(ap->user_name, Ruser_name);
			ap->type = Rtype;
			strcpy(ap->password, Rpassword);
			strcpy(ap->phone_number, Rphone_number);
			ap->state = Rstate;
			ap->next = Rnext;

			ahead = ap;
			atmp = ap;
			ap->next = NULL;

		}
		else
		{
			ap = (struct account*)malloc(sizeof(struct account));
			strcpy(ap->user_name, Ruser_name);
			ap->type = Rtype;
			strcpy(ap->password, Rpassword);
			strcpy(ap->phone_number, Rphone_number);
			ap->state = Rstate;
			ap->next = Rnext;

			atmp->next = ap;
			atmp = ap;
			ap->next = NULL;

		}
		return ap;

	}
}*/

void welcome() {
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\t\t                                              \n");
	printf("\t\t==============================================\n");
	printf("\t\t                                              \n");
	printf("\t\t                                              \n");
	printf("\t\t             欢迎使用菜鸟驿站                 \n");
	printf("\t\t                                              \n");
	printf("\t\t                                              \n");
	printf("\t\t==============================================\n");
	printf("\t\t-----^-^-----------------------------^-^------\n");
	printf("按enter键继续");
	if (getchar())system("cls");
}
void select() {
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\t\t                                              \n");
	printf("\t\t==============================================\n");
	printf("\t\t                  请选择身份                   \n");
	printf("\t\t                  1---用户                    \n");
	printf("\t\t                  2---管理员                  \n");
	printf("\t\t                  3---退出                    \n");
	printf("\t\t                                              \n");
	printf("\t\t==============================================\n");
	printf("\t\t-----^-^-----------------------------^-^------\n");
	printf("请输入选项前的序号:");
}

void administrator_signin()
{
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\t\t                                              \n");
	printf("\t\t==============================================\n");
	printf("\t\t             请输入（管理员密码）              \n");
	printf("\t\t                                              \n");
	printf("\t\t                                              \n");
	printf("\t\t                                              \n");
	printf("\t\t                                              \n");
	printf("\t\t==============================================\n");
	printf("\t\t-----^-^-----------------------------^-^------\n");
	printf("密码:");
	while (1) {
		if (!strcmp(encryptpassword(3), administrator_password)) {
			system("cls");
			administrator_main_menu();
			break;
		}
		else {
			system("cls");
			printf("\n密码错误 请再次输入");
		}
	}

}

void signlog() {
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\t\t                                              \n");
	printf("\t\t==============================================\n");
	printf("\t\t             请输入（用户名 密码）            \n");
	printf("\t\t                                              \n");
	printf("\t\t                                              \n");
	printf("\t\t                                              \n");
	printf("\t\t             新用户请按enter注册              \n");
	printf("\t\t==============================================\n");
	printf("\t\t-----^-^-----------------------------^-^------\n");
	printf("请输入:");

	char input_password[51];
	char input_username[51];
	char input_tmp[102] = { 0 };

	int i = 0;
	int indicator = 0;
	for (; i < 102; )
	{
		char c = getch();
		if (c == '\r' && i == 0 && indicator == 0) {//仅输入换行进入注册
			system("cls");
			login();
			return;//此处完善user_home之后换成对应用户主界面
		}
		if (c == ' ' && i == 0) {
			system("cls");
			printf("用户名格式错误");
			signlog();
		}
		if (c != ' ' && indicator == 0) {
			if (c == '\b' && i > 0) {
				i--;
				printf("\b \b");
				continue;
			}
			else if (c == '\r' && indicator == 0) {
				system("cls");
				printf("输入格式不符要求（要求：用户名 密码）");
				signlog();
			}
			else if (c != '\b' && i < 50) {
				input_tmp[i++] = c;
				printf("%c", c);
				continue;
			}
			else if (i == 50) {
				system("cls");
				printf("用户名长度不符");
				signlog();
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
			system("cls");
			printf("密码长度不符");
			signlog();
		}
	}

	//分开用户名 密码
	//printf("用户名：%s password:%s\n", input_username,input_password);
	if (signin_match(input_username, input_password) == 1) {
		system("cls");
		struct account* user = loadaccountfromfile();
		while (user != NULL)
		{
			if (!(strcmp(user->user_name, input_username)))
			{
				break;
			}
			user = user->next;
		}
		if (user->state == 1) {
			printf("登录成功");
			user_home(input_username);
		}
		else {
			system("cls");
			printf("账号已被禁用");
			signlog();
		}
	}
	else if (signin_match(input_username, input_password) == 0) {
		system("cls");
		printf("\n密码错误！\n");
		signlog();
	}
	else {
		system("cls");
		printf("\n用户不存在！\n");
		signlog();
	}

}



void login() {
	printf("\n\n\n\n\n\n\n\n\n");
	printf("\t\t                                              \n");
	printf("\t\t==============================================\n");
	printf("\t\t             欢迎使用菜鸟驿站                 \n");
	printf("\t\t             请起一个用户名吧                 \n");
	printf("\t\t          （用户名最多50个字符）              \n");
	printf("\t\t                                              \n");
	printf("\t\t                                              \n");
	printf("\t\t==============================================\n");
	printf("\t\t-----^-^-----------------------------^-^------\n");
	printf("请输入用户名:");
	char user_name_input[51];
	while (1) {
		scanf("%s", user_name_input);
		getchar();
		if (isUsernameTaken(ahead, user_name_input)) {
			system("cls");
			printf("用户名已存在,换一个名字吧");
			login();
		}
		else if(strlen(user_name_input) > 50) {
			system("cls");
			printf("用户名长度超过50 请重新输入");
			login();
		}
		else
		{
			struct account* login_ap = NULL;
			login_ap = build(user_name_input);
			login_password(login_ap);
			getchar();
			signlog();
			//user_home();
			break;
		}

	}
}
