#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>
int main(){
	int s, r, recb, sntb, x, sa;
	socklen_t len;
	printf("Input port number: ");
	scanf("%d",&x);
	struct sockaddr_in server;
	s = socket(AF_INET,SOCK_STREAM,0);
	if(s==-1){
		printf("\nSocket creation error!!");
		exit(0);
	}
	printf("\nSocket created.");
	server.sin_family = AF_INET;
	server.sin_port = htons(x);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	r = connect(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1){
		printf("\nConnection error!!");
		exit(0);
	}
	printf("\nSocket Connected.");
	char buff[50];
	printf("\nEnter Host name: ");
	scanf("%s",buff);
	send(s, buff, sizeof(buff), 0);
	recv(s, buff, sizeof(buff), 0);
	if(strcmp(buff,"-1")==0)
	        printf("Host not found");
	else
	        printf("%s", buff);
	close(s);
}

