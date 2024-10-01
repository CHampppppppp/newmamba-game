#include <iostream>
#include <stdio.h>
#include <graphics.h>
#ifndef END_H
#define END_H
#pragma once
#define WIDTH 1500
#define HEIGHT 800
//定义食物以及蛇的大小
#define SIZE  10
using namespace std;

class End
{
private:
	IMAGE kobe1, kobe2, kobe3, champ;
public:
	End()
	{
		loadimage(&kobe1, "ending.jpg", 552, 551, 0);
		loadimage(&kobe2, "hurt2.jpg", 539, 839, 0);
		loadimage(&kobe3, "hurt.jpg", 570, 856, 0);
		loadimage(&champ, "champ.png", 520, 359, 0);
	}
	void draw()
	{
		cleardevice();
		putimage(19, 497, &champ);
		putimage(0, 0, &kobe1);
		putimage(552, 0, &kobe2);
		putimage(1010, 0, &kobe3);
		Sleep(9000);
	}
};

#endif
