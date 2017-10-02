//DS mini project: Food Menu
#include<stdio.h>
#include<stdlib.h>
#define MAX 10
//item in menu 
typedef struct mitem
{
	char	name[30];
	float 	price;
	int	 	rank;
	struct 	mitem *next;
}mitem;
//menu
typedef struct menu
{
	mitem * start;
}menu;
//item in order
typedef struct oitem
{
	char 	name[30];
	float 	price;
	int 	quantity;
	struct	oitem *next;
}oitem;
//orderList
typedef struct order_list
{
	oitem * start;
}order_list;
void insert(menu *t,mitem ele)
{
	mitem *p,*q,*r;
	p=(mitem*)malloc(sizeof(mitem));
	p->name = ele.name;
	p->price = ele.price;
	p->rank = ele.rank;
	if(t->start == NULL)
	{
		t->start = p;
		p->next = NULL;
		return;
	}
	if(ele.rank > t->start->rank)
	{ 
		p->next = t->start;
		t->start = p;
		return;
	}
	r = t->start;
	q = t->start->next;
	while(q != NULL)
	{
		if(ele.rank > q->rank)
		{
			r->next = p;
			p->next = q;
			return;
		}
		r = q;
		q = q->next;
	}
	r->next = p;
	p->next = NULL;  
}
//edits item in menu
int edit()
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
void getmenu(menu *t)
{
	FILE *fmenu;
	int  i=0;
	mitem x;
	fmenu = fopen("menu.txt","r");
	if(fmenu == NULL)
	{
		printf("cannot open file\n");
		exit(2);
	}
	while(fscanf(fmenu,"%s%f%d",x.name,x.price,x.rank) != EOF)
	{
		insert(t,x);
	};
	fclose(fmenu);
}
void displaymenu(menu *t)
{
	int i=1;
    mitem *q;
    if(t->start == NULL)
    {
        printf("Queue Empty\n");
        return;
    }
    q = t->start;
    while(q!= NULL)
    {
        printf("%d. %s - %f",i++,q->name,q->price);
        q = q->next;
    }
    printf("\n");
}
void main()
{
	int ch,noi,n;
	char another='y';
	menu m;
	order_list ol; 
	m.start = ol.start = NULL;
	printf("Welcome\n1.menu 2.Admin login");
	scanf("d",&ch);
	getmenu(&m);
	switch(ch)
	{
		case 1 :while(another == 'y')
				{
					displaymenu(&m);
					printf("Enter the your index of choice: ");
					scanf("%d",&n);
				}
		case 2 :edit(&m);
		default:printf("Invalid Choice. Please try again\n");
	}
}