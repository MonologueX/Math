#include<stdio.h>

int main()
{
	int ch = 0;
	
	while ((ch=getchar()) != EOF)
	{
		if (ch >= 'A'&&ch <= 'Z')
		{
			printf("ch=%c\n", ch + 32);
		}
		else if (ch >= 'a'&&ch <= 'z')
		{
			printf("ch=%c\n", ch - 32);
		}
	}
	system("pause");
	return 0;
}
