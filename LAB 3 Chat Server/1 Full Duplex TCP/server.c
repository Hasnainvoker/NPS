#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>
int main(){
	int s, r, l, recb, sntb, x, ns;
	printf("Input port number: ");
	scanf("%d",&x);
	socklen_t len;
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
	printf("\nOriginal Process, PID : %d && PPID : %d\n" ,getpid() , getppid( )) ;
    	int pid = fork();
    	while (1) {
        	if (pid > 0) {
			printf("\n\n\nPID: %d\nPPID: %d\n", pid, getppid());
            		printf("Parent - Type message: ");
            		scanf("%s", buff2);
            		send(ns, buff2, sizeof(buff2), 0);
            		if (strcmp(buff2, "BYE") == 0)
                		break;
        	} 
        	else {
            		recv(ns, buff1, sizeof(buff1), 0);
			printf("\n\n\nPID: %d\nPPID: %d\n", pid, getppid());
			if (strcmp(buff1, "BYE") == 0){
			        send(ns, "BYE\0", 4, 0);
                		break;
                	}
            		printf("Child - Message Recieved: ");
            		printf("%s\n", buff1);
        	}
    	}
    	close(ns);
    	close(s);
    	if(pid==0)
    	        kill(getppid(),SIGTERM);
}

