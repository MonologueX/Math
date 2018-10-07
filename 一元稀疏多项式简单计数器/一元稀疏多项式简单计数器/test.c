#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include <windows.h>
#include<malloc.h>

typedef struct Polyomial
{
	float coef;
	int expn;
	struct Polyomial *next;
}*Poly, Polyomial;               //Poly为结点指针类型

void Insert(Poly p, Poly h)
{
	if (p->coef == 0) free(p);       //系数为0时释放结点
	else{
		Poly q1, q2;
		q1 = h; q2 = h->next;
		while (q2&&p->expn<q2->expn)
		{   //查找插入位置
			q1 = q2;
			q2 = q2->next;
		}
		if (q2&&p->expn == q2->expn)
		{   //将指数相同相合并
			q2->coef += p->coef;
			free(p);
			if (!q2->coef)
			{   //系数为0的话释放结点
				q1->next = q2->next;
				free(q2);
			}
		}
		else
		{   //指数为新时将结点插入
			p->next = q2;
			q1->next = p;
		}
	}
}

Poly CreatePoly(Poly head, int m)
{   
	//建立一个头指针为head、项数为m的一元多项式
	int i;
	Poly p;
	p = head = (Poly)malloc(sizeof(struct Polyomial));
	head->next = NULL;
	for (i = 0; i<m; i++)
	{
		p = (Poly)malloc(sizeof(struct Polyomial));//建立新结点以接收数据
		printf("\t\t\t输入第%d项的系数与指数:", i + 1);
		scanf("%f %d", &p->coef, &p->expn);
		Insert(p, head);   //调用Insert函数插入结点
	}
	return head;
}

void DestroyPoly(Poly p)
{   
	
	//销毁多项式p
	Poly q1, q2;
	
	q1 = p->next;
	q2 = q1->next;
	while (q1->next)
	{
		free(q1);
		q1 = q2;//指针后移
		q2 = q2->next;
	}
}

void PrintPoly(Poly P)
{
	Poly q = P->next;
	int flag = 1;//项数计数器
	if (!q)
	{   
		//若多项式为空，输出0
		putchar('0');
		printf("\n");
		return;
	}
	while (q)
	{
		if (q->coef>0 && flag != 1) 
			putchar('+'); //系数大于0且不是第一项
		if (q->coef != 1 && q->coef != -1){//系数非1或-1的普通情况
			printf("%g", q->coef);
			if (q->expn == 1) 
				putchar('X');
			else if (q->expn) 
				printf("X^%d", q->expn);
		}
		else
		{
			if (q->coef == 1)
			{
				if (!q->expn) putchar('1');
				else if (q->expn == 1) 
					putchar('X');
				else 
					printf("X^%d", q->expn);
			}
			if (q->coef == -1){
				if (!q->expn) 
					printf("-1");
				else if (q->expn == 1) 
					printf("-X");
				else printf("-X^%d", q->expn);
			}
		}
		q = q->next;
		flag++;
	}
	printf("\n");
}

int compare(Poly a, Poly b)
{
	if (a&&b)
	{
		if (!b || a->expn>b->expn) return 1;
		else if (!a || a->expn<b->expn) return -1;
		else return 0;
	}
	else if (!a&&b) return -1;//a多项式已空，但b多项式非空
	else return 1;//b多项式已空，但a多项式非空
}

Poly AddPoly(Poly pa, Poly pb)
{   
	//求解并建立多项式a+b，返回其头指针
	Poly qa = pa->next;
	Poly qb = pb->next;
	Poly headc, hc, qc;
	hc = (Poly)malloc(sizeof(struct Polyomial));//建立头结点
	hc->next = NULL;
	headc = hc;
	while (qa || qb)
	{
		qc = (Poly)malloc(sizeof(struct Polyomial));
		switch (compare(qa, qb))
		{
		case 1:
		{
				  qc->coef = qa->coef;
				  qc->expn = qa->expn;
				  qa = qa->next;
				  break;
		}
		case 0:
		{
				  qc->coef = qa->coef + qb->coef;
				  qc->expn = qa->expn;
				  qa = qa->next;
				  qb = qb->next;
				  break;
		}
		case -1:
		{
				   qc->coef = qb->coef;
				   qc->expn = qb->expn;
				   qb = qb->next;
				   break;
		}
		}
		if (qc->coef != 0){
			qc->next = hc->next;
			hc->next = qc;
			hc = qc;
		}
		else free(qc);//当相加系数为0时，释放该结点
	}
	return headc;
}

