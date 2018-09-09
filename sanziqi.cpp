#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib") 
#include"head.h"
#include<time.h>
//游戏时间
time_t start;
time_t end;
//显示首页
void firstPage()
{
	srand((unsigned int)time(NULL));
	while(1)
	{
		printf("\n\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),rand()%8+8);
		printf("\t\t\t   《");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),rand()%8+8);
		printf(" 贪");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),rand()%8+8);
		printf(" 吃");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),rand()%8+8);
		printf(" 蛇");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),rand()%8+8);
		printf(" 》\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		printf("\t\t\t      空格开始\n\n");
		printf("\t\t    《方向键或w a s d 控制方向》\n\n\n\n");
		printf("\t\t\t难度：");
		if((temp%3)==1)
		{
			printf("  →初   中   高");
		}
		if((temp%3)==2)
		{
			printf("   初  →中   高");
		}
		if((temp%3)==0)
		{
			printf("   初   中  →高");
		}
		if(GetAsyncKeyState(VK_RIGHT))
		{	
			temp++;
			if(temp>=3)
				temp=3;
		}
		if(GetAsyncKeyState('D'))
		{	
			temp++;
			if(temp>=3)
				temp=3;
		}
		if(GetAsyncKeyState(VK_LEFT))
		{	
			temp--;
			if(temp<=1)
				temp=1;
		}
		if(GetAsyncKeyState('A'))
		{	
			temp--;
			if(temp<=1)
				temp=1;
		}
		if(GetAsyncKeyState(VK_SPACE))
		{
			break;
		}
		Sleep(500);
		system("cls");
	}
}
//打开音乐
void myPlaySound()
{
	PlaySound("1.wav",NULL,SND_FILENAME | SND_ASYNC);
}
//检查是否按下空格
/*void checkSpaceKey()
{
	char space;
	while(1)
	{
		space=getch();
		if(space==' ')
			{
				break;
			}
	}
}*/
//关闭音乐
void shutMusic() 
{
	PlaySound(NULL,NULL,SND_FILENAME | SND_ASYNC);
}
//显示游戏背景
void showBackGround()
{
	int i;	
	for(i=0;i<20;i++)
	{
		printf(gameblcak[i]);
	}
}
//画蛇到背景
void drawSnack()
{
	int i;
	for(i=0;arrSnack[i][0]!=0;i++)
	{
		strncpy(&gameblcak[arrSnack[i][0]][arrSnack[i][1]],"■",2);
	}
}
//为蛇产生一个随机位置
void setSnackRandPos()
{
	int nY;
	int nX;
	srand((unsigned int)time(NULL));
	nX=rand()%17+2;
	nY=rand()%18+1;

	arrSnack[0][0]=nY;//行
	arrSnack[0][1]=nX*2;//列
	arrSnack[0][2]=left;

	arrSnack[1][0]=nY;//行
	arrSnack[1][1]=nX*2+2;//列
	arrSnack[1][2]=left;

	arrSnack[2][0]=nY;//行
	arrSnack[2][1]=nX*2+4;//列
	arrSnack[2][2]=left;
	//向背景画蛇
	drawSnack();
}
//消除残留
void cleanSncak()
{
	int i;
	for(i=0;arrSnack[i][0]!=0;i++)
	{
		strncpy(&gameblcak[arrSnack[i][0]][arrSnack[i][1]],"  ",2);
	}
}
//方向按键检测
void checkKey()
{
	//getchar();检测按键但是需要再按回车键
	//getch();同步检测，直接检测按键，但是需要一直等待输入
	//GetAsyncKeyState();异步检测，不需要等待输入，可直接向下运行
	if(GetAsyncKeyState('W'))
		if(down!=arrSnack[0][2])
			getKeyDir=up;
	if(GetAsyncKeyState('A'))
		if(right!=arrSnack[0][2])
			getKeyDir=left;
	if(GetAsyncKeyState('S'))
		if(up!=arrSnack[0][2])
			getKeyDir=down;
	if(GetAsyncKeyState('D'))
		if(left!=arrSnack[0][2])
			getKeyDir=right;
	if(GetAsyncKeyState(VK_UP))
		if(down!=arrSnack[0][2])
			getKeyDir=up;
	if(GetAsyncKeyState(VK_DOWN))
		if(up!=arrSnack[0][2])
			getKeyDir=down;
	if(GetAsyncKeyState(VK_LEFT))
		if(right!=arrSnack[0][2])
			getKeyDir=left;
	if(GetAsyncKeyState(VK_RIGHT))
		if(left!=arrSnack[0][2])
			getKeyDir=right;
}
//判断蛇死亡
bool judgeSncakDie()
{
	if(left==arrSnack[0][2]||right==arrSnack[0][2])	
	{
		if(0==strncmp(&gameblcak[arrSnack[0][0]][arrSnack[0][1]+arrSnack[0][2]],"■",2))
			return false;
	}
	else
	{
		if(0==strncmp(&gameblcak[arrSnack[0][0]+arrSnack[0][2]][arrSnack[0][1]],"■",2))
			return false;
	}
	return true;
}
//蛇移动
void sncakMove()
{
	int i=snackMaxLength;
	//消除残留
	cleanSncak();
	for(i;i>=1;i--)
	{
		//过滤掉非法蛇身
		if(arrSnack[i][0]==0)
		{
			continue;
		}
		//把前一个节点值赋值给后一个节点
		arrSnack[i][0]=arrSnack[i-1][0];
		arrSnack[i][1]=arrSnack[i-1][1];
		arrSnack[i][2]=arrSnack[i-1][2];
	}
	//处理蛇头
	arrSnack[0][2]=getKeyDir;
	if(left==arrSnack[0][2]||right==arrSnack[0][2])
	{
		arrSnack[0][1]+=arrSnack[0][2];
	}
	else
	{
		arrSnack[0][0]+=arrSnack[0][2];
	}
	//向背景画蛇
	drawSnack();
}
//产生随机食物
void food()
{
	int i;
	srand((unsigned int)time(NULL));
	if(false==eatted)
	{
		return;
	}
	while(1)
	{
		bool flag=true;
		line=rand()%16+2;//2--17
		row=rand()%19+2;//2--20
		for(i=0;arrSnack[i][0]!=0;i++)
		{
			if(line==arrSnack[i][0]&&row==arrSnack[i][1])
			{
				flag=false;
				break;
			}
		}
		if(true==flag)
		{
			break;
		}
	}
	//画食物
	strncpy(&gameblcak[line][row*2],"★",2);
	eatted=false;
}
//蛇长大
void snackGrow()
{
	if(line==arrSnack[0][0] && row*2==arrSnack[0][1])
	{
		if(left==arrSnack[length][2])
		{
			arrSnack[length+1][0]=arrSnack[length][0];
			arrSnack[length+1][1]=arrSnack[length][0]+2;
			arrSnack[length+1][2]=arrSnack[length][0];
		}
		if(right==arrSnack[length][2])
		{
			arrSnack[length+1][0]=arrSnack[length][0];
			arrSnack[length+1][1]=arrSnack[length][0]-2;
			arrSnack[length+1][2]=arrSnack[length][0];
		}
		if(up==arrSnack[length][2])
		{
			arrSnack[length+1][0]=arrSnack[length][0]+1;
			arrSnack[length+1][1]=arrSnack[length][0];
			arrSnack[length+1][2]=arrSnack[length][0];
		}
		if(down==arrSnack[length][2])
		{
			arrSnack[length+1][0]=arrSnack[length][0]-1;
			arrSnack[length+1][1]=arrSnack[length][0];
			arrSnack[length+1][2]=arrSnack[length][0];
		}
		length++;
		total_Score++;
		eatted=true;
	}	
}
//记分
void score()
{
	COORD rd;
	//显示游戏得数
	rd.X=53;
	rd.Y=6;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),rd);
	printf("分    数：");
	rd.X=59;
	rd.Y=7;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),rd);
	printf("%d",(total_Score-1)*10);
	//显示难度等级
	rd.X=53;
	rd.Y=9;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),rd);
	printf("难    度：");
	rd.X=59;
	rd.Y=10;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),rd);
	if(temp==1)
		printf("初级");
	if(temp==2)
		printf("中级");
	if(temp==3)
		printf("高级");
	//显示游戏时间
	rd.X=53;
	rd.Y=12;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),rd);
	printf("游戏时间：");
	rd.X=59;
	rd.Y=13;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),rd);
	end=time(NULL);
	int t,minute,second;
	t=end-start;
	second=t%60;
	minute=t/60; 
	printf("%d:%d",minute,second);
}
//闪闪的Mr.Wang
void flash()
{
	COORD rd;
	srand((unsigned int)time(NULL));
	rd.X=50;
	rd.Y=3;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),rd);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),rand()%8+8);
	printf("MADE BY Mr.Wang");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
