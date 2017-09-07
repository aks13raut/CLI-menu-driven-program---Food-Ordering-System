//DS mini project: Food Menu
#include<stdio.h>
#define MAX 10
//item in menu 
typedef struct mitem
{
	int 	index;
	char	name[30];
	float 	price;
}
//item in order
typedef struct oitem
{
	char 	name[30];
	float 	price;
	int 	qntty;
}item;
//edits item in menu
void  editmenu()
{
	FILE fmenu;
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
	fmenu = fopen("menu.txt","a");
	if(fmenu == NULL)
	{
		printf("cannot open file\n");
		exit(1);
	}
	while(another == 'y')
	{
		Printf("Enter name & price of food item: ");
		scanf("%s%f"",x.name,&x.price);
		fprintf(fmenu,"%d%s%f\n",++noi,x.name);
		Printf("Add another record(y/n): ")
		fflush(stdin);
		scanf("%c",&another);
	}
	fclose(fmenu);
}
//reads menu from file to array of mitem
void getmenu(mitem menu[])
{
	FILE fmenu;
	char ch,n[30];
	int  i=0;
	fmenu = fopen("menu.txt","r");
	if(fmenu == NULL)
	{
		printf("cannot open file\n");
		exit(2);
	}
	while(1)
	{
		printf("%d%s%f",t->index,n,t->price);
		while(ch!=',')
		{
			t->name[j] = ch;
			j++;
			ch = fgetc(fmenu);
		}
		t->name[j]='\0';
		prvch = ch;
}
void main()
{
	int choice;
	mitem Menu[MAX];
	Printf("Welcome\n1.menu 2.Admin login");
	getmenu(Menu);
	printf("Enter the your index of choice\nEnter 0 to go back\n");
