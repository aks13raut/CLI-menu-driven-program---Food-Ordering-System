//DS mini project: Food Menu
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>
#include<graphics.h>
#define MAX 10
//item in menu - node in LL menu
typedef struct mitem
{
	char	name[20];
	float 	price;
	int		demand;
	struct 	mitem *next;
}mitem;
//menu - priority queue using LL(Linked List)
typedef struct menu
{
	mitem *start;
}menu;
//item in order - node in LL order_list
typedef struct oitem
{
	char 	name[20];
	float 	price;
	int 	quantity;
	struct	oitem *next,*prev;
}oitem;
//orderList - doubly Linked List
typedef struct order_list
{
	double total;
	oitem *start,*last;
}order_list;
/*	
	stores time and date in string Curr_time
	in  dd-mm-yyyy, hh:mm:ss  format
*/
void get_time(char Curr_time[])
{
	time_t rawtime = time(0);
	struct tm * t;
	t = localtime(&rawtime);
	sprintf(Curr_time,"%02d-%02d-%d, %02d:%02d:%02d",t->tm_mday,t->tm_mon+1,t->tm_year+1900,t->tm_hour,t->tm_min,t->tm_sec);
}
//inserts item in LL in descending order of thier demand
void insert(menu *t,mitem ele)
{
	mitem *p,*q,*r;
	p = (mitem*)malloc(sizeof(mitem));
	strcpy(p->name,ele.name);
	p->price = ele.price;
	p->demand = ele.demand;
	if(t->start == NULL)
	{
		t->start = p;
		p->next = NULL;
		return;
	}
	if(ele.demand > t->start->demand)
	{ 
		p->next = t->start;
		t->start = p;
		return;
	}
	r = t->start;
	q = t->start->next;
	while(q != NULL)
	{
		if(ele.demand > q->demand)
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
//holds output till any key is pressed
void wait()
{
	char   garbage;
	printf("\nPress any key to continue: ");
	garbage = getch();
}
//loads menu from file to LL of mitem
int getmenu(menu *t)
{
	int reset = 0; //flag to determine whether to reduce demand value or not
	FILE *fmenu;
	mitem x;
	fmenu = fopen("menu.txt","r");
	if(fmenu == NULL)
	{
		printf("cannot open file\n");
		perror("fopen:");
		exit(2);
	}
	while(fscanf(fmenu,"%s%f%d",x.name,&x.price,&x.demand) != EOF)
	{
		insert(t,x);
		if(x.demand >= 1000)
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
	printf("Menu Empty\n");
	return;
    }
    q = t->start;
    while(q!= NULL)
    {
		printf("%d. %-20s -- %.3f Rs\n",i++,q->name,q->price);
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
	printf("%d. %-20s | %5.2f * %d = %5.2f Rs\n",i++,q->name,q->price,q->quantity,q->quantity*q->price);
	q = q->next;
    }
    printf("Current Total = %7lf Rs\n",t->total);
}
//updates demand value of food items according to their quantity in order
void demand(menu *m,char a[],int n)
{
	mitem *q;
	q = m->start;
	while(strcmp(q->name,a) != 0)
		q = q->next;
	q->demand += n;
}
//adds food item to order_list
void add(menu *m,order_list *ol,int i,int n)
{
	int j;
	oitem *x;
	mitem *q = m->start;
	x = (oitem*)malloc(sizeof(oitem));
	x->next = NULL;
	for(j=0;j < i-1&& q != NULL;j++)
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
	demand(m,q->name,n);
}
void change_qnty(menu *m,order_list *ol,int i,int n)
{
	int j;
	oitem *q = ol->start;
	for(j=0;j < i-1&& q != NULL;j++)
	q = q->next;
	if(i <= 0|| q == NULL)
	{
		printf("Invalid Choice!\n");
		return;
	}
	ol->total += q->price*(n - q->quantity);
	demand(m,q->name,n - q->quantity);
	q->quantity = n;
}
void remove1(menu *m,order_list *ol,int i)
{
	int j;
	oitem *q = ol->start;
	for(j=0;j < i-1&& q != NULL;j++)
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
	demand(m,q->name,-1*q->quantity);
	free(q);
}
//stores order in file for further use
void print(order_list *ol)
{
	int i=1,k=1;
	FILE *forder;
	char now[25],orderID[15];
	oitem *q = ol->start;
	forder = fopen("Order.txt","w");
	if(forder == NULL)
	{
		printf("Cannot open file\n");
		exit(3);
	}
	get_time(now);
	printf("\t\t\tORDER\n\n");
	while(q != NULL)
	{
		fprintf(forder,"%d. %-20s  | %5.2f * %d | %5.2f Rs\n\n",i++,q->name,q->price,q->quantity,(q->price*q->quantity));
		q = q->next;
	}
	orderID[0] = 'O';
	for(i=0;i<strlen(now);i++)
		if(now[i] >= '0' && now[i] <= '9')
			orderID[k++] = now[i];
	orderID[k] = '\0';
	fprintf(forder,"%s\n",orderID);
	printf("OrderNO : %s\n",orderID);
	display_ol(ol);
	printf("\n___________________________________________________________________\n\n");
	fprintf(forder,"Total Bill= %5lf Rs\n",ol->total);
	printf("Total = %5lf Rs\t\t\t%s\n",ol->total,now);
	fclose(forder);
}
//writes menu to file to update demand values of food items in menu
void save(menu *m,int reset)
{
	FILE *fmenu;
	mitem *q = m->start;
	fmenu = fopen("menu.txt","w");
	if(fmenu == NULL)
	{
		printf("Cannot open file\n");
		exit(4);
	}
	while(q != NULL)
	{	
		if(reset == 1)
			q->demand /= 2;
		fprintf(fmenu,"%s%f %d\n",q->name,q->price,q->demand);
		q = q->next
	}
	fclose(fmenu);
}
void main()
{
	int ch,n,reset,pos;
	float newQ;
	char c,e;
	menu m;
	order_list ol;
	m.start = NULL;
	ol.start = ol.last = NULL;
	ol.total = 0;
	clrscr();
	textcolor(YELLOW);
	getmenu(&m);
	while(1)
	{
		clrscr();
		printf("\nMENU:-\n");
		displaymenu(&m);
		printf("Welcome:-\n1.Add Item\n2.Remove Item\n3.Change Quantity\n4.View Order\n5.Confirm\n6.Cancel\n\nEnter your choice: ");
		scanf("%d",&ch);
		if(ch == 6)
		{
			printf("Order cancelled\n");
			break;
		}
		switch(ch)
		{
			case 1 :	printf("Enter index of food you want: ");
					scanf("%d",&pos);
					printf("How many do you want?: ");
					scanf("%d",&n);
					if(n <= 0)
					{
						printf("Quantity can not be less than 1\n");
						break;
					}
					add(&m,&ol,pos,n);
					display_ol(&ol);
					wait();
					break;
			case 2 :	display_ol(&ol);
					printf("Enter index of item to be deleted: ");
					scanf("%d",&pos);
					remove1(&m,&ol,pos);
					display_ol(&ol);
					wait();
					break;    
			case 3 :	display_ol(&ol);
					printf("Enter index of item to change quantity: ");
					scanf("%d",&pos);
					printf("How many do you want?: ");
					scanf("%f",&newQ);
					if(newQ <= 0)
					{
						printf("Quantity can not be less than 1\n");
						break;
					}
					change_qnty(&m,&ol,pos,newQ);
					display_ol(&ol);
					wait();;
					break;         
			case 4 :	printf("ORDER: \n");
					display_ol(&ol);
					wait();
					break;
			case 5 :	display_ol(&ol);
					printf("Do you want Confirm this Order?(y/n): ");
					fflush(stdin);
					scanf("%c",&c);
					if(c == 'y' || c == 'Y')
					{
						print(&ol);
						save(&m,reset);
						printf("\nOrder placed successfully\n");
					}
					break;
			default:	printf("Invalid Input!\n");
					wait();
		}
		if(ch == 5 &&(c == 'y' || c == 'Y'))
			break;
	}
	printf("\t\tThank you for your Visit!\n");
	getch();
}