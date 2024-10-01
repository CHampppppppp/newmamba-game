
#include <easyx.h>
#include<time.h>

#include <vector>
#include"menu.h"
#include"music.h"
#include "end.h"
#include "block.h"
#pragma comment(lib,"winmm.lib")
#include <mmsystem.h>
using namespace std;

//定义场景大小
#define WIDTH 1500
#define HEIGHT 800
//定义食物以及蛇的大小
#define SIZE  10
//定义蛇的朝向
#define UP 1
#define DOWN -1
#define LEFT 2
#define RIGHT -2
int speed = 175;		//蛇的速度(用在睡眠函数里面)
#define MAXLEN 1600             //蛇的最大长度
int wuditime = 0;//无敌帧
typedef struct {
	int x;
	int y;
}SnakeNode;

//创建蛇的类
class Snake
{
	friend class Food;          //蛇的友元为食物
	friend class Block;
public:
	Snake()//初始化
	{
		this->dirt = RIGHT;
		this->length = 3;
		score = 0;
		two = three = 0;
		//下标是0的位置为蛇的头部
		for (int i = 0; i < length; i++) {
			this->node[i].x = 70 - ((i + 1) * 2 * SIZE);
			this->node[i].y = SIZE;
		}
		loadimage(&bk, "bk.png", WIDTH, HEIGHT, 1);
	};
	void Move();				//移动
	void Draw();				//绘制蛇
	int Eat(Food& food);	    //吃食物
	bool Defeat(Block& block);				//失败判定
private:
	int dirt;					//朝向
	int length;					//长度
	int score; //总得分
	int two;//两分球个数
	int three;//三分球个数
	SnakeNode node[MAXLEN];		//蛇的结点     
	IMAGE bk;
};

//创建食物的类
class Food
{
	friend class Snake;         //食物的友元为蛇
	friend class Block;
public:
	Food(Snake& snake, Block& block);			//食物初始化
	void Draw();				//绘制食物
	bool coli(float x0, float y0)//碰撞判断
	{
		if (x0 == x && y0 == y) return true;
		if (x0 == x + 2 * SIZE && y0 == y) return true;
		if (x0 == x + 4 * SIZE && y0 == y) return true;
		if (x0 == x && y0 == y + 2 * SIZE) return true;
		if (x0 == x && y0 == y + 4 * SIZE) return true;
		if (x0 == x + 2 * SIZE && y0 == y + 2 * SIZE) return true;
		if (x0 == x + 4 * SIZE && y0 == y + 2 * SIZE) return true;
		if (x0 == x + 2 * SIZE && y0 == y + 4 * SIZE) return true;
		if (x0 == x + 4 * SIZE && y0 == y + 4 * SIZE) return true;
		return false;
	}
private:
	int x, y;					//坐标
	int score;					//分数
	int type;
	IMAGE ima1, ima2, ima3, ima4;
};

SnakeNode tmp[MAXLEN];	//用另外一个数组来存储蛇原来的位置
//移动

