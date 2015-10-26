#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 
#include <math.h>
#include<windows.h>
#include<time.h>
#define C2D(c) (c-'0')  //???????
#define D2C(d) (d+'0')  //???????

#define OK 1 
#define ERROR 0 
#define TRUE 1 
#define FALSE 0 

typedef int Status;
typedef int ElemType;

int getnumber(char* a)
{
	int number = 0, i;
	for (i = 0; i < min(strlen(a), 5 - 1); i++)
	{
		if (a[i] != '\n')
			number = number + (a[i] - '0') * pow(10, (min(strlen(a), 5 - 1) - 1 - i));
	}
	return number;
}

int getdigit(int num)
{
	int i = 0;
	while (num)
	{
		num /= 10;
		i++;
	}
	return i;
}

void getconv(int* a, int *b, int* w, int m, int n)
{
	int i, j;
	int k = m + n - 1;
	for (i = 0; i<k; i++)
		for (j = max(0, i + 1 - n); j <= min(i, m - 1); j++)
		{
			w[i] += a[j] * b[i - j];
		}
	//  return w;
}

//???
typedef struct Node
{
	ElemType num;
	ElemType en;
	char data[5];
	struct Node *next;
}Node;
typedef struct Node *LinkList;

//??????
Status InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(Node)); /* ?????,??L?????? */
	if (!(*L)) /* ?????? */
	{
		return ERROR;
	}
	(*L)->next = NULL; /* ????? */
	return OK;
}


void printLink(LinkList L)
{
	Node *p;
	p = L->next;
	while (p)
	{
		printf("%4d\n", p->num);
		p = p->next;
	}
}


// ????
void Destory(LinkList L)
{
	Node *p, *r;
	p = L->next;
	while (p)
	{
		r = p;
		p = p->next;
		free(r);
	}
	L->next = p;
}

//???????
LinkList CreateListHead(LinkList L, char* string_temp, int n1, int n2)
{
	LinkList p;
	p = (LinkList)malloc(sizeof(Node)); /*  ????? */
										//	p->data = string_temp;
	p->next = L->next;
	L->next = p;                      /*  ????? */
	strcpy(p->data, string_temp);
	p->num = n1;
	p->en = n2;
	return L;
}

//align
LinkList AlignList(LinkList L, int n)
{

	Node *p, *q;
	int i;
	p = L->next;
	q = p->next;
	while (p->next)
	{
		if (n)
		{
			for (i = 0; i < n; i++)
				//p->data[5 - 1 - n + i] = p->data[i];
				p->data[5 - 1 - 1 - i] = p->data[n - 1 - i];
			for (i = 0; i < 5 - 1 - n; i++)
				p->data[i] = q->data[n + i];
		}
		p->num = getnumber(p->data);
		p = p->next;
		q = q->next;
	}
	if (n)
	{
		for (i = n; i < 5 - 1; i++)
			p->data[i] = '\0';
	}
	p->num = getnumber(p->data);
	return L;
}

//add
LinkList add(LinkList L1, LinkList L2, LinkList L)
{
	Node *p, *q;
	int i, nu0 = 0, en0 = 0;
	p = L1->next;
	q = L2->next;
	while (p && q)
	{
		i = p->num + q->num + en0;
		nu0 = i % 10000;
		CreateListHead(L, "00", nu0, 0);
		en0 = i / 10000;
		p = p->next;
		q = q->next;
	}
	while (p)
	{
		i = p->num + en0;
		nu0 = i % 10000;
		CreateListHead(L, "00", nu0, 0);
		en0 = i / 10000;
		p = p->next;
	}
	while (q)
	{
		i = q->num + en0;
		nu0 = i % 10000;
		CreateListHead(L, "00", nu0, 0);
		en0 = i / 10000;
		q = q->next;
	}
	if (en0)
	{
		CreateListHead(L, "00", en0, 0);
	}
	return L;
}

