#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define max 2048

int main()
{
	int socket1;
	struct sockaddr_in serveraddr;
	struct hostent *hostt;
	struct in_addr **address_list;
	char Sreply[max],ip[50];
	char message[max];
	int n,i=0,k=0,total_len=0;
	FILE *f,*fx;
	char hostname[50],c[100],object1[100],filename[13];
	char x;
	//File address and Check to Open
	if((f = fopen("/home/adityasingh/Downloads/fetch.txt", "r")) == NULL)
	{
		printf("File Couldn't Open !! Check File Location \n");
		exit(1);
	}
	//GETTING HOSTNAME
	fgets(c,sizeof(c),f);
	{
		printf("\nHost Name is \t");
		fputs(c,stdout);
			while(c[i] != '\n'){
				hostname[i]=c[i];
				i++;}
			hostname[i+1]='\0';
		printf("\n\n");
	}

	//Getting object from file
	while(fgets(c,sizeof(c),f) != NULL)
	{
		printf("Object from Host \t");
		fputs(c,stdout);
			i=0;
			while(c[i] != '\n'){
				object1[i]=c[i];
				i++;}
			object1[i+1]='\0';
		
	//SOCKET CREATION
	socket1=socket(AF_INET,SOCK_STREAM,0);
	if(socket1 == -1)
	{
		printf("Socket Creation Failed !!!");
		return 0;
	}
	
	//GETTING HOSTNAME
	hostt = gethostbyname(hostname);
	if(hostt == NULL)
	{
		printf("ERROR Reaching Host !!! Check the Readme file and Retry \n");
		close(socket1);
		return 0;			
	}
	
	address_list = (struct in_addr **)hostt->h_addr_list;
	for(i = 0; address_list[i] != NULL; i++) {
        //Copying the IP address
        strcpy(ip , inet_ntoa(*address_list[i]) );
    	}   
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=inet_addr(ip);
	serveraddr.sin_port=htons(80);
	
	//CHECKING FOR CONNECTION
	if(connect(socket1,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) == 0)
	{
	printf("Connected to Server \n");
	}
	
	snprintf(message, 199, "GET %s HTTP/1.1\r\n" "Host: %s\r\n" "\r\n\r\n",object1, hostname);
	

	if (send(socket1, message, strlen(message), 0) < 0)
	{
        printf("Send failed!\n");
        return 1;
    	}
    	printf("Data Sent Successful \n");
	//File 	Name and Extension
	snprintf(filename, 13, "Acn_%d_S.jpg", k);
	fx = fopen(("/home/adityasingh/Downloads/%s",filename), "ab");
	k++;
while(1)
    {
        int sizeRec = recv(socket1, Sreply , sizeof(Sreply) , 0);

        if( sizeRec == 0 ){
            printf("Recieving Over\n");
            break;
		
        }
	
       	 total_len = total_len + sizeRec;
	
        //server_reply 
       fwrite(Sreply , sizeRec , 1, fx);
	sizeRec=0;
       
    }
	
	if(total_len > 0) 
    		printf("Reply received of size %d Bytes\n",total_len);
	else
		puts("Recieving failed \n");

    	fclose(fx);
	close(socket1); //Close the Socket



	}
	fclose(f);
	
}

