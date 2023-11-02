#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
void replaceAll(char *str, const char *oldWord, const char *newWord) {
    char *pos, temp[1000];
    int index = 0;
    int owlen;

    owlen = strlen(oldWord);
    while ((pos = strstr(str, oldWord)) != NULL) {
        strcpy(temp, str);
        index = pos - str;
        str[index] = '\0';
        strcat(str, newWord);
        strcat(str, temp + index + owlen);
    }
}
int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}
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
	char buff[30], filename[30]; 
        int choice;
	recb = recvfrom(s, filename, sizeof(filename), 0, (struct sockaddr*)&client, &ca);
        if (recb == -1) {
            printf("Message receiving failed");
            exit(0);
        }
        printf("\nFile name received: %s", filename);        
        FILE *file = fopen(filename, "r");
        if (file == NULL)
            strcpy(buff, "File not present!");
        else
            strcpy(buff, "File found");           
        printf("\n%s", buff);        
        sntb = sendto(s, buff, sizeof(buff), 0, (struct sockaddr*)&client, len);
        if (sntb == -1) {
            printf("\nMessage sending failed!!");
            exit(0);
        }
        if (strcmp(buff, "File not present!") == 0){
            close(s);
            exit(0);
            printf("not there");
        }
        char file_buffer[100];
        size_t bytes_read;
        printf("\nFile contents:\n");
        while ((bytes_read = fread(file_buffer, 1, sizeof(file_buffer), file)) > 0)
              fwrite(file_buffer, 1, bytes_read, stdout);
              fclose(file);
        while(1){
        	recb = recvfrom(s, &choice, sizeof(choice), 0, (struct sockaddr*)&client, &ca);
       	        printf("\n\nchoice received: %d",choice);
        	int i, n, n1, n2, j;
        	char str[50], str1[50], str2[50];
                		char Temp[1000]; 
        	switch(choice){
        		case 1:
        			recb = recvfrom(s, str, sizeof(str), 0, (struct sockaddr*)&client, &ca);
        			printf("\nSearching for %s...",str);     
        			FILE *file1 = fopen(filename, "r");
                		int count = 0;               
                		while (fgets(Temp, 512, file1) != NULL) {
                			if ((strstr(Temp, str)) != NULL)
                        			count++;
                		}
                		sntb = sendto(s, &count, sizeof(count), 0, (struct sockaddr *)&client, len);
                		fclose(file1);
                		break;
        		case 2:
        			recb = recvfrom(s, str1, sizeof(str1), 0, (struct sockaddr *)&client, &ca);
        			recb = recvfrom(s, str2, sizeof(str2), 0, (struct sockaddr *)&client, &ca);
                		printf("\nReplacing %s with %s..\n", str1, str2);
                		FILE *file2 = fopen(filename, "r");
                		FILE *filetemp = fopen("replace.tmp", "w");
                		while ((fgets(Temp, 1000, file2)) != NULL) {
                                        replaceAll(Temp, str1, str2);
                                        fputs(Temp, filetemp);
                                }
				strcpy(buff, "Replace finished");
                		sntb = sendto(s, buff, sizeof(buff), 0, (struct sockaddr *)&client, len);
                		fclose(file2); fclose(filetemp);
                		remove(filename);
                		rename("replace.tmp", filename);
                		break;
        		case 3:
        			printf("\nOrdering file...\n");
        			char lines[100][1000];
                                char *sorted_lines[100];
                                int num_lines = 0;
                                FILE *file3 = fopen(filename, "r");
                                while (fgets(lines[num_lines], 1000, file3)) {
                                    sorted_lines[num_lines] = lines[num_lines];
                                    num_lines++;
                                }
                                fclose(file3);
        			qsort(sorted_lines, num_lines, sizeof(char *), compare_strings);
        			filetemp = fopen("temp.tmp", "w");
        			for (int i = 0; i < num_lines; i++)
            			    fputs(sorted_lines[i], filetemp);
        			strcpy(buff, "Ordering done!");
                		sntb = sendto(s, buff, sizeof(buff), 0, (struct sockaddr *)&client, len);
                		fclose(filetemp);
                		remove(filename);
                		rename("temp.tmp", filename);
                		break;
        		case 4:
        			close(s);
        			exit(0);
        	}
        }
}
