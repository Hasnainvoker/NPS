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
	
	while(1){
		int choice, pid;
		char buff[50], regno[10], name[10], subs[10][10], marks[10], add[20], sem[5], dept[10], sec[5];
		printf("\n\nWhat would you like to enter?\n1. Registration Number\n2. Name of the Student\n3. Subject Code\n4. Exit\n>");
		scanf("%d", &choice);
		sendto(s, &choice, sizeof(choice),0, (struct sockaddr*)&server, len);
		switch(choice){
			case 1:
				printf("Enter Registration Number: ");	
				scanf("%s", buff);
				sendto(s, buff, sizeof(buff),0, (struct sockaddr*)&server,len);
				recvfrom(s, &pid, sizeof(pid),0, (struct sockaddr*)&server, &sa);
				recvfrom(s, &name, sizeof(name),0, (struct sockaddr*)&server, &sa);
				recvfrom(s, &add, sizeof(add),0, (struct sockaddr*)&server, &sa);
				printf("PID: %d\n",pid);
				printf("Name: %s\n",name);
				printf("Address: %s\n",add);
				break;
			case 2:
				printf("Enter Student Name: ");	
				scanf("%s", buff);
				sendto(s, buff, sizeof(buff),0, (struct sockaddr*)&server, len);
				recvfrom(s, &pid, sizeof(pid),0, (struct sockaddr*)&server, &sa);
				recvfrom(s, &dept, sizeof(dept),0, (struct sockaddr*)&server, &sa);
				recvfrom(s, &sem, sizeof(sem),0, (struct sockaddr*)&server, &sa);
				recvfrom(s, &sec, sizeof(sec),0, (struct sockaddr*)&server, &sa);
				recvfrom(s, &subs, sizeof(subs),0, (struct sockaddr*)&server, &sa);
				printf("PID: %d\n",pid);
				printf("Department: %s\n",dept);
				printf("Semester: %s\n",sem);
				printf("Section: %s\n",sec);
				printf("Courses Registered: \n");
				for(int i=0; i<2; i++)
					printf("%d. %s\n", i+1, subs[i]);
				break;
			case 3:
				printf("Enter Subject Code: ");	
				scanf("%s", buff);
				sendto(s, buff, sizeof(buff),0, (struct sockaddr*)&server, len);
				recvfrom(s, &pid, sizeof(pid),0, (struct sockaddr*)&server, &sa);
				recvfrom(s, &marks, sizeof(marks),0, (struct sockaddr*)&server, &sa);
				printf("PID: %d\n",pid);
				printf("Marks: %s\n",marks);
				break;	
			case 4:
				close(s);
				exit(0);	
		}	
	}
}

