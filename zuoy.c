#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu()
{
	printf("#############################\n");
	printf("######## 1.开始游戏  ########\n");
	printf("######## 0.退出游戏  ########\n");
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
		printf("请输入你猜的数字\n");
		scanf_s("%d", &c);
		if (c > ret)
		{
			printf("猜大了，请再猜一次\n");
		}
		else if (c < ret)
		{
			printf("猜小了，请再猜一次\n");
		}
		else
		{
			printf("你真棒，猜对了\n");
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
		printf("请根据菜单输入数字");
		scanf_s("%d", &input);
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			break;
		default:
			printf("选择错误，请根据菜单输入数字");
			break;
		}
	} while (input);
	return 0;
}