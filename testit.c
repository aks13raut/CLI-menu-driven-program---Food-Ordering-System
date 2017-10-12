#include<stdio.h>
#include<string.h>
typedef struct stack
{
	int s[100];
	int tos;
}stack;
void push(stack *t,int ele)
{
	t->s[++t->tos] = ele;
}
char pop(stack *t)
{
	int z = t->s[t->tos];
	t->tos--;
	if(z>9)
	     return((char)z+55);
	else return((char)z+'0');
}
stack tobaseN(int n,int d)
{
	stack x;
	x.tos=-1;
	while(d!=0)
	{
		printf("%(d)",d);
		push(&x,d%n);
		d=d/n;
	}
	return x;
}
void display(stack *t)
{
	int i;
    for(i=t->tos;i>=0;i--)
    {
	if(t->s[i]>9)
	     printf("%c",t->s[i]+55);
	else printf("%d",t->s[i]);
    }
    printf("\n");
}
void hash(char pass[],int m,char hash[])
{
	stack x;
	char ch,temp[10];
	int i=0,b,k,n = strlen(pass);
	hash = {'\0'};
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
		{
			temp[k++] = pop(&x);
			display(&x);
		}
		temp[k] = '\0';
		strcat(hash,temp);
	}
}
void main()
{
	int i;
	char hashkey[50] = {'\0'},a[20],b[20];
	float p = 3.4525;
	printf("%d.%-25s|%.3f\n",i++,a,p);
	printf("%d.%-25s|%.3f\n",i++,"ABXCSSAXADX",p-1.0);
	printf("%d.%-25s|%.3f\n",i++,"ABXCSSAXADX",p-1.0);
	while(1)
	{
		printf("Enter userid and password: ");
		scanf("%s%s",a,b);
		hash(b,strlen(a),hashkey);
		printf("%50s\n",hashkey);
		printf("Enter 1 to continue: ");
		scanf("%d",&i);
		if(i != 1)
			break;
	}
}
/*
while(1)
	{
		if(i < 0)
			i = 0;
		ch = getchar();
		if(ch == 13)
			break;
		if(ch == 8)
		{
			putchar('b');
			putchar(' ');
			putchar('b');
			i--;
			continue;
		}
		pass[i++] = ch;
		ch = '*';
		putchar(ch);
	}
	In 2013 a Password Hashing Competition was announced to choose a new, standard algorithm for password hashing.[7] The winner, 
	selected in July 2015, was a new key stretching algorithm, argon2
	*/