//暂停功能
void pause()
{
	bool i=true;
	if(GetAsyncKeyState(VK_SPACE))
	{
		COORD rd;
		i=false;
		rd.X=59;
		rd.Y=15;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),rd);
		printf("暂停");
		while(1)
		{
			flash();
			Sleep(100);
			if(GetAsyncKeyState(VK_SPACE))
			{
				i=true;
			}
			if(i==true)
			{	
				break;
			}
		}
	}
}
//游戏结束显示
void endding()
{
	showBackGround();
	printf("\n\t方向键或w a s d 移动 ， 空格暂停");
	flash();
	score();
	COORD rd;
	rd.X=53;
	rd.Y=15;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),rd);
	printf("恭喜你得了%d分",(total_Score-1)*10);
}
void main()
{
	//打开音乐
	myPlaySound();
	//显示首页
	firstPage();
	//检查是否按下空格
   	//checkSpaceKey();
	//关闭音乐
	shutMusic();
	//为蛇产生一个随机位置
	setSnackRandPos();
	start=time(NULL);
	while(1)
	{
		system("cls");
		printf("\t\t  贪吃蛇\n");
		food();
		//蛇长大
		snackGrow();
		//方向按键检测
		checkKey();	
		if(false==judgeSncakDie())
		{
			endding();
			break;
		}
		//蛇移动
		sncakMove();
		//显示游戏背景
		showBackGround();
		printf("\n\t方向键或w a s d 移动 ， 空格暂停");
		flash();
		//显示分数
		score();
		//暂停
		pause();
		Sleep(difficult[temp-1]); 
	}
	COORD rd;
	rd.X=0;
	rd.Y=23;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),rd);
	system("pause");
}
