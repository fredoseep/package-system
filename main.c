#pragma warning (disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include "struct.h"
struct package* phead = NULL;
struct package* pp = NULL;
struct package* ptmp = NULL;
struct account* ahead = NULL;
struct account* ap = NULL;
struct account* atmp = NULL;
struct account user_account;
char administrator_password[51] = {
'1','4','2','8','5','7'
};
void user_home();

int main()
{
	int choice = -1;
	welcome();
	select();
	scanf("%d", &choice);
	if (getchar())system("cls");
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
