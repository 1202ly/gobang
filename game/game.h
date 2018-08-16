#pragma once 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<unistd.h>


#define ROW 10
#define COL 10



typedef struct my_point{
	int row;
	int col;
}my_point;

//初始化棋盘
void Init(char board[ROW][COL],int row,int col);

//打印棋盘
void Print(char board[ROW][COL],int row,int col);

//客户端移动
void ClientMove(char board[ROW][COL],my_point* point);

//服务器移动
void ServerMove(char board[ROW][COL],my_point* point);

//共同移动
void CommonMove(char board[ROW][COL],my_point* point,char ch);

//判断输赢
char GameState(char board[ROW][COL],my_point* point);
