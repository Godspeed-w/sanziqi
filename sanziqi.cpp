#include<stdio.h>
#include<windows.h>

//游戏背景(玩家：#； 电脑：X)
char background[6][11]={"  -------\n",
					    "3 | | | |\n",
					    "2 | | | |\n",
					    "1 | | | |\n",
					    "  -------\n",
					    "   1 2 3 \n"};

//游戏数据 0:空 1:玩家 2:电脑
int board[3][3]={{0,0,0},
				{0,0,0},
				{0,0,0}};

//绘制游戏背景
void drawBackground(){
	//system("cls");
	for(int i=0;i<6;i++){
		printf(background[i]);
	}
	printf("~~~~~~~~~~~~~~~~~~~~\n");
	for(int j=0;j<3;j++){
		for(int k=0;k<3;k++){
			printf("%d ",board[j][k]);
		}
		printf("\n");
	}
	printf("\n输入象限坐标：左下角(1,1),右上角(3,3)\n");
}

//玩家输入坐标(要点：1、判断坐标位置是否合法；2、坐标位置与游戏数据、背景棋盘位置转换)
void human_play(){
	int x=0;
	int y=0;
	while(1){
		printf("横坐标：");
		scanf("%d",&x);
		printf("纵坐标：");
		scanf("%d",&y);
		if(x<1||x>3||y<1||y>3){
			printf("坐标有误 \n");
		}else if(board[3-y][x-1]!=0){
			printf("该位置已经有棋子了!!\n");
		}else{
			//把玩家下棋位置记录在坐标数据中{坐标转换规则：玩家输入坐标→游戏数据→背景数据==(x,y)→(3-y,x-1)→(4-y,2x+1)}
			board[3-y][x-1]=1;
			background[4-y][2*x+1]='#';
			break;
		}
	}
}

void ai_play(){
	int x=0;
	int y=0;
	while(1){
		printf("横坐标：");
		scanf("%d",&x);
		printf("纵坐标：");
		scanf("%d",&y);
		if(x<1||x>3||y<1||y>3){
			printf("坐标有误 \n");
		}else if(board[3-y][x-1]!=0){
			printf("该位置已经有棋子了!!\n");
		}else{
			//把玩家下棋位置记录在坐标数据中{坐标转换规则：玩家输入坐标→游戏数据→背景数据==(x,y)→(3-x,y-1)→(4-x,2y+1)}
			board[3-y][x-1]=2;
			background[4-y][2*x+1]='*';
			break;
		}
	}
}

//判断当前深度，即判断棋盘还有多少空格
int currentDepth(){
	int depth=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(board[i][j]==0)
				depth++;
		}
	}
	printf("深度%d\n",depth);
	return depth;
}

//搜索树估值算法
void value(){
	
}

//极大极小算法
void miniMaxSearch(){
	
}

//判断胜负 0:平局 1：玩家胜 2：电脑胜 3：游戏还未结束
int judge_winner(){
	for(int i=0;i<3;i++){
		//横向判断
		if((board[i][0]==1)&&(board[i][1]==1)&&(board[i][2]==1))
			return 1;
		if((board[i][0]==2)&&(board[i][1]==2)&&(board[i][2]==2))
			return 2;
		//纵向判断
		if((board[0][i]==1)&&(board[1][i]==1)&&(board[2][i]==1))
			return 1;
		if((board[0][i]==2)&&(board[1][i]==2)&&(board[2][i]==2))
			return 2;
	}
	//斜向判断
	if(board[1][1]==1){
		if((board[0][0]==board[2][2]&&board[0][0]==1)||(board[0][2]==board[2][0]&&board[0][2]==1))
			return 1;
	}
	if(board[1][1]==2){
		if((board[0][0]==board[2][2]&&board[0][0]==2)||(board[0][2]==board[2][0]&&board[0][2]==2))
			return 2;
	}
	if(currentDepth()==0){
		return 0;	
	}else{
		return 3;
	}
}

//展示获胜方，结束游戏
int show_winner(){
	switch(judge_winner()){
		case 0:
			printf("平局!!\n");
			return 1;
			break;
		case 1:
			printf("你赢了!!\n");
			return 1;
			break;
		case 2:
			printf("电脑获胜!!\n");
			return 1;
			break;
		default:
			return 0;
			break;
	}
}

//主函数入口
int main(){
	drawBackground();
	while(1){
		human_play();
		drawBackground();
		if(show_winner()==1)
			break;
		
		ai_play();
		drawBackground();
		if(show_winner()==1)
			break;
	}
	printf("\nGAME OVER!\n");
	return 0;
}
