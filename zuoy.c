#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu()
{
	printf("#############################\n");
	printf("######## 1.��ʼ��Ϸ  ########\n");
	printf("######## 0.�˳���Ϸ  ########\n");
	printf("#############################\n");
}

void game()
{
	int c = 0;
	int ret = 0;
	ret = rand() % 100;
	//printf("%d\n",ret);
	while (1)
	{
		printf("��������µ�����\n");
		scanf_s("%d", &c);
		if (c > ret)
		{
			printf("�´��ˣ����ٲ�һ��\n");
		}
		else if (c < ret)
		{
			printf("��С�ˣ����ٲ�һ��\n");
		}
		else
		{
			printf("��������¶���\n");
			break;
		}
	}
}

int main()
{
	int input = 0;
	srand((unsigned)time(NULL));
	do
	{
		menu();
		printf("����ݲ˵���������");
		scanf_s("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			break;
		default:
			printf("ѡ���������ݲ˵���������");
			break;
		}
	} while (input);
	return 0;
}