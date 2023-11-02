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
	struct sockaddr_in server, client;
	s = socket(AF_INET,SOCK_DGRAM,0);
	if(s==-1){
		printf("\nSocket creation error!!");
		exit(0);
	}
	printf("\nSocket created.");
	server.sin_family = AF_INET;
	server.sin_port = htons(x);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	len = sizeof(server);
	sa = sizeof(server);
	
	char buff[50], result[20];
	int length, a, e, i, o, u;
	
	while(1){
	printf("\nEnter the string:");
		scanf("%s", buff);
		sendto(s, buff, sizeof(buff),0, (struct sockaddr*)&server, len);
		if(strcmp(buff, "Halt")==0)
		{		
			printf("Closing the socket");	
			close(s);
			exit(0);
		}		
		recvfrom(s, result, sizeof(result), 0, (struct sockaddr*)&server, &sa);
		recvfrom(s, &length, sizeof(length), 0, (struct sockaddr*)&server, &sa);		
		recvfrom(s, &a, sizeof(a),0, (struct sockaddr*)&server, &sa);	
		recvfrom(s, &e, sizeof(e),0, (struct sockaddr*)&server, &sa);	
		recvfrom(s, &i, sizeof(i),0, (struct sockaddr*)&server, &sa);	
		recvfrom(s, &o, sizeof(o),0, (struct sockaddr*)&server, &sa);	
		recvfrom(s, &u, sizeof(u),0, (struct sockaddr*)&server, &sa);	
		printf("Size of the string = %d\n", length);
		printf("%s\n",result);
		printf("Vowels count:\n");
		printf("A = %d\n", a);
		printf("E = %d\n", e);
		printf("I = %d\n", i);
		printf("O = %d\n", o);
		printf("U = %d\n", u);	
	}
}
