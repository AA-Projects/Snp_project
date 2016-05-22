#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<dirent.h>
int hu=0;
char temp_buffer[10000];
int main(int argc, char *argv[]){
	struct sockaddr_in localaddr,remoteaddr,remoteaddr_act,local_act;
	unsigned char act_port[2];
	long int act_ip[4], port_dec;
	char ip_decimal[40];int s,ns,nsx;
	int s_data_act;
	char send_buffer[10000],receive_buffer[10000];
	char fileName[10000];
	int n,bytes,addrlen,addrlenx;
	s = socket(PF_INET, SOCK_STREAM, 0);
	if (s <0){
		printf("socket failed\n");
		fflush(stdout);
	}
	localaddr.sin_family = AF_INET;
	localaddr.sin_port = htons(atoi(argv[1]));
	localaddr.sin_addr.s_addr = inet_addr("10.0.2.15");
	if (bind(s,(struct sockaddr *)(&localaddr),sizeof(localaddr)) != 0){
		printf("Bind failed!\n");
		fflush(stdout);
		exit(0);
	}
	listen(s,100);
	while (1){
		addrlen = sizeof(remoteaddr);
		ns = accept(s,(struct sockaddr *)(&remoteaddr),&addrlen);
		if (ns <0 )
			break;
		sprintf(send_buffer,"\n220 Welcome to AA's FTP server\r\n\n");
		fflush(stdout);bytes = send(ns, send_buffer, strlen(send_buffer), 0);
		while (1){
			n = 0;
			while (1){
				bytes = recv(ns, &receive_buffer[n], 1, 0);
				if ( bytes <= 0 )
					break;
				if (receive_buffer[n] == '\n'){ 
					receive_buffer[n] = '\0';
					printf("\n");
					fflush(stdout);
					break;
				}
				if (receive_buffer[n] != '\r') n++;
			}
			if ( bytes <= 0 )
				break;
			printf("\n");
			fflush(stdout);
			printf("\n-->DEBUG: the message from client reads: '%s' \r\n", receive_buffer);
			fflush(stdout);
			if(strncmp(receive_buffer,"USER",4)  && strncmp(receive_buffer,"PASS",4)&&  strncmp(receive_buffer,"QUIT",4)&&  strncmp(receive_buffer,"PWD",3)&&  strncmp(receive_buffer,"TYPE",4)){
				sprintf(send_buffer,"\n202 Command not implemented, superfluous at this site. \r\n");
				fflush(stdout);
				bytes = send(ns, send_buffer, strlen(send_buffer), 0);
			}
			if (strncmp(receive_buffer,"USER",4)==0){
				printf("\nLogging in \n");
				fflush(stdout);
				sprintf(send_buffer,"\n331 Password required \r\n");
				fflush(stdout);
				bytes = send(ns, send_buffer, strlen(send_buffer), 0);
				if (bytes < 0)
					break;
			}

			if (strncmp(receive_buffer,"PASS",4)==0){
				printf("\nTyping password (anything will do... \n");
				fflush(stdout);
				sprintf(send_buffer,"\n230 Public login sucessful \r\n");
				fflush(stdout);
				bytes = send(ns, send_buffer, strlen(send_buffer), 0);
				if (bytes < 0)
					break;
			}
			if(strncmp(receive_buffer,"PWD",3)==0){
				system("pwd");
				sprintf(send_buffer,"\n257 Current working directory is '/home/akash/Downloads/SNP' \r\n");
				fflush(stdout);
				bytes = send(ns, send_buffer, strlen(send_buffer), 0);		
			}
			if(strncmp(receive_buffer,"TYPE",4)==0){
				sprintf(send_buffer,"\n200 Type is now 8- bit binary\r\n");
				bytes = send(ns, send_buffer, strlen(send_buffer), 0);
			}
			if (strncmp(receive_buffer,"QUIT",4)==0){
				printf("Quit \n");
				fflush(stdout);
				sprintf(send_buffer,"\n221 Connection closed by the FTP client\r\n");
				fflush(stdout);
				bytes = send(ns, send_buffer, strlen(send_buffer), 0);
				if (bytes < 0)
					break;
				close(ns);
			}
		}
		close(ns);
		printf("disconnected from %s\n",inet_ntoa(remoteaddr.sin_addr));
		fflush(stdout);
	}
	close(s);
}
