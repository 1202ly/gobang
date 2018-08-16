#include"game.h"

void Game(int sock)
{
	my_point point_client,point_server;
	char board[ROW][COL];
	Init(board,ROW,COL);
	Print(board,ROW,COL);
	ssize_t s;
	int x;
	int y;
	while(1){
		printf("please input: ");
		scanf("%d%d",&x,&y);
		point_client.row=x-1;
		point_client.col=y-1;
		ClientMove(board,&point_client);
		Print(board,ROW,COL);
		write(sock,(void*)&point_client,sizeof(point_client));
		if(GameState(board,&point_client)=='*'){
			printf("you win!\n");
			break;
		}else if(GameState(board,&point_client)=='p'){
			printf("equal!\n");
			break;
		}
		s=read(sock,(void*)&point_server,sizeof(point_server));
		if(s==0){
			printf("server quit\n");
			return;
		}
		ServerMove(board,&point_server);
		Print(board,ROW,COL);
		if(GameState(board,&point_server)=='#'){
			printf("server win!\n");
			break;
		}else if(GameState(board,&point_server)=='p'){
			printf(" equal!\n");
			break;
		}
	}
}
int main(int argc,char*argv[])
{
	if(argc!=3){
		printf("Usage: ./server [ip][port]");
		return 1;
	}
	int fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd<0){
		printf("socket error\n");
		return 2;
	}
	struct sockaddr_in client;
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=inet_addr(argv[1]);
	client.sin_port=htons(atoi(argv[2]));
	int ss=connect(fd,(const struct sockaddr*)&client,sizeof(client));
	if(ss<0){
		printf("connect error\n");
		return 3;
	}
	printf("#################################\n");
	printf("#####1.start####2.sxit###########\n");
	printf("#################################\n");
	int num;
	while(1)
	{
		printf("please select: ");
		scanf("%d",&num);
		if(num==1){
			Game(fd);
		}else if(num==0){
			break;
		}else{
			printf("please select\n");
	        printf("#################################\n");
	        printf("#####1.start####2.sxit###########\n");
        	printf("#################################\n");
			sleep(2);
		}
	}
	close(fd);
}
