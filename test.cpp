#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct tagGoods
{
	char prName[10];		//����
	int nNumber;			//���
	int nPrice;				//�۸�
}Goods;

typedef struct tagNode
{
	Goods good;			//��Ʒ��Ϣ
	struct tagNode* pNext;	//ָ����һ����Ʒ
}Node;

Node *g_pHead = NULL;			//�����һ����Ʒ

//¼����Ʒ��Ϣ
void InputGoods();
//��ӡ��Ʒ��Ϣ
void PrintGoods();
//������Ʒ��Ϣ
void SaveGoods();
//��ȡѧԱ��Ϣ
void ReadGoods();
//ͳ��������Ʒ����
int CountGoods();
//������Ʒ��Ϣ
Node* FindGoods();
//�޸�ĳ����Ʒ����Ϣ
void ModifyGoods();
//ɾ����Ʒ��Ϣ
void DeleteGoods();

int main()
{
	while (1)
	{
		printf("==============��ӭʹ�ø�У��Ʒ�۸����ϵͳV1.0==============\n");
		printf("\t=======��ѡ�����б�=======\n");
		printf("\t\t1.¼����Ʒ��Ϣ\n");
		printf("\t\t2.��ӡ��Ʒ��Ϣ\n");
		printf("\t\t3.������Ʒ��Ϣ\n");
		printf("\t\t4.��ȡ��Ʒ��Ϣ\n");
		printf("\t\t5.ͳ��������Ʒ����\n");
		printf("\t\t6.������Ʒ��Ϣ\n");
		printf("\t\t7.�޸���Ʒ��Ϣ\n");
		printf("\t\t8.ɾ����Ʒ��Ϣ\n");
		printf("\t\t0.�˳�ϵͳ\n");

		char ch;

		ch = _getch();

		switch (ch)
		{
		case '1'://¼����Ʒ��Ϣ
			InputGoods();
			break;
		case '2'://��ӡ��Ʒ��Ϣ
			PrintGoods();
			break;
		case '3'://������Ʒ��Ϣ
			SaveGoods();
			break;
		case '4'://��ȡѧԱ��Ϣ
			ReadGoods();
			break;
		case '5'://ͳ��������Ʒ����
			printf("��ǰ��Ʒ������Ϊ:%d\n", CountGoods());
			break;
		case '6'://������Ʒ��Ϣ
		{
					 Node *pNode = FindGoods();
					 if (pNode != NULL)
					 {
						 printf("���:%d\t����:%s\t�۸�:%d\n", pNode->good.nNumber, pNode->good.prName, pNode->good.nPrice);
					 }
					 break;
		}
		case '7'://�޸�ĳ����Ʒ����Ϣ
			ModifyGoods();
			break;
		case '8'://ɾ����Ʒ��Ϣ
			DeleteGoods();
			break;
		case '0':
			printf("��ӭ�ٴ�ʹ�ã�\n");
			return 0;
			break;
		default:
			printf("���������������������룡\n");
			break;
		}
	}
	return 0;
}

//¼����Ʒ��Ϣ
void InputGoods()
{
	printf("\n��������Ʒ��Ϣ:��� ���� �۸�\n");

	Node* p;
	p = g_pHead;
	while (g_pHead != NULL && p->pNext != NULL)
	{
		p = p->pNext;
	}

	//Ϊ�µ���Ʒ����һ���ռ�
	Node* pNewNode = (Node*)malloc(sizeof(Node));
	pNewNode->pNext = NULL;

	if (g_pHead == NULL)
	{
		g_pHead = pNewNode;
		p = g_pHead;
	}
	else
	{
		p->pNext = pNewNode;//p����һ���ڵ�ΪpNewNode
	}

	//�����µ���Ʒ����
	scanf("%d %s %d", &pNewNode->good.nNumber, pNewNode->good.prName, &pNewNode->good.nPrice);

	system("cls");
	printf("\n������ӳɹ�....\n");

}



//��ӡ��Ʒ��Ϣ
void PrintGoods()
{
	system("cls");
	printf("��ӡ������Ʒ��Ϣ\n");

	Node* p;
	p = g_pHead;

	while (p != NULL)
	{
		printf("���:%d\t����:%s\t�۸�:%d\n",
			p->good.nNumber,
			p->good.prName,
			p->good.nPrice);

		p = p->pNext;
	}
}