Poly SubtractPoly(Poly pa, Poly pb)
{   
	//求解并建立多项式a-b，返回其头指针
	Poly h = pb;
	Poly p = pb->next;
	Poly pd;
	while (p)
	{   
		//将pb的系数取反
		p->coef *= -1;
		p = p->next;
	}
	pd = AddPoly(pa, h);
	for (p = h->next; p; p = p->next)    //恢复pb的系数
		p->coef *= -1;
	return pd;
}

void welcome()  //输入密钥进入程序，欢迎函数 
{
	char password[5];
	char num[5];
	strcpy(num, "2018");
loopback3:printf(" \n\n\n\n\n\n\n\n");
	//0 = 黑色      8 = 灰色   1 = 蓝色      9 = 淡蓝色   2 = 绿色      A = 淡绿色   3 = 湖蓝色    B = 淡浅绿色   4 = 红色      
	//C = 淡红色   5 = 紫色      D = 淡紫色   6 = 黄色      E = 淡黄色   7 = 白色      F = 亮白色
	system("color b2");
	printf("\t\t\t欢迎使一元稀疏多项式简单计数器！\n");
	
	printf("\t\t\t\t请输入密码:");
	scanf("%s", &password);
	if (strcmp(password, num) == 0)
	{
		system("cls");
		
		Sleep(300);
	}

	else
	{
		printf("\t\t\t\t 密码错误!");
		//密码错误重新输出 
		Sleep(2000);
		system("cls");
		goto loopback3;
	}
}

void menu()
{
	printf("\n\n\n\n\t\t==============欢迎使一元稀疏多项式简单计数器==============\n");
	printf("\t\t\t=======请选择功能列表=======\n");
	printf("\t\t\t\t1.输入并建立多项式：\n");
	printf("\t\t\t\t2.输出多项式\n");
	printf("\t\t\t\t3.输出多项式a+b\n");
	printf("\t\t\t\t4.输出多项式a-b\n");
	printf("\t\t\t\t0.退出系统\n");
}

int main()
{
	welcome();
	int m, n = 0;
	Poly pa = 0, pb = 0, pc, pd, pe, pf;//定义各式的头指针，pa与pb在使用前初值NULL

	while (1)
	{
		system("cls");
		menu();
		char sh;
		char ch;
		ch = _getch();
		switch (ch)
		{
		case '1'://录入商品信息
			system("cls");
			printf("\n\n\n\n\t\t\t输入a的项数:");
			scanf("%d", &m);
			pa = CreatePoly(pa, m);//建立多项式a
			printf("\n");
			printf("\t\t\t输入b的项数:");
			scanf("%d", &n);
			pb = CreatePoly(pb, n);//建立多项式b
			printf("\n\t\t\t按任意键返回上一级！");
			sh = _getch();
			break;
		case '2':
			system("cls");
			printf("\n\n\n\n\t\t\t多项式a："); 
			PrintPoly(pa);
			printf("\t\t\t多项式b："); 
			PrintPoly(pb);
			printf("\n\t\t\t按任意键返回上一级！");
			sh = _getch();
			break;
		case '3':
			system("cls");
			pc = AddPoly(pa, pb);
			printf("\n\n\n\n\t\t\t输出多项式a+b:");
			PrintPoly(pc);
			DestroyPoly(pc);
			printf("\n\t\t\t按任意键返回上一级！");
			sh = _getch();
			break;
		case '4':
			system("cls");
			pd = SubtractPoly(pa, pb);
			printf("\n\n\n\n\t\t\t输出多项式a-b:");
			PrintPoly(pd);
			DestroyPoly(pd);
			printf("\n\t\t\t按任意键返回上一级！");
			sh = _getch();
			break;
		case '0':
			DestroyPoly(pa);
			DestroyPoly(pb);
			system("cls");
			printf("\n\n\n\n\t\t\t欢迎再次使用！\n");
			Sleep(30000);
			return 0;
			break;
		default:
			system("cls");
			printf("\n\n\n\n\t\t\t您的输入有误，请重新输入！\n");
			Sleep(3000);
			break;
		}
	}
	system("pause");
	return 0;
}h