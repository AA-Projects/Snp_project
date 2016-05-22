#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
int main(){
	FILE *fp;
	int sd,newsd,ser,n,a,cli,pid,bd,port,clilen;
	char ip[100],name[100],fileread[100],fname[100],ch,file[100],rcv[100],send_buffer[200];
	struct sockaddr_in servaddr,cliaddr;
	printf("Enter the ip address: ");
	scanf("%s",ip);
	printf("Enter the port address: ");
	scanf("%d",&port);
	sd=socket(AF_INET,SOCK_STREAM,0);
	if(sd<0)
		printf("Can't create\n");
	else{
		printf("Socket is created\n");
		servaddr.sin_family=AF_INET;
		servaddr.sin_addr.s_addr=inet_addr(ip);
		servaddr.sin_port=htons(port);
		a=sizeof(servaddr);
		bd=bind(sd,(struct sockaddr *)&servaddr,a);
		if(bd<0)
			printf("Cant bind\n");
		else{
			printf("Binded\n");
			listen(sd,5);
			clilen=sizeof(cliaddr);
			newsd=accept(sd,(struct sockaddr *)&cliaddr,&clilen);
			if(newsd<0){
				printf("Cant accept\n");
			}
			else{
				strcpy(send_buffer,"==220 Welcome to Alan's FTP site==");			
				send(newsd,send_buffer,100,0);
				n=recv(newsd,rcv,100,0);
						printf("Accepted\n");
						n=recv(newsd,rcv,100,0);
						rcv[n]='\0';
						fp=fopen(rcv,"r+");
						while(fp==NULL){
							send(newsd,"error",5,0);
							n=recv(newsd,rcv,100,0);
							rcv[n]='\0';
							fp=fopen(rcv,"r+");				
						}
						while(fgets(fileread,sizeof(fileread),fp)){
							if(send(newsd,fileread,sizeof(fileread),0)<0){
								printf("Cant send\n");
							}
						}
						if(!fgets(fileread,sizeof(fileread),fp)){
							send(newsd,"completed",20,0);
						}					
				return(0);
			}
		}
	}
}
