#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<mmsystem.h>//播放音乐
#pragma comment(lib,"winmm.lib") //播放音乐

#define SNAKE_NUM 500 //蛇的最大节数
enum DIR//表示方向
{
   UP,
   DOWN,
   LEFT,
   RIGHT,
};
struct Snake
{
	int size;//蛇的节数
	int dir;//蛇的方向
	int speed;//移动速度
	POINT coor[500];//坐标
}snake;
//食物结构
struct Food
{
	int x;
	int y;
	int r;//食物大小
	bool flag;//食物是否被吃
	DWORD color;//食物的颜色
}food;
void GameInit()
{
	//播放背景音乐
	//mciSendString("open ./music/芝麻Mochi - Where Is The Love（铃声版）.mp3 alias BGM", 0, 0, 0);
	//mciSendString("play BGM repeat", 0, 0, 0);
	PlaySound(TEXT("music/芝麻Mochi-Where-Is-The-Love（铃声版）.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	//初始化 图形窗口
	initgraph(640, 480);
	//设置随机数种子
	srand(GetTickCount()); //获取开机到现在所经过的毫秒数
	//初始化蛇
	snake.size = 3;
	snake.speed = 10;
	snake.dir = RIGHT;
	for (int i = 0; i < snake.size; i++)
	{
		snake.coor[i].x = 40-10*i;
		snake.coor[i].y = 10;
	}
	//初始化食物 rand随机产生一个整数，如果没有设置随机种子，每次产生都是固定的整数 2 % 5 == 1
	//设置种子需要头文件stdlib.h,一般把时间作为种子,因为时间是不断变化的
	food.x = rand() %640;
	food.x = rand() %480;
	food.color = RGB(rand()%256, rand()%256, rand()%256 );
	food.r = rand() % 10 + 10;
	food.flag = true;
}
void GameDraw()
{
	BeginBatchDraw();
	//设置背景颜色
	setbkcolor(RGB(20, 50, 119));
	cleardevice();
	//绘制蛇
	setfillcolor(GREEN);
	for (int i = 0; i <= snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	//绘制食物
	if (food.flag)
	{
		solidcircle(food.x, food.y+20, food.r);
	}
	EndBatchDraw();
}
//移动蛇
void snakeMove()
{
	//让身体跟着头走
	for (int i = snake.size-1; i > 0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y -= snake.speed;
		if (snake.coor[0].y + 10 <= 0)//超出了上面的边界
		{
			snake.coor[0].y = 480;
		}
		break;
	case DOWN:
		snake.coor[0].y += snake.speed;
		if (snake.coor[0].y - 10 >= 480)
		{
			snake.coor[0].y = 0;
		}
		break;
	case LEFT:
		snake.coor[0].x -= snake.speed;
		if (snake.coor[0].x + 10 <= 0)
		{
			snake.coor[0].x = 640;
		}
		break;
	case RIGHT:
		snake.coor[0].x += snake.speed;
		if (snake.coor[0].x - 10 >= 640)
		{
			snake.coor[0].y = 0;
		}
		break;
	}
}
//通过按键改变蛇的方向
void keycontrol()
{
	//判断有没有按键，如果有按键就返回真
	if (_kbhit())
	{
		switch (_getch())
		{
			// 72 80 75 77上下左右键值
		case 'w':
		case 'W':
		case 72:
			//改变方向
			if (snake.dir != DOWN)
			{
				snake.dir = UP;
			}
			break;
		case 's':
		case 'S':
		case 80:
			if (snake.dir != UP)
			{
				snake.dir = DOWN;
			}
			break;
		case 'a':
		case 'A':
		case 75:
			if (snake.dir != RIGHT)
			{
				snake.dir = LEFT;
			}
			break;
		case 'd':
		case 'D':
		case 77:
			if (snake.dir != LEFT)
			{
				snake.dir = RIGHT;
			}
			break;
		case  ' ': //游戏暂停逻辑
				while (1)
				{
					if (_getch() == ' ')
						return;
				}
				break;
		}
	}

}
void Eatfood()
{
	if (food.flag && snake.coor[0].x >= food.x - food.r && snake.coor[0].x <= food.x + food.r &&
		snake.coor[0].y >= food.y - food.r && snake.coor[0].y <= food.y + food.r)
	{
		food.flag = false;
		snake.size++;
	}
	if (!food.flag)
	{
		food.x = rand() % 640;
		food.x = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256, );
		food.r = rand() % 10 + 5;
		food.flag = true;
	}
}
//游戏暂停
void stop()
{
	if (_kbhit())
	{
		if (_getch() == ' ')
		{
			while (_getch() == ' ')
			{
				
			}
		}
	}
}
//如果食物消失，则重新生成一个食物
int main()
{
	GameInit();
	  while (1)
	{
		  snakeMove();
		  GameDraw();
		  keycontrol();
		  Eatfood();
		  Sleep(200);
	}
	return 0;
}