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
	
	int array[10], buffer[10], choice, key, pos=-1, size, temp, odd[10] = {0}, even[10] = {0}, a =0, b = 0;	
	printf("\nEnter the no of elements in array:");
	scanf("%d", &size);
	printf("\nEnter the elements in array:");
	for(int i=0 ; i<size ; i++)
		scanf("%d", &array[i]);
	send(s, array, sizeof(array), 0);
	send(s, &size, sizeof(size), 0);
	while(1){
		printf("\n\n1. Search for a number");	
		printf("\n2. Sort in ascending order");
		printf("\n3. Sort in descending order");
		printf("\n4. Split into odd and even arrays");
		printf("\n5. Exit");
		printf("\nEnter your choice:");
		scanf("%d", &choice);
		send(s, &choice, sizeof(choice), 0);
		switch(choice)
		{
			case 1:
					printf("Enter number to be searched: ");
					scanf("%d", &key);
					send(s, &key, sizeof(key),0);
					recv(s, &pos, sizeof(pos),0);
					printf("\nThe element %d is found at position %d \n", key, pos);
					break;
			case 2:
					recv(s, buffer, sizeof(buffer),0);
					printf("\nThe array in ascending order is \n");
					for(int i=0 ; i<size ; i++)
						printf("%d ", buffer[i]);
					break;
			case 3:
					recv(s, buffer, sizeof(buffer),0);
					printf("\nThe array in descending order is \n");
					for(int i=0 ; i<size ; i++)
						printf("%d ", buffer[i]);
					break;					
			case 4:
					recv(s, odd, sizeof(odd),0);
					recv(s, &b, sizeof(b), 0);
					recv(s, even, sizeof(even), 0);
					recv(s, &a, sizeof(a), 0);
					printf("\nThe odd elements in the array are ");
					for(int i=0 ; i<b ; i++)
						printf("%d, ", odd[i]);
					printf("\nThe even elements in the array are ");
					for(int i=0 ; i<a ; i++)
						printf("%d, ", even[i]);
					break;

			case 5:	
					close(s);
					exit(0);
		
		}
	}
}
