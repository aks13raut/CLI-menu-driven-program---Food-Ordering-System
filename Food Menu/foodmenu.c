//DS mini project: Food Menu
#include<stdio.h>
#include<stdlib.h>
#define MAX 10
//item in menu 
typedef struct mitem
{
	int 	index;
	char	name[30];
	float 	price;
}mitem;
//item in order
typedef struct oitem
{
	char 	name[30];
	float 	price;
	int 	qntty;
}oitem;
//edits item in menu
int editmenu()
{
	FILE *fmenu;
	mitem x;
	char another='y',ch;
	int  noi=0; //no of items in menu
	fmenu = fopen("menu.txt","r");
	while(1)
	{
		ch = fgetc(fmenu);
		if(ch == EOF)
			break;
		if(ch == '\n')
			noi++;
	}
	fclose(fmenu);
	fmenu = fopen("menu.txt","a");
	if(fmenu == NULL)
	{
		printf("cannot open file\n");
		exit(1);
	}
	while(another == 'y')
	{
		printf("Enter name & price of food item: ");
		scanf("%s%f",x.name,&x.price);
		fprintf(fmenu,"%d%s%f\n",++noi,x.name);
		printf("Add another record(y/n): ");
		fflush(stdin);
		scanf("%c",&another);
	}
	fclose(fmenu);
	return noi;
}
//reads menu from file to array of mitem
void getmenu(mitem menu[])
{
	FILE *fmenu;
	int  i=0;
	fmenu = fopen("menu.txt","r");
	if(fmenu == NULL)
	{
		printf("cannot open file\n");
		exit(2);
	}
	while(fscanf(fmenu,"%d%s%f",menu[i].index,menu[i].name,menu[i].price) != EOF)
		i++;
	fclose(fmenu);
}
void displaymenu(mitem menu[],int noi)
{
	int  i;
	for(i=0;i<noi;i++)
		printf("%d %s %f",menu[i].index,menu[i].name,menu[i].price);
}
void main()
{
	int ch,noi,n;
	char another='y';
	mitem Menu[MAX];
	printf("Welcome\n1.menu 2.Admin login");
	scanf("d",&ch);
	getmenu(Menu);
	switch(ch)
	{
		case 1 :while(another == 'y')
				{
					displaymenu(Menu,noi);
					printf("Enter the your index of choice: ");
					scanf("%d",&n);
				}
		case 2 :editmenu(Menu);
		default:printf("Invalid Choice. Please try again\n");
	}
}