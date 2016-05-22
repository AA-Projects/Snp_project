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
			if(strncmp(receive_buffer,"USER",4)  && strncmp(receive_buffer,"PASS",4)&&  strncmp(receive_buffer,"QUIT",4)&&  strncmp(receive_buffer,"PWD",3)&&  strncmp(receive_buffer,"TYPE",4)&&  strncmp(receive_buffer,"SYST",4) &&strncmp(receive_buffer,"PORT",4)&&strncmp(receive_buffer,"LIST",4)  &&  strncmp(receive_buffer,"NLST",4)&& strncmp(receive_buffer,"STOR",4)){
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
			if (strncmp(receive_buffer,"SYST",4)==0){
				system("lsb_release -d > tmp.txt");
				FILE *fin=fopen("tmp.txt","r");
				sprintf(send_buffer,"\n150 Transfering... \r\n");
				fflush(stdout);                
				bytes = send(ns, send_buffer, strlen(send_buffer), 0);
				char temp_buffer[80];
				while (!feof(fin)){
					fgets(temp_buffer,78,fin);
					sprintf(send_buffer,"%s",temp_buffer);
					fflush(stdout);                    
					send(s_data_act, send_buffer, strlen(send_buffer), 0);
				}
				fclose(fin);
				sprintf(send_buffer,"\n226 File transfer completed... \r\n");
				fflush(stdout);
				bytes = send(ns, send_buffer, strlen(send_buffer), 0);
				if (bytes < 0)
					break;
			}
			if(strncmp(receive_buffer,"PORT",4)==0){
				sscanf(receive_buffer, "PORT %d,%d,%d,%d,%d,%d",&act_ip[0],&act_ip[1],&act_ip[2],&act_ip[3],(int*)&act_port[0],(int*)&act_port[1]);
				sprintf(ip_decimal, "\n%d.%d.%d.%d\n", act_ip[0], act_ip[1], act_ip[2],act_ip[3]);
				fflush(stdout);
				printf("\nIP is %s\n",ip_decimal);
				fflush(stdout);                
				port_dec=act_port[0]*256+act_port[1];
				printf("\nport %d\n",port_dec);
				fflush(stdout);                
				printf("\n");
				fflush(stdout);                
				sprintf(send_buffer, "\n200 Ok\r\n");	
				fflush(stdout);                    
				bytes = send(ns, send_buffer, strlen(send_buffer), 0);
			}
			if ( (strncmp(receive_buffer,"LIST",4)==0) || (strncmp(receive_buffer,"NLST",4)==0)){
				s_data_act = socket(AF_INET, SOCK_STREAM, 0);
				local_act.sin_family=AF_INET;
				local_act.sin_addr.s_addr=inet_addr("10.0.2.15");
				local_act.sin_port=htons(port_dec);
				sprintf(send_buffer,"\n150 Transfering... \r\n");
				bytes = send(ns, send_buffer, strlen(send_buffer), 0);
				system("dir -1 > tmp.txt");
				FILE *fin=fopen("tmp.txt","r");
				nsx = connect(s_data_act,(struct sockaddr *)(&local_act),sizeof(local_act));
				fflush(stdout);
				while (!feof(fin)){
					fgets(temp_buffer,78,fin);
					sprintf(send_buffer,"%s",temp_buffer);
					fflush(stdout);                    
					bytes=send(s_data_act, send_buffer, strlen(send_buffer), 0);
				}
				fclose(fin);
				close(s_data_act);
				sprintf(send_buffer,"\n226 File transfer completed... \r\n");
				fflush(stdout);
				bytes = send(ns, send_buffer, strlen(send_buffer), 0);
				close(s);
			}
			if((strncmp(receive_buffer,"STOR",4)==0)){
				s_data_act = socket(AF_INET, SOCK_STREAM, 0);
				local_act.sin_family=AF_INET;
				local_act.sin_addr.s_addr=inet_addr("10.0.2.15");
				local_act.sin_port=htons(port_dec);memset(&fileName, 0, strlen(fileName));
				nsx = connect(s_data_act,(struct sockaddr *)(&local_act),sizeof(local_act));memset(&fileName, 0, strlen(fileName));
				wy_fileName_collector(receive_buffer,   fileName);
				if(fopen(fileName,"w")  ==  NULL){
					sprintf(send_buffer,"\n450 Requested file action not taken. \r\n");
					fflush(stdout);                    
					bytes = send(ns, send_buffer, strlen(send_buffer), 0);
				}
				else{
					FILE *fout=fopen(fileName,"w");
					sprintf(send_buffer,"\n150 File status okay; about to open data connection. \r\n");
					fflush(stdout);
					bytes = send(ns, send_buffer, strlen(send_buffer), 0);
					while(1){
						n = 0;
						while(1){
							bytes = recv(s_data_act, &receive_buffer[n], 1, 0);
							if ( bytes <= 0 )
								break;
							if (receive_buffer[n] == '\n'){
								receive_buffer[n] = '\0';
								break;
							}
							if (receive_buffer[n] != '\r')
								n++;
						}
						if ( bytes <= 0 )
							break;
						fprintf(fout,"%s\n",receive_buffer);
					}
					sprintf(send_buffer,"\n226 File transfer completed... \r\n");
					fflush(stdout);
					bytes = send(ns, send_buffer, strlen(send_buffer), 0);
					fclose(fout);
				}
				close(s_data_act);
			}
		}
		close(ns);
		printf("disconnected from %s\n",inet_ntoa(remoteaddr.sin_addr));
		fflush(stdout);
	}
	close(s);
}
