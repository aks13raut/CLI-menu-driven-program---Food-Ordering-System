//DS mini project: Food Menu
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
//item in menu - node in menu LL
typedef struct mitem
{
	char	name[20];
	float 	price;
	int		demand;
	struct 	mitem *next;
}mitem;
//menu - priority Queue using LL
typedef struct menu
{
	mitem *start;
}menu;
typedef struct stack
{
	int s[100];
	int tos;
}stack;

void push(stack *t,int ele)
{
	t->s[++t->tos] = ele;
}
/*
	if poped integer is greater than 9
	then funtion returns corresponding alphabet
	e.g :- 10 --> A, 11 --> B, 26 --> Q
*/
char pop(stack *t)
{
	int z = t->s[t->tos];
	t->tos--;
	if(z > 9)
	     return((char)z + 55);
	else return((char)z + '0');
}
//converts decimal value to specified base
stack tobaseN(int n,int d)
{
	stack x;
	x.tos=-1;
	while(d!=0)
	{
		push(&x,d%n);
		d=d/n;
	}
	return x;
}
/*
	Genrates hashkey for password in "pass" string
	"temp" string stores value of ascii code of a charecter
	of "pass" in base "b"
	value of "b" for each charecter is calculated by 
	m - length of string "userid"
	n - length of string "pass"
	i - position of the charecter in string "pass"
*/
void hash(char pass[],int m,char hash[])
{
	stack x;
	char ch,temp[10];
	int i=0,b,k,n = strlen(pass);
	hash[0] = '\0';
	x.tos = -1;
	while(i<n)
	{
		ch = pass[i++];
		b = m + (i*i)%n;
		while(b < 2)
			b += m;
		x = tobaseN(b,ch);
		k = 0;
		while(x.tos > -1)
			temp[k++] = pop(&x);
		temp[k] = '\0';
		strcat(hash,temp);
	}
}
//stores userid and password for new user
void register1()
{
	FILE *fp;
	char userid[20], pass[20], hashkey[50];
	menu m;
	void save(menu *m);
	fp = fopen("credentials.txt","w");
	if(fp == NULL)
	{
		printf("cannot open file\n");
		exit(3);
	}
	printf("Enter a username: ");
	scanf("%s",userid);
	printf("Enter a password: ");
	scanf("%s",pass);
	hash(pass,strlen(userid),hashkey);
	fprintf(fp,"%s %s",userid,hashkey);
	fclose(fp);
	printf("Registeration Successful\n");
	m.start = NULL;
	save(&m);
}
int login()
{
	FILE *fp;
	int i = 0;
	char userid[20], pass[20], u[20], hashkey1[50], hashkey2[50],ch;
	fp = fopen("credentials.txt","r");
	if(fp == NULL)
	{
		printf("cannot open file\n");
		exit(1);
	}
	fscanf(fp,"%s%s",u, hashkey1);
	printf("Enter UserID: ");
	fflush(stdin);
	gets(userid);
	if(strcmp(u,userid) != 0)
	{
		printf("Invalid UserID!\n");
		return 0;
	}
	else
	{
		printf("Enter Password: ");
		while(1)
		{
			if(i < 0)
				i = 0;
			ch = getch();
			if(ch == '\r')
			{
				printf("\n");
				break;
			}
			if(ch == '\b')
			{
				putch('\b');
				putch(' ');
				putch('\b');
				i--;
				continue;
			}
			pass[i++] = ch;
			putchar('*');
		}
		hash(pass,strlen(userid),hashkey2);
		if(strcmp(hashkey1,hashkey2) != 0)
		{
			printf("Invalid Password!\n");
			return 0;
		}
	}
	fclose(fp);
	printf("Login Successful\n");
	return 1;
}
void change_pass()
{
	FILE *fp;
	char ch,userid[20], pass[20], hashkey[50];
	fp = fopen("credentials.txt","r");
	if(fp == NULL)
	{
		printf("cannot open file\n");
		exit(2);
	}
	fscanf(fp,"%s",userid);
	fclose(fp);
	fp = fopen("credentials.txt","w");
	if(fp == NULL)
	{
		printf("cannot open file\n");
		exit(3);
	}
	printf("Enter New Password: ");
	//fflush(stdin);
	gets(pass);
	hash(pass,strlen(userid),hashkey);
	fprintf(fp,"%s %s",userid,hashkey);
	fclose(fp);
	printf("Password changed Successfully\n");
	fclose(fp);
}
//holds output till any key is pressed
void wait()
{
	char   garbage;
	printf("\nPress any key to continue: ");
	garbage = getch();
}
void displaymenu(menu *t)
{
	int i=1; // index
    mitem *q;
    if(t->start == NULL)
    {
	printf("Menu Empty\n");
	return;
    }
    q = t->start;
	printf("MENU:-\n");
    while(q!= NULL)
    {
	printf("%d. %-20s -- %.3f Rs\n",i++,q->name,q->price);
	q = q->next;
    }
    printf("\n");
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
void getmenu(menu *t)
{
	FILE *fmenu;
	mitem x;
	fmenu = fopen("menu.txt","r");
	if(fmenu == NULL)
	{
		printf("cannot open file\n");
		exit(2);
	}
	while(fscanf(fmenu,"%s%f%d",x.name,&x.price,&x.demand) != EOF)
		insert(t,x);
	fclose(fmenu);
}
void change_price(menu *m,int pos,float newPrice)
{
	int i;
	mitem *q = m->start;
	if(q == NULL)
	{
		printf("Menu is Empty\n");
		return;
	}
	for(i=0;i < pos-1 && q != NULL;i++)
	q = q->next;
	if(pos <= 0|| q == NULL)
	{
		printf("Invalid Choice!\n");
		return;
	}
	printf("price of %s changed from %.3f to %.3f\n",q->name,q->price,newPrice);
	q->price = newPrice;
}
void deletepos(menu *m,int pos)
{
	int i;
	mitem *q = m->start;
	if(pos == 1)
	{
		printf("%s deleted\n",m->start->name);
		m->start = m->start->next;
		return;
	}
	for(i=0;i < pos-2 && q != NULL;i++)
	q = q->next;
	if(pos <= 0|| q == NULL)
	{
		printf("Invalid Choice!\n");
		return;
	}
	printf("%s deleted\n",q->next->name);
	q->next = q->next->next;
}
void save(menu *m)
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
		fprintf(fmenu,"%s %f %d\n",q->name,q->price,q->demand);
		q = q->next;
	}
	fclose(fmenu);
}
void main()
{
	int ch1,ch2,n=0,loggedin =0;
	char c = 'n',a[20];
	menu m;
	mitem food;
	m.start = NULL;
	food.demand = 0;
	textcolor(CYAN);
	while(1)
	{
		clrscr();
		printf("1. Login\n2. Register\n3. Change Password\n4. Exit\nEnter your Choice: ");
		scanf("%d",&ch1);
		if(ch1 == 4)
			exit(0);
		switch(ch1)
		{
			case 1 :while(n < 3)
					{
						loggedin = login();
						if(loggedin)
							break;
						n++;
						printf("%d attempts left\n",3-n);
					}
					if(loggedin == 0)
					{
						printf("3 Consecutive Failed Attempts\nTry again Latar.");
						exit(6);
					}
					break;
			case 2 :printf("Previously stored Data will be overwritten\n is it ok?(y/n):");
					fflush(stdin);
					scanf("%c",&c);
					if(c != 'y' && c != 'Y')
						break;
					register1();
					printf("Please Login if you want to edit the menu\n");
					wait();
					break;
			case 3 :while(n < 3)
					{
						loggedin = login();
						if(loggedin)
							break;
						n++;
						printf("%d attempts left\n",3-n);
					}
					if(loggedin == 0)
					{
						printf("3 Consecutive Failed Attempts\nTry again Latar.");
						exit(7);
					}
					change_pass();
					break;
			default:printf("Invalid Input!\n");
		}
		wait();
		if(loggedin)
			break;
	}
	getmenu(&m);
	while(1)
	{
		clrscr();
		displaymenu(&m);
		printf("Options:-\n1.Add Item\n2.Remove Item\n3.Change Price\n4.Remove All\n5.Exit\nEnter your choice: ");
		scanf("%d",&ch2);
		if(ch2 == 5)
		{
			printf("Do you want to save the changes?(y/n): ");
			fflush(stdin);
			scanf("%c",&c);
			if(c == 'y'||c == 'Y')
				save(&m);
			break;
		}
		switch(ch2)
		{
			case 1 :printf("Enter Name of food: ");
					fflush(stdin);
					gets(food.name);
					if(strlen(food.name) >= 20)
					{
						printf("Food name must be less than 20 letters!\n");
						break;
					}
					printf("Enter Price of food: ");
					scanf("%f",&food.price);
					insert(&m,food);
					displaymenu(&m);
					wait();
					break;
			case 2 :printf("Eneter index of item to be deleted: ");
					scanf("%d",&n);
					deletepos(&m,n);
					displaymenu(&m);
					wait();
					break;
			case 3 :printf("Eneter index of item to change_price: ");
					scanf("%d",&n);
					printf("Enter New Price of food: ");
					scanf("%f",&food.price);
					change_price(&m,n,food.price);
					displaymenu(&m);
					wait();
					break;
			case 4 :m.start = NULL;
					displaymenu(&m);
					wait();
					break;
			default:printf("Invalid Input!\n");
					displaymenu(&m);
					wait();
		}
	}
}