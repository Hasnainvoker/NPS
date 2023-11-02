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
        int s, r, recb, sntb, x;
	socklen_t len;
	printf("Input port number: ");
	scanf("%d",&x);
	struct sockaddr_in server, client;
	char buff1[50], buff2[50];
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
	printf("\nOriginal Process, PID : %d && PPID : %d\n" ,getpid() , getppid( )) ;
	int pid = fork();
    	while (1){
                if (pid > 0) {
            		recv(s, buff1, sizeof(buff1), 0);
			printf("\n\n\nPID: %d\nPPID: %d\n", pid, getppid());
            		if (strcmp(buff1, "BYE") == 0)
               		        break;
            		printf("Parent - Message Recieved: ");
            		printf("%s\n", buff1);
        	} 
        	else{
        		printf("\n\n\nPID: %d\nPPID: %d\n", pid, getppid());
            		printf("Child - Type Message: ");
            		scanf("%s", buff2);
            		send(s, buff2, sizeof(buff2), 0);
            		if (strcmp(buff2, "BYE") == 0)
                		break;
        	}
    }
    close(s);
}
