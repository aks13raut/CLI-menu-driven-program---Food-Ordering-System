#include<stdio.h>
#include<stdlib.h>
#define MAX 25
void main()
{
	FILE *fp;
	char userid[MAX], pass[MAX];
	fp = fopen("credentials.txt","w");
	if(fp == NULL)
	{
		printf("cannot open file\n");
		exit(1);
	}
	printf("Enter UserID: ");
	gets(userid);
	printf("Enter password: ");
	gets(pass);
	fprintf(fp,"%s %s",userid,pass);
	printf("credentials Successfully saved\n");
}