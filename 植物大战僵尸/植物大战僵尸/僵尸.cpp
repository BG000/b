#include <stdio.h>
#include<graphics.h>
#define WIN_WIDTH 902
#define WIN_HEIGHT 597
#include<mmsystem.h>//播放音乐
#pragma comment(lib,"winmm.lib") //播放音乐



enum {
	WAN_DOU,
    XIANG_RI_KUI,
	LA_JIAO,
	ZHI_WU_COUNT,
};

IMAGE imgBg;//表示游戏背景图
IMAGE imgBar;//游戏上方的工具栏
IMAGE imgCards[ZHI_WU_COUNT];
IMAGE* imgZhiwu[ZHI_WU_COUNT][20]; //13 第十四张设置 NULL，NULL作为最后结尾
int framecount[ZHI_WU_COUNT];

int sunshine;
int curX, curY;
int curZhiwu;//当前选中的植物

void gameinit()
{
	PlaySound(TEXT("music/Laura-Shigihara-Grazy-Dave-_Intro-Theme_.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	loadimage(&imgBg, "res/屏幕截图 2023-01-14 094807.png");
	loadimage(&imgBar, "res/未标题-1.jpg");
	sunshine = 150;

	char name[64];
	for (int i = 0; i < ZHI_WU_COUNT; i++)
	{
		//生成文件名
		sprintf_s(name, sizeof(name), "res/cards/card_%d.jpg", i + 1);
		loadimage(&imgCards[i], name);

	for (int j = 0; j < 20; j++)
	{
		sprintf_s(name, sizeof(name), "res/zhiwu/%d/%d.jpg", i, j + 1);
		imgZhiwu[i][j] = new IMAGE;//申请内存
		loadimage(imgZhiwu[i][j], name);
		if (imgZhiwu[i][j]->getwidth() == 0)
		{
			delete imgZhiwu[i][j];//释放内存
			imgZhiwu[i][j] = NULL;
		}
	}
}
	initgraph(WIN_WIDTH, WIN_HEIGHT,1);//第三个参数为1，表示控制台可以显示
	//设置字体，只设置一次
	LOGFONT f;  //表示字体的变量
	gettextstyle(&f);//获取当前字体
	f.lfWidth = 12;
	f.lfHeight = 15;
	strcpy_s(f.lfFaceName, "Segoe UI Black");//设置字体的名称
	f.lfQuality = ANTIALIASED_QUALITY;//抗锯齿效果
	settextstyle(&f);
	setbkmode(TRANSPARENT); //设置字体背景为透明效果
	setcolor(BLACK);
}
	void upwindow()
	{
		//把图片先输出到缓冲区 直到遇到EndBatchDraw才一起输出到窗口
		//避免窗口闪烁
		BeginBatchDraw();
		//从窗口的左上角(0,0)打印图片
		putimage(0, 0, &imgBg);
		putimage(260, 0, &imgBar);
		for (int i = 0; i < ZHI_WU_COUNT; i++)
		{
			int x = 330 + i *55;
			int y = 6;
			putimage(x, y, &imgCards[i]);
		}
		//显示阳光值
		char scoreText[8];
		sprintf_s(scoreText, sizeof(scoreText), "%d", sunshine);
		outtextxy(285, 55, scoreText);
		//绘制移动过程中的植物
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
			//是不是左键按下
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
				//记录当前拖动过程中的位置
				curX = msg.x;
				curY = msg.y;
             }
			else if (msg.message == WM_LBUTTONUP) {

             }
		}
     }
int main(void)
{
	gameinit();//游戏初始化
	//游戏主循环
	while (1)
	{
		userClick();//用户的点击操作（种植植物）
		upwindow();
	}
	return 0;
}