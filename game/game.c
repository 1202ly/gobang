#include"game.h"

//初始化棋盘
void Init(char board[ROW][COL],int row,int col)
{
	memset(board,' ',row*col*sizeof(char));
	FILE* fp=fopen("./test.c","a+");
	if(fp==NULL){
		printf("fopen error\n");
	}else{
		fputs("Test1: game init is OK!",fp);
	}
}

//打印棋盘
void Print(char board[ROW][COL],int row,int col)
{
	int i=0;
	printf("     | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 \n");
	for(;i<row;i++)
	{
		printf("%2d",i+1);
		int j=0;
		for(;j<col;j++)
		{
			if(j==col-1)
			{
				printf(" %c \n",board[i][j]);
				if(i!=row-1)
				{
					printf(" ----|---|---|---|---|---|---|---|---|---\n");
				}
				break;
			}
			printf(" %c ",board[i][j]);
			printf("|");
		}
	}
	printf("\n");
}
int IsFull(char board[ROW][COL])
{
	size_t i=0;
	for(;i<ROW;i++){
		size_t j=0;
		for(;j<COL;j++){
			if(board[i][j]==' ')
				return 0;
		}
	}
	return 1;
}
//客户端移动
void ClientMove(char board[ROW][COL],my_point* point)
{
	CommonMove(board,point,'*');
}

//服务器移动
void ServerMove(char board[ROW][COL],my_point* point)
{
	CommonMove(board,point,'#');
}

//共同移动
void CommonMove(char board[ROW][COL],my_point* point,char ch)
{
	if(NULL==point){
		return;
	}
	int x=point->row;
	int y=point->col;
	while(1){
		if(x>=0&&x<ROW&&y>=0&&y<COL){
			if(board[x][y]==' ')
			{
				board[x][y]=ch;
				point->row=x;
				point->col=y;
				break;
			}else{
				printf("input error,please input again: ");
				scanf("%d%d",&x,&y);
				x--;
				y--;
			}
		}else{
				printf("input error,please input again: ");
				scanf("%d%d",&x,&y);
				x--;
				y--;

		}
	}
}
int ColFull(char board[ROW][COL],my_point* point)
{
	int x=point->row;
	int y=point->col;
	int count=1;
	while(x-1>=0){
		if(board[x][y]!=board[x-1][y]){
			break;
		}
		count++;
		if(count==5){
			return count;
		}
		x--;
	}
	count=1;
	while(x+1<=ROW){
		if(board[x][y]==board[x+1][y]){
			count++;
			if(count==5){
				return count;
			}
			x++;
		}else{
			return 0;
		}
	}
	return 0;
}
int RowFull(char board[ROW][COL],my_point* point)
{
	int x=point->row;
	int y=point->col;
	int count=1;
	while(y-1>=0){
		if(board[x][y]!=board[x][y-1]){
			break;
		}
		count++;
		if(count==5){
			return count;
		}
		y--;
	}
	count=1;
	while(y+1<=COL){
		if(board[x][y]==board[x][y+1]){
			count++;
			if(count==5){
				return count;
			}
			y++;
		}else{
			return 0;
		}
	}
	return 0;
}
int LeftFull(char board[ROW][COL],my_point* point)
{
	int x=point->row;
	int y=point->col;
	int count=1;
	while(x-1>=0&&y-1>=0){
		if(board[x][y]!=board[x-1][y-1]){
			break;
		}
		count++;
		if(count==5){
			return count;
		}
		x--;
		y--;
	}
	count=1;
	while(x+1<=ROW&&y+1<=COL){
		if(board[x][y]==board[x++][y+1]){
			count++;
			if(count==5){
				return count;
			}
			x++;
			y++;
		}else{
			return 0;
		}
	}
	return 0;
}
int RightFull(char board[ROW][COL],my_point* point)
{
	int x=point->row;
	int y=point->col;
	int count=1;
	while(x-1>=0&&y+1<=COL){
		if(board[x][y]!=board[x-1][y+1]){
			break;
		}
		count++;
		if(count==5){
			return count;
		}
		x--;
		y++;
	}
	count=1;
	while(y+1<=ROW){
		if(board[x][y]==board[x+1][y-1]){
			count++;
			if(count==5){
				return count;
			}
			x++;
			y--;
		}else{
			return 0;
		}
	}
	return 0;
}
//判断输赢
char GameState(char board[ROW][COL],my_point* point)
{
	if(NULL==point)
	{
		return 'e';
	}
	if(ColFull(board,point)==5){
		return board[point->row][point->col];
	}
	if(RowFull(board,point)==5){
		return board[point->row][point->col];
	}
	if(LeftFull(board,point)==5){
		return board[point->row][point->col];
	}
	if(RightFull(board,point)==5){
		return board[point->row][point->col];
	}
	if(IsFull(board)){
		return 'p';
	return 'g';
	}
}
