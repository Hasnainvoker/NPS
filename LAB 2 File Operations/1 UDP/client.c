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
	char buff[30];
        int choice=0;
	printf("\n\nEnter the file name: ");
        scanf("%s", buff);
        sntb = sendto(s, buff, sizeof(buff), 0, (struct sockaddr*)&server, len);
        if (sntb == -1) {
            printf("\nMessage sending failed!!");
            exit(0);
        }
        recb = recvfrom(s, buff, sizeof(buff), 0, (struct sockaddr*)&server, &sa);
        if (recb == -1) {
            printf("Message receiving failed");
            exit(0);
        }
        printf("\n%s", buff);
        if (strcmp(buff, "File not present!") == 0) {
            close(s);
            exit(0);
        }
        while(1){
        	printf("\n\n1. Search\n2. Replace\n3. Reorder\n4. Exit\nEnter choice: ");
        	scanf("%d",&choice);
        	sntb = sendto(s, &choice, sizeof(choice), 0, (struct sockaddr*)&server, len);
        	char str[50], str1[50], str2[50];
        	int n, i, j, count;
        	switch(choice){
        		case 1:
        			printf("Enter string to be searched: ");
                		scanf("%s", str);
                		sntb = sendto(s, str, sizeof(str), 0, (struct sockaddr *)&server, len);
                		recb = recvfrom(s, &count, sizeof(count), 0, (struct sockaddr *)&server, &sa);
                		printf("Word found %d number of times!", count);
                		break;
        		case 2:
        			printf("Enter old string: ");
                		scanf("%s", str1);
                		sntb = sendto(s, str1, sizeof(str1), 0, (struct sockaddr *)&server, len);
                		printf("Enter new string: ");
                		scanf("%s", str2);
                		sntb = sendto(s, str2, sizeof(str2), 0, (struct sockaddr *)&server, len);
                		recb = recvfrom(s, buff, sizeof(buff), 0, (struct sockaddr *)&server, &sa);
                		printf("%s\n", buff);
                		break;
        		case 3:
        			recb = recvfrom(s, buff, sizeof(buff), 0, (struct sockaddr *)&server, &sa);
                		printf("%s\n", buff);
                		break;
        		case 4:
        			close(s);
        			exit(0);        			
        	}
        }
}
