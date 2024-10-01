#include <iostream>
#include <stdio.h>
#include <graphics.h>
#ifndef BLOCK_H
#define BLOCK_H
#pragma once
#define WIDTH 1500
#define HEIGHT 800
//定义食物以及蛇的大小
#define SIZE  10
using namespace std;

class Block
{
	friend class Snake;
	friend class Food;
private:
	vector<vector<int>> vc;//用vector数组存放批量障碍物的坐标
	int x, y;
	int count;
	int difficulty;//难度越高，障碍物数量越多
	IMAGE b, bv;//障碍物的图案
public:
	Block(); //初始化8个障碍物
	void Draw(int num);//负责障碍物相关的绘画
	bool coli(int x0, int y0);//碰撞判定
	bool onblock(int x, int y);//判断一个东西是否与障碍物重叠
	void modify(int num);//改变障碍物数量
	void diff();//改变显示难度
};

Block::Block():vc(100, vector<int>(2)), count(8), difficulty(1)
{
	srand(time(0));//改变随机数种子
	for (int i = 0; i < 100; i++)
	{
		do
		{
			x = rand() % (WIDTH / SIZE);
			y = rand() % (HEIGHT / SIZE);
		} while (x % 2 == 0 || y % 2 == 0 || x >= WIDTH / 10 - 5 || y >= HEIGHT / 10 - 5);
		x *= 10;
		y *= 10;
		vc[i][0] = x;
		vc[i][1] = y;
	}
	loadimage(&b, "block.png", 5 * SIZE, 5 * SIZE);//初始化图案
	loadimage(&bv, "blockrv.png", 5 * SIZE, 5 * SIZE);
}

void Block::Draw(int num)
{
	char difficultystr[10];
	settextcolor(BLACK);
	sprintf_s(difficultystr, "难度:%2d", difficulty);
	outtextxy(900, 20, difficultystr);
	for (int i = 0; i < num; i++)
	{
		putimage(vc[i][0], vc[i][1], &bv, SRCAND);
		putimage(vc[i][0], vc[i][1], &b, SRCPAINT);
	}
}

bool Block::coli(int x0,int y0)
{
	for (int i = 0; i < count; i++)
	{
		int x = vc[i][0];
		int y = vc[i][1];//循环每个障碍物，判断蛇头坐标x0，y0是否碰到障碍物
		if (x0 == x && y0 == y) return true;
		if (x0 == x + 2 * SIZE && y0 == y) return true;
		if (x0 == x + 4 * SIZE && y0 == y) return true;
		if (x0 == x && y0 == y + 2 * SIZE) return true;
		if (x0 == x && y0 == y + 4 * SIZE) return true;
		if (x0 == x + 2 * SIZE && y0 == y + 2 * SIZE) return true;
		if (x0 == x + 4 * SIZE && y0 == y + 2 * SIZE) return true;
		if (x0 == x + 2 * SIZE && y0 == y + 4 * SIZE) return true;
		if (x0 == x + 4 * SIZE && y0 == y + 4 * SIZE) return true;
	}
	return false;
}

bool Block::onblock(int x,int y)
{
	x *= 10;
	y *= 10;
	for (int i = 0; i < count; i++)
	{
		if (x >= vc[i][0] && x <= vc[i][0] + 4 * SIZE && y >= vc[i][1] && y <= vc[i][1] + 4 * SIZE) return true;
	}return false;
}

void Block::modify(int num)
{
	count = num;
}

void Block::diff()
{
	difficulty++;
}

#endif