//������Ʒ��Ϣ
void SaveGoods()
{
	system("cls");

	FILE *pFile = fopen("goodinfo.data", "w");
	if (pFile == 0)
	{
		printf("���ļ�ʧ��\n");
		return;
	}
	//д������
	Node *p;
	p = g_pHead;
	while (p != NULL)
	{
		fprintf(pFile, "%d %s %d\n", p->good.nNumber, p->good.prName, p->good.nPrice);

		p = p->pNext;
	}
	printf("���ݱ���ɹ�\n");
	//�ر��ļ�
	fclose(pFile);
}

//��ȡѧԱ��Ϣ
void ReadGoods()
{
	system("cls");
	//����ɾ���������ݣ�Ȼ����ļ��ж�ȡ����
	Node *p, *p2;
	p = p2 = g_pHead;

	while (p2 != NULL)
	{
		//���ɾ�������е�����
		p = p->pNext;
		free(p2);
		p2 = p;
	}

	g_pHead = NULL;

	//���ļ�
	FILE *pFile = fopen("goodinfo.data", "r");

	if (pFile == 0)
	{
		printf("���ļ�ʧ��\n");
		return;
	}

	//��ȡ����
	while (!feof(pFile))
	{
		//����ռ��Դ洢����
		Node *pTemp = (Node*)malloc(sizeof(Node));
		//���ļ��ж�ȡ
		fscanf(pFile, "%d %s %d\n", &pTemp->good.nNumber, &pTemp->good.prName, &pTemp->good.nPrice);

		//��������
		if (g_pHead == NULL)
		{
			g_pHead = pTemp;
			p = g_pHead;
		}
		else
		{
			p->pNext = pTemp;//p����һ���ڵ�Ϊtemp
			p = p->pNext;
			p->pNext = NULL;
		}
	}

	//�ر��ļ�
	fclose(pFile);
}

//ͳ��������Ʒ����
int CountGoods()
{
	system("cls");
	int nCount = 0;

	//�Ȱ��ļ��е����ݶ�ȡ��������
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

//������Ʒ��Ϣ
Node* FindGoods()
{
	system("cls");
	int nNumber;
	printf("������Ҫ���ҵ���Ʒ�����:\n");

	scanf("%d", &nNumber);

	//�ȴ��ļ��ж�ȡ��������
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

	//����������Ҳû���ҵ���Ϣ
	if (p == NULL)
	{
		printf("û�и���Ʒ����Ϣ\n");
		return NULL;
	}

	return NULL;
}

//�޸�ĳ����Ʒ����Ϣ
void ModifyGoods()
{
	system("cls");
	int nNumber;
	printf("������Ҫ�޸���Ʒ��Ϣ�����:\n");
	scanf("%d", &nNumber);

	//�Ȱ��ļ��е����ݶ�ȡ��������
	ReadGoods();

	Node* p;
	p = g_pHead;

	while (p != NULL)
	{
		if (p->good.nNumber == nNumber)
		{
			printf("������Ҫ�޸ĵ���Ϣ����� ���� �۸�\n");
			scanf("%d %s %d", &p->good.nNumber, p->good.prName, &p->good.nPrice);
			printf("�޸ĳɹ�!\n");
			break;
		}

		p = p->pNext;
	}

	if (p == NULL)
	{
		printf("û�и���Ʒ��Ϣ!\n");
	}
}

//ɾ����Ʒ��Ϣ
void DeleteGoods()
{
	system("cls");
	int nNumber;
	printf("������Ҫɾ����Ʒ��Ϣ�����:\n");

	scanf("%d", &nNumber);
	//�Ȱ��ļ��е����ݶ�ȡ������
	ReadGoods();

	Node *p, *p2;

	p = g_pHead;
	//�ж��Ƿ���ͷ���
	if (g_pHead->good.nNumber == nNumber)
	{
		p2 = g_pHead;
		g_pHead = g_pHead->pNext;//ͷָ��ָ��ɾ��Ԫ�غ����Ԫ��
		free(p2);//�ͷŽڵ�
		return;
	}
	//����ͷ���

	while (p->pNext != NULL)
	{
		if (p->pNext->good.nNumber == nNumber)
		{
			p2 = p->pNext;
			p->pNext = p->pNext->pNext;//ɾ���ýڵ�ָ�������˽ڵ�
			free(p2);
			return;
		}

		p = p->pNext;//ָ����һ���ڵ�
		if (p->pNext == NULL)
		{
			//�ж��Ƿ�������Ľ�β
			break;
		}
	}

	if (p->pNext == NULL)
	{
		printf("û�и���Ʒ��Ϣ\n");
	}
}