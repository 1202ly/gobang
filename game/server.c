#include"game.h"

int main(int argc,char*argv[])
{
	if(argc!=3){
		printf("Usage: ./server [ip] [port]\n");
		return 1;
	}
	int fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd<0){
		printf("socket error\n");
		return 2;
	}
	struct sockaddr_in local;
	local.sin_family=AF_INET;
	local.sin_addr.s_addr=inet_addr(argv[1]);
	local.sin_port=htons(atoi(argv[2]));
	int ret=bind(fd,(const struct sockaddr*)&local,sizeof(local));
	if(ret<0){
		printf("bind error\n");
		return 3;
	}
	ret=listen(fd,5);
	if(ret<0){
		printf("listen error\n");
		return 4;
	}
	while(1){
		struct sockaddr_in client;
		socklen_t len;
		int client_sock=accept(fd,(struct sockaddr*)&client,&len);
		if(client_sock<0){
			continue;
		}
		ssize_t s;
		my_point point_server,point_client;
		char board[ROW][COL];
		Init(board,ROW,COL);
		int x,y;
		while(1){
			s=read(client_sock,(void*)&point_client,sizeof(point_client));
			if(s==0){
				printf("client quit!\n");
				close(client_sock);
				return 0;
			}
			ClientMove(board,&point_client);
			Print(board,ROW,COL);
			if(GameState(board,&point_client)=='*')
			{
				printf("client win!\n");
				break;
			}else if(GameState(board,&point_client)=='p'){
				printf("equal!\n");
				break;
			}
			printf("please input: ");
			scanf("%d%d",&x,&y);
			point_server.row=x-1;
			point_server.col=y-1;
			ServerMove(board,&point_server);
			Print(board,ROW,COL);
			write(client_sock,(void*)&point_server,sizeof(point_server));
			if(GameState(board,&point_client)=='#'){
				printf("you win!\n");
				break;
			}else if(GameState(board,&point_client)=='p'){
				printf("equal! \n");
				break;
			}
		}
	}
	close(fd);
}
