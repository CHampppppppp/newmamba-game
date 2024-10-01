#include <iostream>
#include <stdio.h>
#include <graphics.h>
#ifndef MENU_H
#define MENU_H
#pragma once
#define WIDTH 1500
#define HEIGHT 800
//定义食物以及蛇的大小
#define SIZE  10
using namespace std;

class Menu
{
private:
	IMAGE menu_bk, detail_bk, history_bk, control_bk, respect_bk;
	MOUSEMSG m;
public:
	int goon = 1;
	Menu();
	void window();
	void showmenu();
	void showhistory();
	void showdetail();
	void showcontrol();
	void showrespect();
	bool goback();
	void showreturn();
};

void Menu::window()
{
	initgraph(WIDTH, HEIGHT);
	// 确定窗口的初始位置，使其位于屏幕中央
	int windowPosX = 0;
	int windowPosY = 0;

	// 获取当前窗口句柄
	HWND hwnd = GetHWnd();

	// 设置窗口位置
	SetWindowPos(hwnd, HWND_TOP, windowPosX, windowPosY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

Menu::Menu()
{
	loadimage(&menu_bk, "menubk.png", WIDTH, HEIGHT);
	loadimage(&detail_bk, "detailbk.jpg", WIDTH, HEIGHT);
	loadimage(&history_bk, "historybk.jpg", WIDTH, HEIGHT);
	loadimage(&control_bk, "controlbk.jpg", WIDTH, HEIGHT);
}

void Menu::showmenu()
{
menubegin:
	window();
	setbkcolor(WHITE);
	cleardevice();
	putimage(0, 0, &menu_bk);
	setfillcolor(WHITE);
	fillrectangle(200, 140, 600, 160);
	fillrectangle(200, 200, 600, 220);
	fillrectangle(200, 260, 600, 280);
	fillrectangle(200, 320, 600, 340);
	fillrectangle(200, 380, 600, 400);
	fillrectangle(200, 440, 600, 460);
	fillrectangle(200, 500, 600, 520);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(250, 142, "开始游戏");//goto begin
	outtextxy(250, 202, "历史得分榜");//goto history
	outtextxy(250, 262, "操作");//goto control
	outtextxy(250, 322, "游戏说明");//goto detail
	outtextxy(250, 382, "作者好帅");//就喜欢你这种有眼力的玩家
	outtextxy(250, 442, "作者好丑");//游戏崩溃
	outtextxy(250, 502, "mamba out");//退出游戏
	settextcolor(WHITE);
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 200 && m.x <= 600 && m.y >= 140 && m.y <= 160) {//检测鼠标的位置 是否满足条件
			setlinecolor(YELLOW);//满足后 设置新的边框为红色
			rectangle(190, 135, 610, 165);//画新的边框
			if (m.uMsg == WM_LBUTTONDOWN) {
				break;
			}
		}
		else if (m.x >= 200 && m.x <= 600 && m.y >= 200 && m.y <= 220) {
			setlinecolor(YELLOW);
			rectangle(190, 195, 610, 225);
			if (m.uMsg == WM_LBUTTONDOWN) {
				showhistory();
				goto menubegin;
			}
		}
		else if (m.x >= 200 && m.x <= 600 && m.y >= 260 && m.y <= 280) {
			setlinecolor(YELLOW);
			rectangle(190, 255, 610, 285);
			if (m.uMsg == WM_LBUTTONDOWN) {
				showcontrol();
				goto menubegin;
			}
		}
		else if (m.x >= 200 && m.x <= 600 && m.y >= 320 && m.y <= 340) {
			setlinecolor(YELLOW);
			rectangle(190, 315, 610, 345);
			if (m.uMsg == WM_LBUTTONDOWN) {
				showdetail();
				goto menubegin;
			}
		}
		//
		else if (m.x >= 200 && m.x <= 600 && m.y >= 380 && m.y <= 400) {
			setlinecolor(YELLOW);
			rectangle(190, 375, 610, 405);
			if (m.uMsg == WM_LBUTTONDOWN) {
				showrespect();
				goto menubegin;
			}
		}
		else if (m.x >= 200 && m.x <= 600 && m.y >= 440 && m.y <= 460) {
			setlinecolor(YELLOW);
			rectangle(190, 435, 610, 465);
			if (m.uMsg == WM_LBUTTONDOWN) {
				goon = 0;
				cout << "谎言不会伤人，\n真相才是快刀。\n别玩了，一点人情世故都不懂-_-"<<endl<<endl;
				break;
			}
		}
		else if (m.x >= 200 && m.x <= 600 && m.y >= 500 && m.y <= 520) {
			setlinecolor(YELLOW);
			rectangle(190, 495, 610, 525);
			if (m.uMsg == WM_LBUTTONDOWN) {
				goon = 0;
				break;
			}
		}
		else {
			setlinecolor(WHITE);
			rectangle(190, 135, 610, 165);
			rectangle(190, 195, 610, 225);
			rectangle(190, 255, 610, 285);
			rectangle(190, 315, 610, 345);
			rectangle(190, 375, 610, 405);
			rectangle(190, 435, 610, 465);
			rectangle(190, 495, 610, 525);
		}
	}
}