//sub
LinkList sub(LinkList L1, LinkList L2, LinkList L)
{
	Node *p, *q, *r;
	LinkList p0, L_temp;
	int i, nu0 = 0, en0 = 0, flags = 0;
	p = L1->next;
	q = L2->next;
	r = L;
	while (p && q)
	{
		if (p->num >= q->num + en0)
		{
			nu0 = p->num - q->num - en0;
			en0 = 0;
		}
		else
		{
			nu0 = 10000 + p->num - q->num - en0;
			en0 = 1;
		}
		//	CreateListHead(L, "00", nu0, 0);
		p0 = (LinkList)malloc(sizeof(Node));
		p0->next = r->next;
		r->next = p0;
		strcpy(p0->data, "00");
		p0->num = nu0;
		p0->en = 0;
		r = r->next;
		p = p->next;
		q = q->next;
	}
	//printLink(L);
	while (p)
	{
		if (p->num >= en0)
		{
			nu0 = p->num - en0;
			en0 = 0;
		}
		else
		{
			nu0 = 10000 + p->num - en0;
			en0 = 1;
		}
		//	CreateListHead(L, "00", nu0, 0);
		p0 = (LinkList)malloc(sizeof(Node));
		p0->next = r->next;
		r->next = p0;                      /*  ????? */
		strcpy(p0->data, "00");
		p0->num = nu0;
		p0->en = 0;
		r = r->next;
		p = p->next;
	}
	while (q)
	{
		nu0 = 10000 - q->num - en0;
		en0 = 1;
		if (q->next)
			//	       CreateListHead(L, "00", nu0, 0);
		{
			p0 = (LinkList)malloc(sizeof(Node));
			p0->next = r->next;
			r->next = p0;
			strcpy(p0->data, "00");
			p0->num = nu0;
			p0->en = 0;
		}
		else
			//			CreateListHead(L, "00", nu0, 1);
		{
			p0 = (LinkList)malloc(sizeof(Node));
			p0->next = r->next;
			r->next = p0;
			strcpy(p0->data, "00");
			p0->num = nu0;
			p0->en = 1;
		}
		r = r->next;
		q = q->next;
		flags = 1;
	}
	if (en0)
	{
		nu0 = 10000 - en0;
		//	CreateListHead(L, "00", nu0, 1);
		p0 = (LinkList)malloc(sizeof(Node));
		p0->next = r->next;
		r->next = p0;
		strcpy(p0->data, "00");
		p0->num = nu0;
		p0->en = 1;
		flags = 1;
	}
	//	printLink(L);
	InitList(&L_temp);
	p = L->next;
	en0 = 0;
	while (p)
	{
		if (!flags)
		{
			CreateListHead(L_temp, "00", p->num, 0);
			p = p->next;
		}
		else
		{
			CreateListHead(L_temp, "00", 10000 - en0 - p->num, 0);
			en0 = 1;
			p = p->next;
		}
	}
	p = L_temp->next;
	while (!p->num && p->next)
	{
		p = p->next;
		L_temp->next = p;
	}
	return L_temp;
}


