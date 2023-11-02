#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
struct dns{
     char host[50];
     char ip[20];
};
int main(){
        struct dns database[5];
        strcpy(database[0].host,"www.google.com"); strcpy(database[0].ip,"142.251.33.100");
        strcpy(database[1].host,"www.youtube.com"); strcpy(database[1].ip,"142.250.217.78");
        strcpy(database[2].host,"www.chatgpt.com"); strcpy(database[2].ip,"172.67.176.22");
        strcpy(database[3].host,"www.github.com"); strcpy(database[3].ip,"140.82.114.3");
        strcpy(database[4].host,"www.microsoft.com"); strcpy(database[4].ip,"104.73.1.162");
	int s, r, l, recb, sntb, x, ns;
	printf("Input port number: ");
	scanf("%d",&x);
	socklen_t len;
	struct sockaddr_in server, client;
	s = socket(AF_INET,SOCK_STREAM,0);
	if(s==-1){
		printf("\nSocket creation error!!");
		exit(0);
	}
	printf("\nSocket created.");
	server.sin_family = AF_INET;
	server.sin_port = htons(x);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	r = bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1){
		printf("\nBinding error!!");
		exit(0);
	}
	printf("\nSocket binded.");
	l=listen(s,1);
	if(l==-1){
		close(s);
		exit(0);
	}
	printf("\nSocket listening...");
	len = sizeof(client);
	ns = accept(s,(struct sockaddr*)&client,&len);
	if(ns==-1){
		close(s);
		exit(0);
	}
        char buff[50];
	recv(ns, buff, sizeof(buff), 0);
	printf("\nsearching...");
	char reply[50];
	strcpy(reply, "-1");
	for(int i=0; i<5; i++)
	        if(strcmp(buff,database[i].host)==0)
	                strcpy(reply,database[i].ip);
	strcpy(buff,reply);
	send(ns, buff, sizeof(buff), 0);
	printf("\nsent");
	close(s);
}

