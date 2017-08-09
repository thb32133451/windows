#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>

#define LONG 2870  //数组长度
#define ROW 70  //宽度
#define U 72
#define D 80
#define L 75
#define R 77

int tcs[LONG]; //贪吃蛇
int Key = 75;  //记录上次输入(初始化为左)
int x, y;  //坐标
int lenth = 6;  //初始蛇长为6

x = 21;  //初始化蛇起始位置
y = 33;

int isbump(void);  //碰撞（撞墙or吃到球）
int tuichu(void);  //游戏结束
int Up(void);
int Down(void);
int Left(void);
int Right(void);
int Printf(void);  //屏幕打印
int shuru(void);

int main(void)
{
	int i;
	int bool = 0;

	for (i = 0; i < LONG; i++)  //初始化数组
	{
		if (i % ROW == ROW - 1 || i % ROW == 0)  //左右墙壁
			tcs[i] = '|';
		else if (i > 0 && i < ROW - 1)  //上墙壁
			tcs[i] = '*';
		else if (i > LONG - ROW && i < LONG - 1)  //下墙壁
			tcs[i] = '*';
		else if (i >= x*ROW + y + 1 && i <= x*ROW + y + lenth + 1)  //蛇身
			tcs[i] = '*';
		else
			tcs[i] = 0;
	}

	for (i = 1; i <= lenth; i++)  //初始轨迹
	{
		tcs[x*ROW + y + i - 1] = i;
	}

	Printf();  //打印


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
	printf("游戏结束，即将退回主菜单。\n");
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

int Printf(void)  //打印
{
	system("cls");  //清屏

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
		printf("您按下了ESC键，是否退出？");
	else
	{
		switch (ch)
		{
		case U:
		{
			Key = ch;
			printf("向上方向键被按下");
			Up();
			break;
		}
		case D:
		{
			Key = ch;
			printf("向下方向键被按下");
			Down();
			break;
		}
		case L:
		{
			Key = ch;
			printf("向左方向键被按下");
			Left();
			break;
		}
		case R:
		{
			Key = ch;
			printf("向右方向键被按下");
			Right();
			break;
		}
		}
	}
	return 0;
}