//multiply
LinkList mul(LinkList L1, LinkList L2, LinkList L)
{
	Node *p, *q, *r, *p_temp, *q_temp, *r_temp, *r_flag;
	LinkList p0, L_temp;
	int i, j, nu0 = 0, en0 = 0, flags = 0, cnt0 = 0, cnt = 0;
	int a[21] = { 0 }, b[21] = { 0 }, c[42 - 1] = { 0 }, d[21] = { 0 };
	p = L1->next;
	r_flag = L;
	while (p)
	{
		//p_temp = p;
		q = L2->next;
		r = r_flag;
		en0 = 0;
		for (i = 0; i < 21; i++)
		{
			a[i] = p->num;
			p = p->next;
			if (!p)
				break;
		}
		if (!p)
			cnt0 = i + 1;
		else
			cnt0 = i;
		while (q)
		{
			//		q_temp = q;
			//		r_temp = r;

			for (i = 0; i < 21; i++)
			{
				b[i] = q->num;
				q = q->next;
				if (!q)
					break;
			}
			if (!q)
				cnt = i + 1;
			else
				cnt = i;
			getconv(a, b, c, cnt0, cnt);
			for (i = 0; i < min(21, cnt0 + cnt - 1); i++)
			{

				//	CreateListHead(L, "00", nu0, 0);

				if (r->next)
				{
					p0 = r->next;
					nu0 = (c[i] + d[i] + en0 + p0->num) % 10000;
					en0 = (c[i] + d[i] + en0 + p0->num) / 10000;
					p0->num = nu0;

				}
				else
				{
					nu0 = (c[i] + d[i] + en0) % 10000;
					p0 = (LinkList)malloc(sizeof(Node));
					p0->next = r->next;
					r->next = p0;
					strcpy(p0->data, "00");
					p0->num = nu0;
					p0->en = 0;
					en0 = (c[i] + d[i] + en0) / 10000;
				}
				r = r->next;
			}
			for (i = 0; i < 21; i++)
			{
				b[i] = 0;
				d[i] = 0;
			}

			if (cnt0 + cnt - 1 > 21)
			{
				for (i = 0; i < min(20, cnt0 + cnt - 1 - 21); i++)
				{
					d[i] = c[21 + i];
				}
			}
			for (i = 0; i < 41; i++)
			{
				c[i] = 0;
			}

		}
		j = 0;
		while (d[j])
		{
			if (r->next)
			{
				p0 = r->next;
				nu0 = (d[j] + en0 + p0->num) % 10000;
				en0 = (d[j] + en0 + p0->num) / 10000;
				p0->num = nu0;

			}
			else
			{
				nu0 = (d[j] + en0) % 10000;
				p0 = (LinkList)malloc(sizeof(Node));
				p0->next = r->next;
				r->next = p0;
				strcpy(p0->data, "00");
				p0->num = nu0;
				p0->en = 0;
				en0 = (d[j] + en0) / 10000;
			}
			r = r->next;
			j = j + 1;
		}
		while (en0)
		{
			nu0 = en0 % 10000;
			p0 = (LinkList)malloc(sizeof(Node));
			p0->next = r->next;
			r->next = p0;
			strcpy(p0->data, "00");
			p0->num = nu0;
			p0->en = 0;
			en0 = en0 / 10000;
		}

		for (i = 0; i < cnt0; i++)
			r_flag = r_flag->next;
		for (i = 0; i < 21; i++)
		{
			a[i] = 0;
			d[i] = 0;
		}
		for (i = 0; i < 41; i++)
		{
			c[i] = 0;
		}
		//	printLink(L);
	}
	return L;
}

//division
LinkList getL_temp(int k, int n, LinkList L1, LinkList L2, LinkList *L3)
{
	LinkList L,L_mul,L_sub,L3_temp,p0;
	Node *p;
	InitList(&L);
	InitList(&L_mul);
	InitList(&L_sub);
	InitList(&L3_temp);
	int i, nu, n_temp=0, l1, l2, l1_l3, l2_l3, l3;
	int flags_err;
	l3 = getdigit(k);
	if (l3 != n)
	{
		l1 = n % 4;
		l2 = n / 4;
		l1_l3 = l3 % 4;
		l2_l3 = l3 / 4;
		if (l1 >= l1_l3)
		{
			k = k*pow(10, l1 - l1_l3);
			n_temp = l2 - l2_l3;
		}
		if (l1<l1_l3)
		{
			while (getdigit(k) + l1 + 4 - l1_l3>9)
			{
				k = k *6/ 7;
			//	k = 2*pow(10, getdigit(k)  - 1);
			}
			k = k*pow(10, l1 + 4 - l1_l3);
			n_temp = l2 - l2_l3 - 1;
		}
	}
	p = L;
//	printf("%d\n",k);
	if (k == 1919)
	{
		flags_err = 0;
	}
	while (k)
	{
		nu = k % 10000;
	//	L=CreateListHead(L, "00", nu, 0);
		p0 = (LinkList)malloc(sizeof(Node));
		p0->next = p->next;
		p->next = p0;
		strcpy(p0->data, "00");
		p0->num = nu;
		p0->en = 0;
		k = k / 10000;
		p = p->next;
	}
	/*
	k = k*pow(10, n - l3);
	while (k)
	{
		nu = k % 10000;
	//	L = CreateListHead(L, "00", nu, 0);
		k = k / 10000;
	}
	*/
	L_mul = mul(L, L2, L_mul);
	
	while (n_temp)
	{
		L_mul = CreateListHead(L_mul, "00", 0, 0);
		L= CreateListHead(L, "00", 0, 0);
		n_temp = n_temp - 1;
	}
	L_sub = sub(L1, L_mul, L_sub);
	*L3 = add(*L3, L, L3_temp);
//	printLink(L1);
//	printLink(L_mul);
//	printLink(L_sub);
	return L_sub;
}





