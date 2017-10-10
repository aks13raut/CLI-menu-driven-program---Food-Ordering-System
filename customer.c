//DS mini project: Food Menu
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10
//item in menu 
typedef struct mitem
{
	char	name[30];
	float 	price;
	int	rank;
	struct 	mitem *next;
}mitem;
//menu
typedef struct menu
{
	mitem *start;
}menu;
//item in order
typedef struct oitem
{
	char 	name[30];
	float 	price;
	int 	quantity;
	struct	oitem *next,*prev;
}oitem;
//orderList
typedef struct order_list
{
	double total;
	oitem *start,*last;
}order_list;
//inserts item in LL in descending order of thier rank
void insert(menu *t,mitem ele)
{
	mitem *p,*q,*r;
	p = (mitem*)malloc(sizeof(mitem));
	strcpy(p->name,ele.name);
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
//loads menu from file to LL of mitem
int getmenu(menu *t)
{
	int reset = 0;
	FILE *fmenu;
	mitem x;
	fmenu = fopen("menu.txt","r");
	if(fmenu == NULL)
	{
		printf("cannot open file\n");
		exit(2);
	}	
	while(fscanf(fmenu,"%s%f%d",x.name,&x.price,&x.rank) != EOF)
	{
		insert(t,x);
		if(x.rank >= 1000)
			reset = 1;
	}
	fclose(fmenu);
	return reset;
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
		printf("%d\n",q->rank);
        printf("%d. %s  --  %f Rs\n",i++,q->name,q->price);
        q = q->next;
    }
    printf("\n");
}
void display_ol(order_list *t)
{
	int i=1;
    oitem *q;
    if(t->start == NULL)
    {
        printf("No orders yet\n");
        return;
    }
    q = t->start;
    while(q!= NULL)
    {
        printf("%d. %s | %f * %d = %f Rs\n",i++,q->name,q->price,q->quantity,q->quantity*q->price);
        q = q->next;
    }
    printf("Current Total = %lf\n",t->total);
}
void rank(menu *m,char a[],int n)
{
	mitem *q;
	q = m->start;
	while(strcmp(q->name,a) != 0)
		q = q->next;
	q->rank += n;
}
void add(menu *m,order_list *ol,int i,int n)
{
	oitem *x;
	mitem *q = m->start;
	x = (oitem*)malloc(sizeof(oitem));
	x->next = NULL;
	for(int j=0;j < i-1&& q != NULL;j++)
        q = q->next;
	if(i <= 0|| q == NULL)
	{
		printf("Invalid Choice!\n");
		return;
	}
	strcpy(x->name,q->name);
	x->price = q->price;
	x->quantity = n;
	if(ol->start == NULL)
	{
		ol->start = ol->last = x;
		x->prev = NULL;
	}
	else
	{
		ol->last->next = x;
		x->prev = ol->last;
		ol->last = x;
	}
	ol->total += (x->price*x->quantity);
	rank(m,q->name,n); 
}
void edit(menu *m,order_list *ol,int i,int n)
{
	oitem *q = ol->start;
	for(int j=0;j < i-1&& q != NULL;j++)
        q = q->next;
	if(i <= 0|| q == NULL)
	{
		printf("Invalid Choice!\n");
		return;
	}
	ol->total += q->price*(n - q->quantity);
	rank(m,q->name,n - q->quantity);
 	q->quantity = n;
}
void remove1(menu *m,order_list *ol,int i)
{
	mitem *p = m->start;
	oitem *q = ol->start;
	for(int j=0;j < i-1&& q != NULL;j++)
        q = q->next;
	if(i <= 0|| q == NULL)
	{
		printf("Invalid Choice!\n");
		return;
	}
	if(q == ol->start && q == ol->last)
		ol->start = ol->last = NULL;
	else if(q == ol->start)
	{
		ol->start = ol->start->next;
		ol->start->prev = NULL;
	}
		else if(q == ol->last)
		{
			ol->last = ol->last->prev;
			ol->last->next = NULL;
		}
			else
			{
				q->prev->next = q->next;
				q->next->prev = q->prev;
			}
	ol->total -= (q->price*q->quantity);
	rank(m,q->name,-1*q->quantity);
	free(q);
}
void print(order_list *ol)
{
	int i=1;
	FILE *forder;
	oitem *q = ol->start;
	forder = fopen("order.txt","w");
	if(forder == NULL)
	{
		printf("cannot open file\n");
		exit(3);
	}
	printf("\t\t\tORDER\n\n");	
	while(q != NULL)
	{
		printf("%d. %s\t| %.3f * %d\t| %.2f Rs\t\n",i++,q->name,q->price,q->quantity,(q->price*q->quantity));
		printf("      \t|          \t|\n");
		fprintf(forder,"%d. %s  | %f * %d | %f Rs\n\n",i++,q->name,q->price,q->quantity,(q->price*q->quantity));
		q = q->next;
	}
	printf("\n___________________________________________________________\n\n");
	printf("Total = %lf",ol->total);
	fclose(forder);
}
void save(menu *m,int reset)
{
	FILE *fmenu;
	mitem *q = m->start;
	fmenu = fopen("menu.txt","w");
	if(fmenu == NULL)
	{
		printf("cannot open file\n");
		exit(4);
	}	
	while(q != NULL)
	{	
		if(reset == 1)
			q->rank /= 2;
		fprintf(fmenu,"%s %f %d\n",q->name,q->price,q->rank);
		q = q->next;
	}
	fclose(fmenu);
}
void main()
{
	int ch,n,reset;
	char another='y';
	menu m;
	order_list ol;
	m.start = NULL;
	ol.start = ol.last = NULL;
	ol.total = 0;
	reset = getmenu(&m);
	displaymenu(&m);
	add(&m,&ol,1,3);
	display_ol(&ol);
	displaymenu(&m);
	add(&m,&ol,2,2);
	display_ol(&ol);
	displaymenu(&m);
	edit(&m,&ol,2,5);
	display_ol(&ol);
	displaymenu(&m);
	remove1(&m,&ol,1);
	add(&m,&ol,3,7);
	display_ol(&ol);
	displaymenu(&m);
	display_ol(&ol);
	displaymenu(&m);
	print(&ol);
	save(&m,reset);
	/*
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
	*/
}