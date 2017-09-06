//DS mini project: Food Menu
#include<stdio.h>
#define MAX 10
typedef struct mitem
{
	int 	index;
	char	name[30];
	float 	price;
}
typedef struct oitem
{
	char 	name[30];
	float 	price;
	int 	qntty;
}item;
void getmenu(menu *t)
{
	FILE fmenu;
	char ch,n[30];
	int i=0;
	fmenu = fopen("menu.txt","r");
	if(fmenu == NULL)
	{
		printf("Cannot Open File!\a");
		exit(1);
	}
	printf("Enter the your index of choice\nEnter 0 to go back\n");
	while(fscanf(fmenu,"%d%s%f",t->index,n,t->price)!=EOF)
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
	item Menu[MAX];
	Printf("Welcome\n1.menu")
	getmenu(Menu);
}
