#include<stdio.h>
#include<windows.h>

//��Ϸ����(��ң�#�� ���ԣ�X)
char background[6][11]={"  -------\n",
					    "3 | | | |\n",
					    "2 | | | |\n",
					    "1 | | | |\n",
					    "  -------\n",
					    "   1 2 3 \n"};

//��Ϸ���� 0:�� 1:��� 2:����
int board[3][3]={{0,0,0},
				{0,0,0},
				{0,0,0}};

//������Ϸ����
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
	printf("\n�����������꣺���½�(1,1),���Ͻ�(3,3)\n");
}

//�����������(Ҫ�㣺1���ж�����λ���Ƿ�Ϸ���2������λ������Ϸ���ݡ���������λ��ת��)
void human_play(){
	int x=0;
	int y=0;
	while(1){
		printf("�����꣺");
		scanf("%d",&x);
		printf("�����꣺");
		scanf("%d",&y);
		if(x<1||x>3||y<1||y>3){
			printf("�������� \n");
		}else if(board[3-y][x-1]!=0){
			printf("��λ���Ѿ���������!!\n");
		}else{
			//���������λ�ü�¼������������{����ת��������������������Ϸ���ݡ���������==(x,y)��(3-y,x-1)��(4-y,2x+1)}
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
		printf("�����꣺");
		scanf("%d",&x);
		printf("�����꣺");
		scanf("%d",&y);
		if(x<1||x>3||y<1||y>3){
			printf("�������� \n");
		}else if(board[3-y][x-1]!=0){
			printf("��λ���Ѿ���������!!\n");
		}else{
			//���������λ�ü�¼������������{����ת��������������������Ϸ���ݡ���������==(x,y)��(3-x,y-1)��(4-x,2y+1)}
			board[3-y][x-1]=2;
			background[4-y][2*x+1]='*';
			break;
		}
	}
}

//�жϵ�ǰ��ȣ����ж����̻��ж��ٿո�
int currentDepth(){
	int depth=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if(board[i][j]==0)
				depth++;
		}
	}
	printf("���%d\n",depth);
	return depth;
}

//��������ֵ�㷨
void value(){
	
}

//����С�㷨
void miniMaxSearch(){
	
}

//�ж�ʤ�� 0:ƽ�� 1�����ʤ 2������ʤ 3����Ϸ��δ����
int judge_winner(){
	for(int i=0;i<3;i++){
		//�����ж�
		if((board[i][0]==1)&&(board[i][1]==1)&&(board[i][2]==1))
			return 1;
		if((board[i][0]==2)&&(board[i][1]==2)&&(board[i][2]==2))
			return 2;
		//�����ж�
		if((board[0][i]==1)&&(board[1][i]==1)&&(board[2][i]==1))
			return 1;
		if((board[0][i]==2)&&(board[1][i]==2)&&(board[2][i]==2))
			return 2;
	}
	//б���ж�
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

//չʾ��ʤ����������Ϸ
int show_winner(){
	switch(judge_winner()){
		case 0:
			printf("ƽ��!!\n");
			return 1;
			break;
		case 1:
			printf("��Ӯ��!!\n");
			return 1;
			break;
		case 2:
			printf("���Ի�ʤ!!\n");
			return 1;
			break;
		default:
			return 0;
			break;
	}
}

//���������
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
