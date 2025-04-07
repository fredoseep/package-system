#pragma once
#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "struct.h"

extern struct account* ahead;
extern struct account* ap;
extern struct account* atmp;
extern struct account user_account;
void saveaccounttofile(struct account* ahead);
struct account* loadaccountfromfile();
//注册时创建账户链表 返回当前注册指针 用于加入密码
struct account* build(char* user_name_input)
{

	if (ahead == NULL)
	{
		ap = (struct account*)malloc(sizeof(struct account));
		strcpy(ap->user_name, user_name_input);
		ap->state = 1;
		ahead = ap;
		atmp = ap;
		ap->next = NULL;

	}
	else
	{
		ap = (struct account*)malloc(sizeof(struct account));
		atmp = ahead;
		strcpy(ap->user_name, user_name_input);
		ap->state = 1;
		while (atmp->next != NULL)
		{
			atmp = atmp->next;
		}
		atmp->next = ap;
		atmp = ap;
		ap->next = NULL;

	}
	saveaccounttofile(ahead);
	return ap;
}

void saveaccounttofile(struct account* ahead)
{
	FILE* fp;
	fp = fopen("account.txt", "w");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		exit(1);
	}
	struct account* i = ahead;
	while (i != NULL)
	{
		fprintf(fp, "%s %d %s %s %d\n", i->user_name, i->type, i->password, i->phone_number,i->state);
		i = i->next;
	}
	fclose(fp);
}	
struct account* loadaccountfromfile()
{
	FILE* fp;
	fp = fopen("account.txt", "r");
	if (fp == NULL)
	{
		printf("文件打开失败\n");
		exit(0);
	}

	struct account* current = NULL;
	struct account* previous = NULL;
	char user_name[50];
	int type;
	char password[50];
	char phone_number[12];
	int state;
	ahead = NULL;
	while (fscanf(fp, "%s %d %s %s %d", user_name, &type, password, phone_number, &state) == 5)
	{
		current = (struct account*)malloc(sizeof(struct account));
		strcpy(current->user_name, user_name);
		current->type = type;
		strcpy(current->password, password);
		strcpy(current->phone_number, phone_number);
		current->state = state;
		current->next = NULL;

		if (ahead == NULL)
		{
			ahead = current;
			previous = current;
		}
		else
		{
			previous->next = current;
			previous = current;
		}
	}

	fclose(fp);
	return ahead;
}
//登录时加载账户链表

//用户名查重 可用返回0 不可用返回1
int isUsernameTaken(struct account* ahead, char* user_name_input) {
	if (ahead == NULL)return 0;		
	struct account* i = loadaccountfromfile();
	while (i != NULL)
	{
		if (strcmp(i->user_name, user_name_input) == 0)
			return 1;
		i = i->next;
	}
	return 0;

}
void inputthename(struct account* inputthename_ap, char* user_name_input) {
	strcpy(inputthename_ap->user_name, user_name_input);
	saveaccounttofile(ahead);
}

//匹配登录用户名和密码 成功返回1 失败返回0 用户名不存在返回-1
int signin_match(char* signin_user_name, char* signin_password)
{
	struct account* i = loadaccountfromfile();
	while (i != NULL)
	{
		if (!(strcmp(i->user_name, signin_user_name)))
		{
			if (!(strcmp(i->password, signin_password)))
			{
				user_account = *i;
				return 1;
			}
			else return 0;
		}
		i = i->next;
	}
	return -1;

}
//加密密码输出
char* encryptpassword(int choice)
{
	static char password[51];
	int i = 0;
	char ch;
	if (choice == 1) {
		printf("请输入密码        ：");

	}
	else if (choice == 2) {
		printf("\n请再次输入密码确认: ");
	}
	else { ; }

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
	return password;
}

//注册密码
void login_password(struct account* login_password_ap)
{
	char tempPassword[50], confirmPassword[51];

	while (1) {
		strcpy(tempPassword, encryptpassword(1));
		strcpy(confirmPassword, encryptpassword(2));
		if ((strcmp(tempPassword, confirmPassword) != 0)) {
			printf("\n两次输入的密码不一致，注册失败！\n");
		}
		else
		{
			system("cls");
			strcpy(login_password_ap->password, tempPassword);
			saveaccounttofile(ahead);
			printf("\n\n\n\n\n\n\n\n\n");
			printf("\t\t                                              \n");
			printf("\t\t==============================================\n");
			printf("\t\t                  请选择您的身份                   \n");
			printf("\t\t                  1---商家                   \n");
			printf("\t\t                  2---学生                  \n");
			printf("\t\t                  3---残障人士             \n");
			printf("\t\t                  4---教职工                   \n");
			printf("\t\t                  5---居民                \n");
			printf("\t\t                                              \n");
			printf("\t\t==============================================\n");
			printf("\t\t-----^-^-----------------------------^-^------\n");
			printf("请输入选项前的序号:");
			int choice1;
			while (1) {
				scanf("%d", &choice1);
				if (choice1 != 1 && choice1 != 2 && choice1 != 3 && choice1 != 4 && choice1 != 5) {
					printf("无效输入！请重新输入！\n");
				}
				else break;
			}
			printf("请输入您的手机号码:");
			for (int i = 0; i < 11; i++)
			{
				login_password_ap->phone_number[i] = getchar();
				if (login_password_ap->phone_number[i] == '\n') {
					i--;
				}
			}
			login_password_ap->phone_number[11] = '\0';
			login_password_ap->type = choice1;
			saveaccounttofile(ahead);
			printf("注册成功！欢迎新用户！\n");
			system("cls");
			break;
		}
	}
}