void Snake::Move() {
	//将原来的蛇结点拷贝一份
	for (int i = 0; i < this->length; i++) {
		tmp[i].x = this->node[i].x;
		tmp[i].y = this->node[i].y;
	}
	int status = 0;//用来判断是否点击了转向按键
	int flag = 0;
	if (this->dirt == RIGHT) {
		//判断是否转向
		if (GetAsyncKeyState('W') && status == 0) {
			this->node[0].y -= 2 * SIZE;
			this->dirt = UP;
			status = 1;
		}
		else if (GetAsyncKeyState('S') && status == 0) {
			this->node[0].y += 2 * SIZE;
			this->dirt = DOWN;
			status = 1;
		}
		else {
			if (GetAsyncKeyState('A') && status == 0)
				flag -= 10;
			if (GetAsyncKeyState('D') && status == 0)
				flag += 10;
			this->node[0].x += 2 * SIZE;
		}
	}
	else if (this->dirt == DOWN) {
		//判断是否转向
		if (GetAsyncKeyState('A') && status == 0) {
			this->node[0].x -= 2 * SIZE;
			this->dirt = LEFT;
			status = 1;
		}
		else if (GetAsyncKeyState('D') && status == 0) {
			this->node[0].x += 2 * SIZE;
			this->dirt = RIGHT;
			status = 1;
		}
		else {
			if (GetAsyncKeyState('W') && status == 0)
				flag -= 10;
			if (GetAsyncKeyState('S') && status == 0)
				flag += 10;
			this->node[0].y += 2 * SIZE;
		}
	}
	else if (this->dirt == LEFT) {
		//判断是否转向
		if (GetAsyncKeyState('W') && status == 0) {
			this->node[0].y -= 2 * SIZE;
			this->dirt = UP;
			status = 1;
		}
		else if (GetAsyncKeyState('S') && status == 0) {
			this->node[0].y += 2 * SIZE;
			this->dirt = DOWN;
			status = 1;
		}
		else {
			if (GetAsyncKeyState('D') && status == 0)
				flag -= 10;
			if (GetAsyncKeyState('A') && status == 0)
				flag += 10;
			this->node[0].x -= 2 * SIZE;
		}
	}
	else if (this->dirt == UP) {
		//判断是否转向
		if (GetAsyncKeyState('A') && status == 0) {
			this->node[0].x -= 2 * SIZE;
			this->dirt = LEFT;
			status = 1;
		}
		else if (GetAsyncKeyState('D') && status == 0) {
			this->node[0].x += 2 * SIZE;
			this->dirt = RIGHT;
			status = 1;
		}
		else {
			if (GetAsyncKeyState('S') && status == 0)
				flag -= 10;
			if (GetAsyncKeyState('W') && status == 0)
				flag += 10;
			this->node[0].y -= 2 * SIZE;
		}
	}
	//移动
	for (int i = 1; i < this->length; i++) {
		this->node[i].x = tmp[i - 1].x;
		this->node[i].y = tmp[i - 1].y;
	}
	Sleep(speed - flag * 15);
}


//绘制蛇
void Snake::Draw() {
	cleardevice();//清空原先的绘图
	putimage(0, 0, &bk);//先画出背景
	settextcolor(BLACK);
	char  scorestr[2000], twostr[1000], threestr[1000], str[8];
	sprintf_s(twostr, "二分球:%2d", two);
	sprintf_s(threestr, "三分凉:%2d", three);
	sprintf_s(scorestr, "总得分:%2d", score);//画出当前战绩
	outtextxy(900, 90, scorestr);
	outtextxy(900, 70, threestr);
	outtextxy(900, 50, twostr);
	srand((unsigned)time(NULL));//设置随机数种子
	for (int i = 0; i < this->length; i++) {
		setfillcolor(BLACK);//“黑”曼巴
		fillcircle(this->node[i].x, this->node[i].y, SIZE);
	}
}


//食物的初始化
Food::Food(Snake& snake, Block& block)
{
	loadimage(&ima1, "basketball.png", 4 * SIZE, 4 * SIZE);
	loadimage(&ima2, "baskrv.png", 4 * SIZE, 4 * SIZE);
	loadimage(&ima3, "bhc.png", 4 * SIZE, 4 * SIZE);
	loadimage(&ima4, "rv.png", 4 * SIZE, 4 * SIZE);
table:
	srand((unsigned)time(0));
	do
	{
		x = (rand() % (WIDTH / SIZE));
		y = (rand() % (HEIGHT / SIZE));
	} while (x % 2 == 0 || y % 2 == 0 || x >= WIDTH / 10 - 4 || y >= HEIGHT / 10 - 4 || block.onblock(x, y));//一直生成随机坐标直到该坐标不与障碍物重叠并且为能被蛇头碰到
	this->x *= SIZE;
	this->y *= SIZE;
	this->type = rand() % 100;
	if (type >= 0 && type <= 80) {
		type = 1;
	}
	else {
		type = 2;
	}
	for (int i = 0; i < snake.length; i++) {
		if (snake.node[i].x == this->x && snake.node[i].y == this->y) {
			goto table;
		}
	}
}

