#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
        FILE *fptr;
	fptr=fopen("text.txt","a");
	fputs("Manipal",fptr);
	fclose(fptr);
        FILE *fp;
	char temp[30];
	fp = fopen("text.txt", "r");
	char str[30];
      	while(fgets(temp, 30, fp) != NULL)
      	        strcat(str, temp);
      	fclose(fp);
      	printf("\nFile contents: %s", str);
}
