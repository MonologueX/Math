#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct tagGoods
{
	char prName[10];		//名称
	int nNumber;			//序号
	int nPrice;				//价格
}Goods;

typedef struct tagNode
{
	Goods good;			//商品信息
	struct tagNode* pNext;	//指向下一个商品
}Node;

Node *g_pHead = NULL;			//定义第一个商品

//录入商品信息
void InputGoods();
//打印商品信息
void PrintGoods();
//保存商品信息
void SaveGoods();
//读取学员信息
void ReadGoods();
//统计所有商品数量
int CountGoods();
//查找商品信息
Node* FindGoods();
//修改某个商品的信息
void ModifyGoods();
//删除商品信息
void DeleteGoods();

int main()
{
	while (1)
	{
		printf("==============欢迎使用高校商品价格管理系统V1.0==============\n");
		printf("\t=======请选择功能列表=======\n");
		printf("\t\t1.录入商品信息\n");
		printf("\t\t2.打印商品信息\n");
		printf("\t\t3.保存商品信息\n");
		printf("\t\t4.读取商品信息\n");
		printf("\t\t5.统计所有商品数量\n");
		printf("\t\t6.查找商品信息\n");
		printf("\t\t7.修改商品信息\n");
		printf("\t\t8.删除商品信息\n");
		printf("\t\t0.退出系统\n");

		char ch;

		ch = _getch();

		switch (ch)
		{
		case '1'://录入商品信息
			InputGoods();
			break;
		case '2'://打印商品信息
			PrintGoods();
			break;
		case '3'://保存商品信息
			SaveGoods();
			break;
		case '4'://读取学员信息
			ReadGoods();
			break;
		case '5'://统计所有商品数量
			printf("当前商品总数量为:%d\n", CountGoods());
			break;
		case '6'://查找商品信息
		{
					 Node *pNode = FindGoods();
					 if (pNode != NULL)
					 {
						 printf("序号:%d\t名称:%s\t价格:%d\n", pNode->good.nNumber, pNode->good.prName, pNode->good.nPrice);
					 }
					 break;
		}
		case '7'://修改某个商品的信息
			ModifyGoods();
			break;
		case '8'://删除商品信息
			DeleteGoods();
			break;
		case '0':
			printf("欢迎再次使用！\n");
			return 0;
			break;
		default:
			printf("您的输入有误，请重新输入！\n");
			break;
		}
	}
	return 0;
}

//录入商品信息
void InputGoods()
{
	printf("\n请输入商品信息:序号 名称 价格\n");

	Node* p;
	p = g_pHead;
	while (g_pHead != NULL && p->pNext != NULL)
	{
		p = p->pNext;
	}

	//为新的商品分配一个空间
	Node* pNewNode = (Node*)malloc(sizeof(Node));
	pNewNode->pNext = NULL;

	if (g_pHead == NULL)
	{
		g_pHead = pNewNode;
		p = g_pHead;
	}
	else
	{
		p->pNext = pNewNode;//p的下一个节点为pNewNode
	}

	//输入新的商品数据
	scanf("%d %s %d", &pNewNode->good.nNumber, pNewNode->good.prName, &pNewNode->good.nPrice);

	system("cls");
	printf("\n数据添加成功....\n");

}



//打印商品信息
void PrintGoods()
{
	system("cls");
	printf("打印所有商品信息\n");

	Node* p;
	p = g_pHead;

	while (p != NULL)
	{
		printf("序号:%d\t名称:%s\t价格:%d\n",
			p->good.nNumber,
			p->good.prName,
			p->good.nPrice);

		p = p->pNext;
	}
}

//保存商品信息
void SaveGoods()
{
	system("cls");

	FILE *pFile = fopen("goodinfo.data", "w");
	if (pFile == 0)
	{
		printf("打开文件失败\n");
		return;
	}
	//写入数据
	Node *p;
	p = g_pHead;
	while (p != NULL)
	{
		fprintf(pFile, "%d %s %d\n", p->good.nNumber, p->good.prName, p->good.nPrice);

		p = p->pNext;
	}
	printf("数据保存成功\n");
	//关闭文件
	fclose(pFile);
}

