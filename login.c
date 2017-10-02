#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 25
void main()
{
	FILE *fp;
	int i=1;
	char userid[MAX], pass[MAX],u[MAX],p[MAX];
	fp = fopen("credentials.txt","r");
	if(fp == NULL)
	{
		printf("cannot open file\n");
		exit(1);
	}
	fscanf(fp,"%s%s",u,p);
	printf("Enter UserID: ");
	gets(userid);
	if(strcmp(u,userid) != 0)
	{
		printf("Invalid UserID!\n");
		exit(2);
	}
	else
	{
		printf("Enter Password: ");
		gets(pass);
		if(strcmp(p,pass) != 0)
		{
			printf("Invalid Password!\n");	
			exit(3);
		}
	}
	printf("Login Successful\n");
}