int main()
{
	clock_t start, end;
	int i, j = 0, k;
	int digit[2][2] = { 0 };
	char op, string_temp[5];
	char top1, top2;
	char mystring[5], mystring_temp[5];
//	FILE *ft;
	LinkList L1, L2, L, L_temp, L1_temp, L2_temp;

	InitList(&L1);
	InitList(&L2);
	InitList(&L);
	int flags = 1;
	int nu1, nu2;
	while (!digit[1][1])
	{
		
		//getchar()
	//	fgets(mystring, 5, ft);
		if (strstr(mystring, "+") == NULL && strstr(mystring, "-") == NULL && strstr(mystring, "*") == NULL && strstr(mystring, "/") == NULL)
		{
			while (mystring != NULL)
			{
				//			puts(mystring);
				if (strstr(mystring, "\n") == NULL && strlen(mystring) == 5 - 1)
				{
					//	strcpy(string_temp, mystring);
					if (flags == 1)
					{
						L1 = CreateListHead(L1, mystring, 0, 0);
						digit[0][0] = digit[0][0] + 1;
					}
					else
					{
						L2 = CreateListHead(L2, mystring, 0, 0);
						digit[1][0] = digit[1][0] + 1;
					}
				}
				else
				{
					if (flags == 1)
					{
						if (strlen(mystring) == 1)
							digit[0][1] = 0;
						else
						{
							L1 = CreateListHead(L1, mystring, 0, 0);
							digit[0][1] = strlen(mystring) - 1;
						}
					}
					flags = 2;
				}
				if (feof(ft))
					break;
				else {
					fgets(mystring, 5, ft);
					if (feof(ft))
					{
						digit[1][1] = strlen(mystring);
						if (digit[1][1] == 4)
							digit[1][1] = 0;
						else
						{
							L2 = CreateListHead(L2, mystring, 0, 0);
						}
						break;
					}
				}
			}
			if (feof(ft))
				break;
		}
		else
		{
			op = mystring[0];
			//	putchar(op);
			putchar('\n');
		}
	}










	/*
	ft = fopen("C:\\Users\\v-xiafe\\Desktop\\ASE\\project (1)\\ConsoleApplication3\\Release\\test.txt", "r");
	if (ft == NULL)
	{
		printf("File Name Error.\n");
		return 0;
	}
	InitList(&L1);
	InitList(&L2);
	InitList(&L);
	int flags = 1;
	int nu1, nu2;
	while (!digit[1][1])
	{
		fgets(mystring, 5, ft);
		if (strstr(mystring, "+") == NULL && strstr(mystring, "-") == NULL && strstr(mystring, "*") == NULL && strstr(mystring, "/") == NULL)
		{
			while (mystring != NULL)
			{
				//			puts(mystring);
				if (strstr(mystring, "\n") == NULL && strlen(mystring) == 5 - 1)
				{
					//	strcpy(string_temp, mystring);
					if (flags == 1)
					{
						L1 = CreateListHead(L1, mystring, 0, 0);
						digit[0][0] = digit[0][0] + 1;
					}
					else
					{
						L2 = CreateListHead(L2, mystring, 0, 0);
						digit[1][0] = digit[1][0] + 1;
					}
				}
				else
				{
					if (flags == 1)
					{
						if (strlen(mystring) == 1)
							digit[0][1] = 0;
						else
						{
							L1 = CreateListHead(L1, mystring, 0, 0);
							digit[0][1] = strlen(mystring) - 1;
						}
					}
					flags = 2;
				}
				if (feof(ft))
					break;
				else {
					fgets(mystring, 5, ft);
					if (feof(ft))
					{
						digit[1][1] = strlen(mystring);
						if (digit[1][1] == 4)
							digit[1][1] = 0;
						else
						{
							L2 = CreateListHead(L2, mystring, 0, 0);
						}
						break;
					}
				}
			}
			if (feof(ft))
				break;
		}
		else
		{
			op = mystring[0];
			//	putchar(op);
			putchar('\n');
		}
	}
	fclose(ft);
	*/

	L1 = AlignList(L1, digit[0][1]);
	L2 = AlignList(L2, digit[1][1]);
	if (op == '/')
	{
	//	InitList(&L1_temp);
	//	InitList(&L2_temp);
		Node *p, *q, *p0;
		p = L1->next;
		q = L2->next;
		while (p->next)
		{
			nu1 = p->num;
			p = p->next;
		}
		nu1 = 10000 * p->num + nu1;
		while (q)
		{
			nu2 = q->num;
			q = q->next;
		}
	}
	op = '*';
	switch (op)
	{
	case '+':
		L_temp = add(L1, L2, L);
		printLink(L_temp);
		break;
	case '-':
		L_temp = sub(L2, L1, L);
		printLink(L_temp);
		break;
	case '*':
		start = clock();
		L_temp = mul(L1, L2, L);
		end = clock();
		printLink(L_temp);
		printf("%d", (end - start) / CLOCKS_PER_SEC);
		break;
	case '/':
	{
		int n, k,cn_temp;
		Node *p,*q;
		LinkList p0,L_subrev,L1_temp1,L3,L3_temp;
		InitList(&L_subrev);
		InitList(&L3);
		InitList(&L3_temp);
		L1_temp1 = L1;
	//	n = digit[0][0] * 4 + digit[0][1] - digit[1][0] * 4 - digit[1][1];
	//	int record[n][2];
		start = clock();
		while (1)
		{
			n = digit[0][0] * 4 + digit[0][1] - digit[1][0] * 4 - digit[1][1];
			printf("%dwei\n", digit[0][0] * 4 + digit[0][1]);
			digit[0][0] = 0;
			digit[0][1] = 0;
			if (n<0)
			{
			//	printLink(L3);
			//	printLink(L1_temp1);
				break;
			}
			else
			{
				k = nu1 / (nu2 + 1);
				cn_temp = pow(10, getdigit(nu1) - getdigit(nu2));
		//		printf("%d",cn_temp);
					if (nu1 / cn_temp > nu2)
						n = n + 1;
					else
					{
						if (n == 0)
						{
				//			printLink(L3);
				//			printLink(L1_temp1);
							break;
						}
					}
				if (getdigit(k) > n)
					k = k / pow(10, getdigit(k) - n);
				L_temp = getL_temp(k, n, L1_temp1, L2,&L3);
		//		printLink(L_temp);
				p = L_temp->next;
				q = L3->next;
				digit[0][1] = getdigit(p->num);
				Destory(L_subrev);
				Destory(L3_temp);
				nu1 = 0;
				while (p->next)
				{
					L_subrev = CreateListHead(L_subrev, "00", p->num, 0);
				//	nu1 = p->num;
					digit[0][0] = digit[0][0] + 1;
					p = p->next;
				}
				L_subrev = CreateListHead(L_subrev, "00", p->num, 0);
				while(q)
				{
					L3_temp = CreateListHead(L3_temp, "00", q->num, 0);
					q = q->next;
				}
				L3 = L3_temp;
				p = L_temp->next;
				nu1 = p->num;
				if (p->next)
				{
					p = p->next;
					nu1 = 10000 * nu1 + p->num;
				}

		//		Destory(L1_temp1);
		//		Destory(L1_temp);
				L1_temp1 = L_subrev;

			}
		//	Destory(L_subrev);
		}
		end = clock();
	//	printLink(L3);
	//	printLink(L1_temp1);
		printf("%d s", (end - start) / CLOCKS_PER_SEC);
	}
	}
	return 0;
}