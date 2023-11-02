#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#define LISTENQ 2
int main()
{
	int s,r,recb,sntb,x,ns;
	printf("Input port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[100], str[100], strx[100];
	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1)
	{
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=htonl(INADDR_ANY);

	r=bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{
		printf("\nBinding error.");
		exit(0);
	}
	printf("\nSocket binded.");

	r=listen(s,LISTENQ);
	if(r==-1)
	{
		close(s);
		exit(0);
	}
	printf("\nSocket listening.\n");
	FILE *fp;
		char temp[30];
		fp = fopen("text.txt", "r");		
		while(fgets(temp, 30, fp) != NULL) {
		strcat(strx, temp);
		}
		fclose(fp);
              printf("File contents: %s", strx);
	int childpid, n, no_of_clients=0;

	for(;;){
	len=sizeof(client);
	ns=accept(s,(struct sockaddr*)&client, &len);
	if(ns==-1)
	{
		close(s);
		exit(0);
	}
	printf("\nSocket accepting.\n");

	if(no_of_clients==2)
	{
		printf("\nMore than 2 clients!\n");
		close(ns);
		break;
	}
	no_of_clients++;
	
	if ( (childpid = fork ()) == 0 ) {
	close (s);	
	char ipport[50];
	n = recv(ns, ipport, sizeof(ipport),0);
	if (n < 0){
	printf("%s\n", "Read error");
	exit(0);
	}
	printf("Port number and IP addresses are: %d, %s\n", x, ipport);
	n = recv(ns, buff, sizeof(buff),0);
	if (n < 0){
	printf("%s\n", "Read error");
	exit(0);
	}
	FILE *fptr;
	fptr=fopen("text.txt","a");
	fprintf(fptr, "%s", buff);
	fclose(fptr);
	
	if(no_of_clients==2)
	{
		FILE *fp;
		char temp[30];
		fp = fopen("text.txt", "r");		
		while(fgets(temp, 30, fp) != NULL) {
		strcat(str, temp);
		}
		fclose(fp);
		printf("\nFile contents: %s", str);
	}
	exit(0);
	}
close(ns);
}
}