//绘制食物
void Food::Draw() {
	if (type == 1)//篮球
	{
		putimage(this->x, this->y, &ima2, SRCAND);
		putimage(x, y, &ima1, SRCPAINT);
	}
	else if (type == 2)//冰红茶
	{
		putimage(x, y, &ima4, SRCAND);
		putimage(x, y, &ima3, SRCPAINT);
	}
}

//吃食物
int Snake::Eat(Food& food) {
	if (food.coli(node[0].x, node[0].y)) {
		if (food.type == 1) {
			two++;
			score += 2;
		}
		else if (food.type == 2) {
			three++;
			score += 3;
		}
		if (this->node[length - 1].x - this->node[length - 2].x == 0 && this->node[length - 1].y - this->node[length - 2].y == -20) {
			this->length++;
			this->node[length - 1].x = this->node[length - 2].x;
			this->node[length - 1].y = this->node[length - 2].y - 2 * SIZE;
		}
		if (this->node[length - 1].x - this->node[length - 2].x == 0 && this->node[length - 1].y - this->node[length - 2].y == 20) {
			this->length++;
			this->node[length - 1].x = this->node[length - 2].x;
			this->node[length - 1].y = this->node[length - 2].y + 2 * SIZE;
		}
		if (this->node[length - 1].x - this->node[length - 2].x == 20 && this->node[length - 1].y - this->node[length - 2].y == 0) {
			this->length++;
			this->node[length - 1].x = this->node[length - 2].x + 2 * SIZE;
			this->node[length - 1].y = this->node[length - 2].y;
		}
		if (this->node[length - 1].x - this->node[length - 2].x == -20 && this->node[length - 1].y - this->node[length - 2].y == 0) {
			this->length++;
			this->node[length - 1].x = this->node[length - 2].x - 2 * SIZE;
			this->node[length - 1].y = this->node[length - 2].y;
		}
		return true;
	}
	return false;
}

//失败判定
bool Snake::Defeat(Block& block) {
	//1.碰到边界
	if (this->node[0].x < 0 || this->node[0].x >= WIDTH || this->node[0].y < 0 || this->node[0].y >= HEIGHT) {
		return true;
	}
	//2.碰到自己的身体
	for (int i = 1; i < this->length; i++) {
		if (this->node[0].x == this->node[i].x && this->node[0].y == this->node[i].y) {
			return true;
		}
	}
	//3.被肘击
	if (block.coli(node[0].x, node[0].y))
	{
		Sleep(1500);
		if (GetAsyncKeyState('1')) {
			wuditime = 5;
			return false;
		}
		return true;
	}
	return false;
}

int main() {
	Menu menu;
	Music music;
	End ending;
begin:
	menu.showmenu();
	if (menu.goon)
	{
		menu.window();
	table1:
		setbkcolor(WHITE);
		cleardevice();
		music.play_bkmusic();
		Block block;
		Snake snake;
		int num = 8;
		int newnum = 8;
		int eat = 0;
	table2:
		Food food(snake, block);
		while (1) {
			BeginBatchDraw();
			FlushBatchDraw();
			music.bk_volumn();
			snake.Draw();
			if (eat)
			{
				block.modify(newnum);
				block.Draw(newnum);
				num = newnum;
			}
			else block.Draw(num);
			if (GetAsyncKeyState('H'))
			{
				newnum += 16;
				block.diff();
			}
			if (GetAsyncKeyState(' ')) system("Pause");
			food.Draw();
			FlushBatchDraw();
			EndBatchDraw();//双缓冲，防止屏幕一闪一闪的
			if (snake.Eat(food)) {
				eat = 1;
				music.play_eatingsound();
				wuditime = 5;//无敌帧
				goto table2;
			}
			if (wuditime<=0 &&snake.Defeat(block) ) {
				music.play_colisound();
				break;
			}
			snake.Move();
			wuditime--;
			eat = 0;
		}
		HWND window = GetHWnd();
		SetWindowText(window, "死亡");
		int end = MessageBox(window, "mamba out,see you again?", "提示", MB_OKCANCEL);
		if (end == IDOK) goto table1;
		else if (end==IDCANCEL)
		{
			music.play_endmusic();
			ending.draw();
			goto begin;
		}
	}
	return 0;
}

