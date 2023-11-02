
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
int main(){
	int s, r, recb, sntb, x, ca;
	printf("Input port number: ");
	scanf("%d",&x);
	socklen_t len;
	struct sockaddr_in server, client;
	s = socket(AF_INET,SOCK_DGRAM,0);
	if(s==-1){
		printf("\nSocket creation error!!");
		exit(0);
	}
	printf("\nSocket created.");
	server.sin_family = AF_INET;
	server.sin_port = htons(x);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	len = sizeof(client);
	ca = sizeof(client);
	r = bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1){
		printf("\nBinding error!!");
		exit(0);
	}
	printf("\nSocket binded.");
	char buff[50];
	int length;
	
	while(1){
		recvfrom(s, buff, sizeof(buff), 0, (struct sockaddr*)&client, &ca);
		if(strcmp(buff, "Halt")==0)
		{
			close(s);
			exit(0);
		}
		printf("\nString received: \n%s\n",buff);
		length = strlen(buff);
		//printf("%d\n",length);
		char revbuf[50];
		int a=0, e=0, i=0, o=0, u=0, j;
		for(j=0; j<length ; j++)
		{	revbuf[length-j-1]=buff[j];
			switch(buff[j])
			{
				case 'a':
				case 'A': a++; break;
				
				case 'e':
				case 'E': e++; break;
				
				case 'i':
				case 'I': i++; break;
				
				case 'o':
				case 'O': o++; break;
				
				case 'u':
				case 'U': u++; break;				
			}
		}		
		//printf("%d %d %d %d %d\n",a,e,i,o,u);
		revbuf[length] = '\0';
		//printf("%s\n",revbuf);
		char result[20];
		if(strcmp(revbuf, buff)==0)
			strcpy(result, "Palindrome");
		else
			strcpy(result, "Not a palindrome");
		//printf("%s\n",result);

		sendto(s, &result, sizeof(result), 0, (struct sockaddr*)&client,len);
		sendto(s, &length, sizeof(length), 0, (struct sockaddr*)&client,len);
		sendto(s, &a, sizeof(a), 0, (struct sockaddr*)&client,len);
		sendto(s, &e, sizeof(e), 0, (struct sockaddr*)&client,len);	
		sendto(s, &i, sizeof(i), 0, (struct sockaddr*)&client,len);
		sendto(s, &o, sizeof(o), 0, (struct sockaddr*)&client,len);
		sendto(s, &u, sizeof(u), 0, (struct sockaddr*)&client,len);
	}
	close(s);
}

