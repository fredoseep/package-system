#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include "struct.h"
#include "package.h"

struct package* phead = NULL;
struct package* pp = NULL;
struct package* ptmp = NULL;
struct account* ahead = NULL;
struct account* ap = NULL;
struct account* atmp = NULL;
struct account user_account;
struct message* mhead = NULL;
struct message* mtmp = NULL;
char administrator_password[51] = {
'1','4','2','8','5','7'
};
void user_home();
struct message* loadmessagefromfile();
struct account* loadaccountfromfilefirst()
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

int main()
{
	int choice = -1;
	welcome();
	select();
	scanf("%d", &choice);
	if (getchar())system("cls");
	ahead = loadaccountfromfilefirst();
	load_from_file(&phead);
	mhead = loadmessagefromfile();
	while (choice != 1 && choice != 2 && choice != 3) {
		printf("输入错误，请重新输入\n");
		select();
		scanf("%d", &choice);
		if (getchar())system("cls");
	}
	switch (choice) {
	case 1:
		signlog();
		break;
	case 2:
		administrator_signin();
		break;
	case 3:
		printf("再见！\n");
		exit(0);
	}

}
