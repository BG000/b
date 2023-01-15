#include <stdio.h>
#include<graphics.h>
#define WIN_WIDTH 902
#define WIN_HEIGHT 597
#include<mmsystem.h>//��������
#pragma comment(lib,"winmm.lib") //��������



enum {
	WAN_DOU,
    XIANG_RI_KUI,
	LA_JIAO,
	ZHI_WU_COUNT,
};

IMAGE imgBg;//��ʾ��Ϸ����ͼ
IMAGE imgBar;//��Ϸ�Ϸ��Ĺ�����
IMAGE imgCards[ZHI_WU_COUNT];
IMAGE* imgZhiwu[ZHI_WU_COUNT][20]; //13 ��ʮ�������� NULL��NULL��Ϊ����β
int framecount[ZHI_WU_COUNT];

int sunshine;
int curX, curY;
int curZhiwu;//��ǰѡ�е�ֲ��

void gameinit()
{
	PlaySound(TEXT("music/Laura-Shigihara-Grazy-Dave-_Intro-Theme_.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	loadimage(&imgBg, "res/��Ļ��ͼ 2023-01-14 094807.png");
	loadimage(&imgBar, "res/δ����-1.jpg");
	sunshine = 150;

	char name[64];
	for (int i = 0; i < ZHI_WU_COUNT; i++)
	{
		//�����ļ���
		sprintf_s(name, sizeof(name), "res/cards/card_%d.jpg", i + 1);
		loadimage(&imgCards[i], name);

	for (int j = 0; j < 20; j++)
	{
		sprintf_s(name, sizeof(name), "res/zhiwu/%d/%d.jpg", i, j + 1);
		imgZhiwu[i][j] = new IMAGE;//�����ڴ�
		loadimage(imgZhiwu[i][j], name);
		if (imgZhiwu[i][j]->getwidth() == 0)
		{
			delete imgZhiwu[i][j];//�ͷ��ڴ�
			imgZhiwu[i][j] = NULL;
		}
	}
}
	initgraph(WIN_WIDTH, WIN_HEIGHT,1);//����������Ϊ1����ʾ����̨������ʾ
	//�������壬ֻ����һ��
	LOGFONT f;  //��ʾ����ı���
	gettextstyle(&f);//��ȡ��ǰ����
	f.lfWidth = 12;
	f.lfHeight = 15;
	strcpy_s(f.lfFaceName, "Segoe UI Black");//�������������
	f.lfQuality = ANTIALIASED_QUALITY;//�����Ч��
	settextstyle(&f);
	setbkmode(TRANSPARENT); //�������屳��Ϊ͸��Ч��
	setcolor(BLACK);
}
	void upwindow()
	{
		//��ͼƬ������������� ֱ������EndBatchDraw��һ�����������
		//���ⴰ����˸
		BeginBatchDraw();
		//�Ӵ��ڵ����Ͻ�(0,0)��ӡͼƬ
		putimage(0, 0, &imgBg);
		putimage(260, 0, &imgBar);
		for (int i = 0; i < ZHI_WU_COUNT; i++)
		{
			int x = 330 + i *55;
			int y = 6;
			putimage(x, y, &imgCards[i]);
		}
		//��ʾ����ֵ
		char scoreText[8];
		sprintf_s(scoreText, sizeof(scoreText), "%d", sunshine);
		outtextxy(285, 55, scoreText);
		//�����ƶ������е�ֲ��
		if (curZhiwu > 0)
		{
			IMAGE* img = imgZhiwu[curZhiwu-1][0];
			putimage(curX, curY,img);
		}

		EndBatchDraw();
	}
	void userClick()
	{
		static int status = 0;
		ExMessage msg;
		if (peekmessage(&msg))
		{
			//�ǲ����������
			if (msg.message == WM_LBUTTONDOWN)
			{
				if (msg.x > 330 && msg.x < 330 + 55 * ZHI_WU_COUNT &&
					msg.y >6 && msg.y < 56)
				{
					int index = (msg.x - 330) / 56;
					printf("index=%d", index);
					status = 1;
					curZhiwu = index + 1;
				}
			}
			else if (msg.message == WM_MOUSEMOVE  && status == 1) {
				//��¼��ǰ�϶������е�λ��
				curX = msg.x;
				curY = msg.y;
             }
			else if (msg.message == WM_LBUTTONUP) {

             }
		}
     }
int main(void)
{
	gameinit();//��Ϸ��ʼ��
	//��Ϸ��ѭ��
	while (1)
	{
		userClick();//�û��ĵ����������ֲֲ�
		upwindow();
	}
	return 0;
}