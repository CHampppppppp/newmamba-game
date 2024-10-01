#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#ifndef MUSIC_H
#define MUSIC_H
#pragma once
#define WIDTH 1500
#define HEIGHT 800
//定义食物以及蛇的大小
#define SIZE  10
using namespace std;

class Music
{
private:
	int vol;
public:
	Music() :vol(100) {};
	void bk_volumn();
	void play_bkmusic();
	void play_eatingsound();
	void play_colisound();
	void play_endmusic();
	void play_menumusic();
	void play_detailmusic();
	void play_controlmusic();
	void play_respectmusic();//你干嘛~~哎呦
	void play_norespectmusic();
	void play_historymusic();//三十年河西三十年河东，莫欺少年穷！
};

void Music::bk_volumn()
{
	if (GetAsyncKeyState(38)) vol += 100;
	else if (GetAsyncKeyState(40)) vol -= 100;
	char com1[41];
	sprintf(com1, "setaudio BGM1 volume to %d", vol);
	mciSendString(com1, NULL, 0, NULL);
}
void Music::play_bkmusic()
{
	mciSendString("open syagp.mp3 alias BGM1", 0, 0, 0);//see you again加速版
	mciSendString("play BGM1 repeat", 0, 0, 0);
}

void Music::play_eatingsound()
{
	mciSendString("close EAT", 0, 0, 0);
	mciSendString("open eatingsound.mp3 alias EAT", 0, 0, 0);
	mciSendString("play EAT", 0, 0, 0);
	if (GetAsyncKeyState(38)) vol += 100;
	else if (GetAsyncKeyState(40)) vol -= 100;
	char com2[41];
	sprintf(com2, "setaudio EAT volume to %d", vol);
	mciSendString(com2, NULL, 0, NULL);
	
}

void Music::play_colisound()
{
	mciSendString("close BGM1", 0, 0, 0);
	mciSendString("close BGM2", 0, 0, 0);
	mciSendString("open ah.mp3 alias BGM2", 0, 0, 0);//man！
	mciSendString("play BGM2", 0, 0, 0);
	if (GetAsyncKeyState(38)) vol += 100;
	else if (GetAsyncKeyState(40)) vol -= 100;
	char com3[41];
	sprintf(com3, "setaudio BGM2 volume to %d", vol);
	mciSendString(com3, NULL, 0, NULL);
}

void Music::play_endmusic()
{
	mciSendString("close BGM1", 0, 0, 0);
	mciSendString("open mambaout.mp3 alias END", 0, 0, 0);//mambaout
	mciSendString("play END", 0, 0, 0);
	if (GetAsyncKeyState(38)) vol += 100;
	else if (GetAsyncKeyState(40)) vol -= 100;
	char com4[41];
	sprintf(com4, "setaudio END volume to %d", vol);
	mciSendString(com4, NULL, 0, NULL);
}


#endif
