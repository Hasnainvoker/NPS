#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>
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
	recv(ns, buff, sizeof(buff), 0);
	printf("\nString Recieved: ");
    	printf("%s\n", buff);
    	char num[50] = {0}, alpha[50] = {0};
       int i=0, j=0, k=0;
       int n = strlen(buff);
       for (i = 0; i < n; i++) {
           	if ((buff[i] >= 65 && buff[i] <= 91) || (buff[i] >= 97 && buff[i] <= 123)) {
                	alpha[j] = buff[i];
                	j++;
            	} 
            	else {
                	num[k] = buff[i];
                	k++;
            	}		
        }
        alpha[j] = '\0';
        num[k] = '\0';
    	int pid = fork();
    	int pidchild, pidparent;
    	if (pid==0){
    	        close(s);
    		for (i = 0; i < k - 1; i++) {
            		for (int x = 0; x < k - i - 1; x++) {
                		if (num[x] > num[x + 1]) {
                    			char temp = num[x];
                    			num[x] = num[x + 1];
                    			num[x + 1] = temp;
                		}
            		}
        	}
                pidchild=getpid();
       	        printf("\nPID: %d (Child process)\nSorted numerical string is: ", pidchild);
        	printf("%s\n", num);
        	send(ns, &pidchild, sizeof(pidchild), 0); 
        	send(ns, num, sizeof(num), 0); 
        	close(ns);
    	} 
    	else if(pid>0){
    		wait(NULL);
 		for (i = 0; i < j - 1; i++) {
           		for (int x = 0; x < j - i - 1; x++) {
                		if (alpha[x] < alpha[x + 1]) {
                    			char temp = alpha[x];
                    			alpha[x] = alpha[x + 1];
                    			alpha[x + 1] = temp;
                		}	
            		}
        	}
        	pidparent=getpid();
        	printf("\nPID: %d (Parent process)\nSorted alphabetical string is: ", pidparent);
        	printf("%s\n", alpha);
        	send(ns, &pidparent, sizeof(pidparent), 0);
        	send(ns, alpha, sizeof(alpha), 0);  
    	        close(ns);
    	        close(s);             
    	}
}

