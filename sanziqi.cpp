#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib") 
#include"head.h"
#include<time.h>
//��Ϸʱ��
time_t start;
time_t end;
//��ʾ��ҳ
void firstPage()
{
	srand((unsigned int)time(NULL));
	while(1)
	{
		printf("\n\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),rand()%8+8);
		printf("\t\t\t   ��");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),rand()%8+8);
		printf(" ̰");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),rand()%8+8);
		printf(" ��");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),rand()%8+8);
		printf(" ��");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),rand()%8+8);
		printf(" ��\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
		printf("\t\t\t      �ո�ʼ\n\n");
		printf("\t\t    ���������w a s d ���Ʒ���\n\n\n\n");
		printf("\t\t\t�Ѷȣ�");
		if((temp%3)==1)
		{
			printf("  ����   ��   ��");
		}
		if((temp%3)==2)
		{
			printf("   ��  ����   ��");
		}
		if((temp%3)==0)
		{
			printf("   ��   ��  ����");
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
//������
void myPlaySound()
{
	PlaySound("1.wav",NULL,SND_FILENAME | SND_ASYNC);
}
//����Ƿ��¿ո�
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
//�ر�����
void shutMusic() 
{
	PlaySound(NULL,NULL,SND_FILENAME | SND_ASYNC);
}
//��ʾ��Ϸ����
void showBackGround()
{
	int i;	
	for(i=0;i<20;i++)
	{
		printf(gameblcak[i]);
	}
}
//���ߵ�����
void drawSnack()
{
	int i;
	for(i=0;arrSnack[i][0]!=0;i++)
	{
		strncpy(&gameblcak[arrSnack[i][0]][arrSnack[i][1]],"��",2);
	}
}
//Ϊ�߲���һ�����λ��
void setSnackRandPos()
{
	int nY;
	int nX;
	srand((unsigned int)time(NULL));
	nX=rand()%17+2;
	nY=rand()%18+1;

	arrSnack[0][0]=nY;//��
	arrSnack[0][1]=nX*2;//��
	arrSnack[0][2]=left;

	arrSnack[1][0]=nY;//��
	arrSnack[1][1]=nX*2+2;//��
	arrSnack[1][2]=left;

	arrSnack[2][0]=nY;//��
	arrSnack[2][1]=nX*2+4;//��
	arrSnack[2][2]=left;
	//�򱳾�����
	drawSnack();
}
//��������
void cleanSncak()
{
	int i;
	for(i=0;arrSnack[i][0]!=0;i++)
	{
		strncpy(&gameblcak[arrSnack[i][0]][arrSnack[i][1]],"  ",2);
	}
}
//���򰴼����
void checkKey()
{
	//getchar();��ⰴ��������Ҫ�ٰ��س���
	//getch();ͬ����⣬ֱ�Ӽ�ⰴ����������Ҫһֱ�ȴ�����
	//GetAsyncKeyState();�첽��⣬����Ҫ�ȴ����룬��ֱ����������
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
//�ж�������
bool judgeSncakDie()
{
	if(left==arrSnack[0][2]||right==arrSnack[0][2])	
	{
		if(0==strncmp(&gameblcak[arrSnack[0][0]][arrSnack[0][1]+arrSnack[0][2]],"��",2))
			return false;
	}
	else
	{
		if(0==strncmp(&gameblcak[arrSnack[0][0]+arrSnack[0][2]][arrSnack[0][1]],"��",2))
			return false;
	}
	return true;
}
//���ƶ�
void sncakMove()
{
	int i=snackMaxLength;
	//��������
	cleanSncak();
	for(i;i>=1;i--)
	{
		//���˵��Ƿ�����
		if(arrSnack[i][0]==0)
		{
			continue;
		}
		//��ǰһ���ڵ�ֵ��ֵ����һ���ڵ�
		arrSnack[i][0]=arrSnack[i-1][0];
		arrSnack[i][1]=arrSnack[i-1][1];
		arrSnack[i][2]=arrSnack[i-1][2];
	}
	//������ͷ
	arrSnack[0][2]=getKeyDir;
	if(left==arrSnack[0][2]||right==arrSnack[0][2])
	{
		arrSnack[0][1]+=arrSnack[0][2];
	}
	else
	{
		arrSnack[0][0]+=arrSnack[0][2];
	}
	//�򱳾�����
	drawSnack();
}
//�������ʳ��
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
	//��ʳ��
	strncpy(&gameblcak[line][row*2],"��",2);
	eatted=false;
}
//�߳���
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
//�Ƿ�
void score()
{
	COORD rd;
	//��ʾ��Ϸ����
	rd.X=53;
	rd.Y=6;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),rd);
	printf("��    ����");
	rd.X=59;
	rd.Y=7;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),rd);
	printf("%d",(total_Score-1)*10);
	//��ʾ�Ѷȵȼ�
	rd.X=53;
	rd.Y=9;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),rd);
	printf("��    �ȣ�");
	rd.X=59;
	rd.Y=10;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),rd);
	if(temp==1)
		printf("����");
	if(temp==2)
		printf("�м�");
	if(temp==3)
		printf("�߼�");
	//��ʾ��Ϸʱ��
	rd.X=53;
	rd.Y=12;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),rd);
	printf("��Ϸʱ�䣺");
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
//������Mr.Wang
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
//��ͣ����
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
		printf("��ͣ");
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
//��Ϸ������ʾ
void endding()
{
	showBackGround();
	printf("\n\t�������w a s d �ƶ� �� �ո���ͣ");
	flash();
	score();
	COORD rd;
	rd.X=53;
	rd.Y=15;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),rd);
	printf("��ϲ�����%d��",(total_Score-1)*10);
}
void main()
{
	//������
	myPlaySound();
	//��ʾ��ҳ
	firstPage();
	//����Ƿ��¿ո�
   	//checkSpaceKey();
	//�ر�����
	shutMusic();
	//Ϊ�߲���һ�����λ��
	setSnackRandPos();
	start=time(NULL);
	while(1)
	{
		system("cls");
		printf("\t\t  ̰����\n");
		food();
		//�߳���
		snackGrow();
		//���򰴼����
		checkKey();	
		if(false==judgeSncakDie())
		{
			endding();
			break;
		}
		//���ƶ�
		sncakMove();
		//��ʾ��Ϸ����
		showBackGround();
		printf("\n\t�������w a s d �ƶ� �� �ո���ͣ");
		flash();
		//��ʾ����
		score();
		//��ͣ
		pause();
		Sleep(difficult[temp-1]); 
	}
	COORD rd;
	rd.X=0;
	rd.Y=23;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),rd);
	system("pause");
}
