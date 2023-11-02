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
	while(1){
		int choice, pid;
		char buff[50], regno[10], name[10], subs[10][10], marks[10], add[20], sem[5], dept[10], sec[5];
		printf("\n\nWhat would you like to enter?\n1. Registration Number\n2. Name of the Student\n3. Subject Code\n4. Exit\n>");
		scanf("%d", &choice);
		send(s, &choice, sizeof(choice), 0);
		switch(choice){
			case 1:
				printf("Enter Registration Number: ");	
				scanf("%s", buff);
				send(s, buff, sizeof(buff) ,0);
				recv(s, &pid, sizeof(pid),0);
				recv(s, &name, sizeof(name),0);
				recv(s, &add, sizeof(add),0);
				printf("PID: %d\n",pid);
				printf("Name: %s\n",name);
				printf("Address: %s\n",add);
				break;
			case 2:
				printf("Enter Student Name: ");	
				scanf("%s", buff);
				send(s, buff, sizeof(buff), 0);
				recv(s, &pid, sizeof(pid),0);
				recv(s, &dept, sizeof(dept),0);
				recv(s, &sem, sizeof(sem),0);
				recv(s, &sec, sizeof(sec),0);
				recv(s, &subs, sizeof(subs),0);
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
				send(s, buff, sizeof(buff), 0);
				recv(s, &pid, sizeof(pid),0);
				recv(s, &marks, sizeof(marks),0);
				printf("PID: %d\n",pid);
				printf("Marks: %s\n",marks);
				break;	
			case 4:
				close(s);
				exit(0);	
		}	
	}
}

