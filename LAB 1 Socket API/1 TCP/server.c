#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
int main(){
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
	
		int array[10], buffer[10], choice, key, pos=-1, size, temp, odd[10] = {0}, even[10] = {0}, a =0, b = 0;	
		recv(ns, array, sizeof(array), 0);
		recv(ns, &size, sizeof(size), 0);
		int i;
		printf("\nArray received is: ");
		for(i=0 ; i<size ; i++)
			printf("%d ",array[i]);	
		
while(1)
	{	for(i=0 ; i<size ; i++)
			buffer[i]=array[i];
			buffer[i]='\0';	
		recv(ns, &choice, sizeof(choice), 0);
		switch(choice)
		{
			case 1:
					recv(ns, &key, sizeof(key), 0);					
					for(int i=0 ; i<size ; i++)
					{
						if(buffer[i]==key){
							pos=i;
							break;
						}
					}
					send(ns, &pos, sizeof(pos), 0);
					break;
			case 2:
					for(int i=0 ; i<size-1 ; i++)
					{
						for(int j=0 ; j<size-1-i ; j++)
						{
							if(buffer[j]>buffer[j+1])
							{
								temp = buffer[j];
								buffer[j] = buffer[j+1];
								buffer[j+1] = temp;
							}
						}
					}
					send(ns, buffer, sizeof(buffer), 0);
					break;
			case 3:
					for(int i=0 ; i<size-1 ; i++)
					{
						for(int j=0 ; j<size-1-i ; j++)
						{
							if(buffer[j]<buffer[j+1])
							{
								temp = buffer[j];
								buffer[j] = buffer[j+1];
								buffer[j+1] = temp;
							}
						}
					}
					send(ns, buffer, sizeof(buffer), 0);
					break;
			case 4:
					for(int i=0 ; i<size ; i++)
					{
						if(buffer[i]%2==0)
							even[a++] = buffer[i];
						else
							odd[b++] = buffer[i];					
					}
					send(ns, odd, sizeof(odd), 0);
					send(ns, &b, sizeof(b) ,0);
					send(ns, even, sizeof(even), 0);
					send(ns, &a, sizeof(a), 0);

					break;
			case 5:
					exit(0);
			
		} 
	}
}

