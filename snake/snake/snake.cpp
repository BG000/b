#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<mmsystem.h>//��������
#pragma comment(lib,"winmm.lib") //��������

#define SNAKE_NUM 500 //�ߵ�������
enum DIR//��ʾ����
{
   UP,
   DOWN,
   LEFT,
   RIGHT,
};
struct Snake
{
	int size;//�ߵĽ���
	int dir;//�ߵķ���
	int speed;//�ƶ��ٶ�
	POINT coor[500];//����
}snake;
//ʳ��ṹ
struct Food
{
	int x;
	int y;
	int r;//ʳ���С
	bool flag;//ʳ���Ƿ񱻳�
	DWORD color;//ʳ�����ɫ
}food;
void GameInit()
{
	//���ű�������
	//mciSendString("open ./music/֥��Mochi - Where Is The Love�������棩.mp3 alias BGM", 0, 0, 0);
	//mciSendString("play BGM repeat", 0, 0, 0);
	PlaySound(TEXT("music/֥��Mochi-Where-Is-The-Love�������棩.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	//��ʼ�� ͼ�δ���
	initgraph(640, 480);
	//�������������
	srand(GetTickCount()); //��ȡ�����������������ĺ�����
	//��ʼ����
	snake.size = 3;
	snake.speed = 10;
	snake.dir = RIGHT;
	for (int i = 0; i < snake.size; i++)
	{
		snake.coor[i].x = 40-10*i;
		snake.coor[i].y = 10;
	}
	//��ʼ��ʳ�� rand�������һ�����������û������������ӣ�ÿ�β������ǹ̶������� 2 % 5 == 1
	//����������Ҫͷ�ļ�stdlib.h,һ���ʱ����Ϊ����,��Ϊʱ���ǲ��ϱ仯��
	food.x = rand() %640;
	food.x = rand() %480;
	food.color = RGB(rand()%256, rand()%256, rand()%256 );
	food.r = rand() % 10 + 10;
	food.flag = true;
}
void GameDraw()
{
	BeginBatchDraw();
	//���ñ�����ɫ
	setbkcolor(RGB(20, 50, 119));
	cleardevice();
	//������
	setfillcolor(GREEN);
	for (int i = 0; i <= snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	//����ʳ��
	if (food.flag)
	{
		solidcircle(food.x, food.y+20, food.r);
	}
	EndBatchDraw();
}
//�ƶ���
void snakeMove()
{
	//���������ͷ��
	for (int i = snake.size-1; i > 0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	switch (snake.dir)
	{
	case UP:
		snake.coor[0].y -= snake.speed;
		if (snake.coor[0].y + 10 <= 0)//����������ı߽�
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
//ͨ�������ı��ߵķ���
void keycontrol()
{
	//�ж���û�а���������а����ͷ�����
	if (_kbhit())
	{
		switch (_getch())
		{
			// 72 80 75 77�������Ҽ�ֵ
		case 'w':
		case 'W':
		case 72:
			//�ı䷽��
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
		case  ' ': //��Ϸ��ͣ�߼�
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
//��Ϸ��ͣ
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
//���ʳ����ʧ������������һ��ʳ��
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