//读取学员信息
void ReadGoods()
{
	system("cls");
	//首先删除链表数据，然后从文件中读取数据
	Node *p, *p2;
	p = p2 = g_pHead;

	while (p2 != NULL)
	{
		//卒个删除链表中的数据
		p = p->pNext;
		free(p2);
		p2 = p;
	}

	g_pHead = NULL;

	//打开文件
	FILE *pFile = fopen("goodinfo.data", "r");

	if (pFile == 0)
	{
		printf("打开文件失败\n");
		return;
	}

	//读取数据
	while (!feof(pFile))
	{
		//分配空间以存储数据
		Node *pTemp = (Node*)malloc(sizeof(Node));
		//从文件中读取
		fscanf(pFile, "%d %s %d\n", &pTemp->good.nNumber, &pTemp->good.prName, &pTemp->good.nPrice);

		//创建链表
		if (g_pHead == NULL)
		{
			g_pHead = pTemp;
			p = g_pHead;
		}
		else
		{
			p->pNext = pTemp;//p的下一个节点为temp
			p = p->pNext;
			p->pNext = NULL;
		}
	}

	//关闭文件
	fclose(pFile);
}

//统计所有商品数量
int CountGoods()
{
	system("cls");
	int nCount = 0;

	//先把文件中的数据读取到链表中
	ReadGoods();

	Node *p;
	p = g_pHead;

	while (p != NULL)
	{
		nCount++;
		p = p->pNext;
	}

	return nCount;
}

//查找商品信息
Node* FindGoods()
{
	system("cls");
	int nNumber;
	printf("请输入要查找的商品的序号:\n");

	scanf("%d", &nNumber);

	//先从文件中读取到链表中
	ReadGoods();
	Node* p;
	p = g_pHead;
	while (p != NULL)
	{
		if (p->good.nNumber == nNumber)
		{
			return p;
		}

		p = p->pNext;
	}

	//遍历完链表也没有找到信息
	if (p == NULL)
	{
		printf("没有该商品的信息\n");
		return NULL;
	}

	return NULL;
}

//修改某个商品的信息
void ModifyGoods()
{
	system("cls");
	int nNumber;
	printf("请输入要修改商品信息的序号:\n");
	scanf("%d", &nNumber);

	//先把文件中的数据读取到链表中
	ReadGoods();

	Node* p;
	p = g_pHead;

	while (p != NULL)
	{
		if (p->good.nNumber == nNumber)
		{
			printf("请输入要修改的信息：序号 名称 价格\n");
			scanf("%d %s %d", &p->good.nNumber, p->good.prName, &p->good.nPrice);
			printf("修改成功!\n");
			break;
		}

		p = p->pNext;
	}

	if (p == NULL)
	{
		printf("没有该商品信息!\n");
	}
}

//删除商品信息
void DeleteGoods()
{
	system("cls");
	int nNumber;
	printf("请输入要删除商品信息的序号:\n");

	scanf("%d", &nNumber);
	//先把文件中的数据读取到链表
	ReadGoods();

	Node *p, *p2;

	p = g_pHead;
	//判断是否是头结点
	if (g_pHead->good.nNumber == nNumber)
	{
		p2 = g_pHead;
		g_pHead = g_pHead->pNext;//头指针指向删除元素后的首元素
		free(p2);//释放节点
		return;
	}
	//不是头结点

	while (p->pNext != NULL)
	{
		if (p->pNext->good.nNumber == nNumber)
		{
			p2 = p->pNext;
			p->pNext = p->pNext->pNext;//删除该节点指针跳过此节点
			free(p2);
			return;
		}

		p = p->pNext;//指向下一个节点
		if (p->pNext == NULL)
		{
			//判断是否到了链表的结尾
			break;
		}
	}

	if (p->pNext == NULL)
	{
		printf("没有该商品信息\n");
	}
}