void Menu::showdetail()
{
	setbkcolor(WHITE);
	cleardevice();
	/*putimage(0, 0, &detail_bk);*/
	char line1[1000] = "游戏说明:";
	char line2[1000] = "1. 游戏压缩包包没有病毒的，请放心使用，如果游玩发现bug，请转告给世界上最帅的人，欢迎各位转告给我。";
	char line3[1000] = "2. 长按前进方向加速突破，反向减速慢节奏。";
	char line4[1000] = "3. 曼巴具有剧毒性，咬到自己会马上死亡。";
	char line5[1000] = "4. 曼巴速度很快，动能太大，撞墙马上死亡。";
	char line6[1000] = "5. 游戏中的肘子应尽量避免，如被肘击，在1.5秒内扣1可以复活劳大，此时劳大会艰难爬起来前进。";
	char line7[1000] = "6. 如果闲游戏太简单，按h增加难度，难度会在吃到下一个食物后刷新。";
	char line8[1000] = "7. 游戏为本人制作，欢迎转载或用于商业行为。（神头鬼脸）";
	char line9[1000] = "8. 游戏达到81分有彩蛋;";
	char line10[1000] ="9. 游戏后续会更新完善，3.0版本仅为第三代版本，望理解，敬请期待4.0版本。";
	while (1)
	{
		outtextxy(100, 50, line1);
		outtextxy(100, 80, line2);
		outtextxy(100, 110, line3);
		outtextxy(100, 140, line4);
		outtextxy(100, 170, line5);
		outtextxy(100, 200, line6);
		outtextxy(100, 230, line7);
		outtextxy(100, 260, line8);
		outtextxy(100, 290, line9);
		outtextxy(100, 320, line10);
		showreturn();
		if (goback()) break;
	}
}

void Menu::showhistory()
{
	setbkcolor(WHITE);
	cleardevice();
	/*putimage(0, 0, &history_bk);*/
	setfillcolor(WHITE);
	while (1) //文件输出
	{
		showreturn();
		if (goback()) break;
	}
}

void Menu::showcontrol()
{
	setbkcolor(WHITE);
	cleardevice();
	/*putimage(0, 0, &control_bk);*/
	char line1[100] = "WASD : 上下左右，长按加减速";
	char line2[100] = "H : 增加难度";
	char line3[100] = "扣1 : 复活牢大";
	char line4[100] = "空格 : 暂停";
	char line5[100] = "详见游戏说明";
	while (1)
	{
		outtextxy(200, 30, line1);
		outtextxy(200, 60, line2);
		outtextxy(200, 90, line3);
		outtextxy(200, 120, line4);
		outtextxy(200, 150, line5);
		showreturn();
		if (goback()) break;
	}
}

void Menu::showrespect()
{
	setbkcolor(WHITE);
	cleardevice();
	/*putimage(0, 0, &respect_bk);*/
	while (1)
	{
		char line1[100] = "就喜欢爱说真话的人>_<";
		outtextxy(200, 30, line1);
		showreturn();
		if (goback()) break;
	}
	cout << endl;
}


bool Menu::goback()
{
	m = GetMouseMsg();
	if (m.x >= 0 && m.x <= 1800 && m.y >= 0 && m.y <= 800)
		if (m.uMsg == WM_RBUTTONDOWN) {
			return 1;
		}
	return 0;
}

void Menu::showreturn()
{
	settextcolor(BLACK);
	outtextxy(900, 202, "右");
	outtextxy(900, 222, "击");
	outtextxy(900, 242, "鼠");
	outtextxy(900, 262, "标");
	outtextxy(900, 282, "返");
	outtextxy(900, 302, "回");
}
// 
// int main()
// {
// 	Menu m;
// 	m.showmenu();
// 	return 0;
// }


#endif
