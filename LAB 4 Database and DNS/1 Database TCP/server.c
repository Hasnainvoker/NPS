#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
struct student{
	char regno[10];
	char name[10];
	char subs[10][10];
	char marks[10][10];
	char add[20];
	char sem[5];
	char dept[10];
	char sec[5];
};
int main(){

        struct student students[3];
	strcpy(students[0].regno,"210911084"); strcpy(students[1].regno,"210911086"); strcpy(students[2].regno,"210911088");
	strcpy(students[0].name,"Prasanth"); strcpy(students[1].name,"Bella"); strcpy(students[2].name,"Cathy");
	strcpy(students[0].add,"Delhi"); strcpy(students[1].add,"Mumbai"); strcpy(students[2].add,"Hyderabad"); 
	strcpy(students[0].sem,"5"); strcpy(students[1].sem,"5"); strcpy(students[2].sem,"5"); 
	strcpy(students[0].dept,"CSE"); strcpy(students[1].dept,"ECE"); strcpy(students[2].dept,"ICT"); 
	strcpy(students[0].sec,"A"); strcpy(students[0].sec,"B"); strcpy(students[0].sec,"B"); 
	strcpy(students[0].subs[0], "CSE3125"); strcpy(students[0].marks[0], "96"); strcpy(students[0].subs[1], "CSE3126"); strcpy(students[0].marks[1], "80"); 
	strcpy(students[1].subs[0], "ICT3155"); strcpy(students[1].marks[0], "75");
	strcpy(students[2].subs[0], "ICT3156"); strcpy(students[2].marks[0], "99"); strcpy(students[2].subs[1], "ICT3157"); strcpy(students[2].marks[1], "90");
	printf("Student details:");
	for(int i=0; i<3; i++){
		printf("\n\nRegistration Number: %s", students[i].regno);
		printf("\nName: %s", students[i].name);
		printf("\nAddress: %s", students[i].add);
		printf("\nSemester: %s", students[i].sem);
		printf("\nDepartment: %s", students[i].dept);
		printf("\nSection: %s", students[i].sec);
		printf("\nSubject\t\tMarks");
		for(int j=0; j<2; j++){			
			printf("\n%s\t\t%s", students[i].subs[j], students[i].marks[j]);
		}
	}
	printf("\n\n");
	
	int s, r, l, recb, sntb, x, ns;
	printf("Input port number: ");
	scanf("%d",&x);
	socklen_t len;
	struct sockaddr_in server, client;
	char buff[50];
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
	while(1){		
		//recv(ns, &choice, sizeof(choice), 0);
		//send(ns, &pos, sizeof(pos), 0);
		int choice, pid;		
		char buff[50], regno[10], name[10], subs[10][10], marks[10], add[20], sem[5], dept[10], sec[5];
		recv(ns, &choice, sizeof(choice), 0);
		if(choice==4)
			break;
		recv(ns, buff, sizeof(buff), 0);
		int pid1=fork();
		if(pid1==0){	
			pid=getpid();
			if(choice==1){
				for(int i=0; i<3; i++){
					if(strcmp(students[i].regno,buff)==0){
						strcpy(name, students[i].name);
						strcpy(add, students[i].add);
					}
				}
				send(ns, &pid, sizeof(pid), 0);
				send(ns, &name, sizeof(name), 0);
				send(ns, &add, sizeof(add), 0);
			}		
			exit(0);
		}
	else{
		int pid2=fork();
		if(pid2==0){	
			pid=getpid();
			if(choice==2){
				for(int i=0; i<3; i++){
					if(strcmp(students[i].name,buff)==0){
						strcpy(dept, students[i].dept);
						strcpy(sem, students[i].sem);
						strcpy(sec, students[i].sec);
						for(int j=0; j<2; j++)
							strcpy(subs[j], students[i].subs[j]);
					}
				}
				send(ns, &pid, sizeof(pid), 0);
				send(ns, &dept, sizeof(dept), 0);
				send(ns, &sem, sizeof(sem), 0);
				send(ns, &sec, sizeof(sec), 0);
				send(ns, &subs, sizeof(subs), 0);
			}
			exit(0);
		}
	else{
		int pid3=fork();
		if(pid3==0){	
			pid=getpid();
			if(choice==3){
				for(int i=0; i<3; i++){
					for(int j=0; j<2; j++){
						if(strcmp(students[i].subs[j],buff)==0){
							strcpy(marks, students[i].marks[j]);
						}
					}
				}
				send(ns, &pid, sizeof(pid), 0);
				send(ns, &marks, sizeof(marks), 0);
			}
			exit(0);
		}
	}
	}
	}
	close(s);
	exit(0);
}
