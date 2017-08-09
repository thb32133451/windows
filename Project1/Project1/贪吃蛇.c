#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

#define LONG 2870  //���鳤��
#define ROW 70  //���
#define U 72
#define D 80
#define L 75
#define R 77

int tcs[LONG]; //̰����
int Key = 75;  //��¼�ϴ�����(��ʼ��Ϊ��)
int x, y;  //����
int lenth = 6;  //��ʼ�߳�Ϊ6

x = 21;  //��ʼ������ʼλ��
y = 33;

int isbump(void);  //��ײ��ײǽor�Ե���
int tuichu(void);  //��Ϸ����
int Up(void);
int Down(void);
int Left(void);
int Right(void);
int Printf(void);  //��Ļ��ӡ
int shuru(void);

int main(void)
{
	int i;
	int bool = 0;

	for (i = 0; i < LONG; i++)  //��ʼ������
	{
		if (i % ROW == ROW - 1 || i % ROW == 0)  //����ǽ��
			tcs[i] = '|';
		else if (i > 0 && i < ROW - 1)  //��ǽ��
			tcs[i] = '*';
		else if (i > LONG - ROW && i < LONG - 1)  //��ǽ��
			tcs[i] = '*';
		else if (i >= x*ROW + y + 1 && i <= x*ROW + y + lenth + 1)  //����
			tcs[i] = '*';
		else
			tcs[i] = 0;
	}

	for (i = 1; i <= lenth; i++)  //��ʼ�켣
	{
		tcs[x*ROW + y + i - 1] = i;
	}

	Printf();  //��ӡ


	while (1)
	{
		bool = isbump();
		if (bool != 1)

			break;
		else
		{
			shuru();
		}
	}



	getchar();
	return 0;
}

int tuichu(void)
{
	printf("��Ϸ�����������˻����˵���\n");
	return 0;
}

int Up(void)
{
	int i;

	if (Key != D)
	{
		for (i = 0; i < LONG; i++)
		{
			if (tcs[i] != '0' && tcs[i] != '*' && tcs[i] != '|')
				tcs[i] += 1;
		}
		tcs[(x - 1)*ROW + y] = 1;
	}

	Printf();

	return 0;

}

int Down(void)
{
	int i;


	if (Key != U)
	{
		for (i = 0; i < LONG; i++)
		{
			if (tcs[i] != '0' && tcs[i] != '*' && tcs[i] != '|')
				tcs[i] += 1;
		}
		tcs[(x + 1)*ROW + y] = 1;
	}
	Printf();
	return 0;
}

int Left(void)
{
	int i;

	if (Key != R)
	{
		for (i = 0; i < LONG; i++)
		{
			if (tcs[i] != '0' && tcs[i] != '*' && tcs[i] != '|')
				tcs[i] += 1;
		}
		tcs[x*ROW + (y - 1)] = 1;
	}
	Printf();
	return 0;
}

int Right(void)
{
	int i;


	if (Key != L)
	{
		for (i = 0; i < LONG; i++)
		{
			if (tcs[i] != '0' && tcs[i] != '*' && tcs[i] != '|')
				tcs[i] += 1;
		}
		tcs[x*ROW + (y + 1)] = 1;
	}

	Printf();

	return 0;
}

int Printf(void)  //��ӡ
{
	system("cls");  //����

	int i;

	for (i = 0; i < LONG; i++)
	{
		if (tcs[i] == 0)
			printf("%c", ' ');
		else if (tcs[i] == '*' && tcs[i] == '|')
			printf("%c", tcs[i]);
		else
		{
			if (tcs[i] == 1)
				printf("%c", '@');
			else
				printf("%c", '*');
		}
		if (i%ROW == ROW - 1)
			printf("\n");
	}

	return 0;
}

int isbump(void)
{
	if (x == 0 || x == LONG / ROW || y == 1 || y == ROW)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int shuru()
{
	char ch = _getch();

	if (ch == -32)
		ch = _getch();

	if (ch == 27)
		printf("��������ESC�����Ƿ��˳���");
	else
	{
		switch (ch)
		{
		case U:
		{
			Key = ch;
			printf("���Ϸ����������");
			Up();
			break;
		}
		case D:
		{
			Key = ch;
			printf("���·����������");
			Down();
			break;
		}
		case L:
		{
			Key = ch;
			printf("�������������");
			Left();
			break;
		}
		case R:
		{
			Key = ch;
			printf("���ҷ����������");
			Right();
			break;
		}
		}
	}
	return 0;
}