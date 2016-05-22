# Snp_project on FTP Server
# Pre-Requisites
1. FileZilla client.
2. Ubuntu or any other unix based OS.

# Details:
1. ReadDir.c: This was made to learn fetching file names of particular type of files in this case (.txt).
2. ServerInc.c: This was made to learn how to connect a self made server to a self made client and transferring files among them.
3. Server1.c: This was made to connect our server to a global client like filezilla or telnet.
4. server2.c: This was made to debug commands like PWD, TYPE and QUIT, sent by the client (here FileZilla) to the server.
5. Server3.c: In this debugging was done for the commands like PORT and LIST sent by the client (here FileZilla) to the server.
6. Server4.c: In this storing a file on the server using STOR command was implemented.
7. Server5.c: In this retrieving a file from the server using RETR command was implemented.
8. ServerFinal.c: This is the final server in which entering 1 will connect to FileZilla and 2 connects to telnet.

# Commands for running:
1. Download ServerFinal.c.
2. Change ip address inside the program and type there ip of your machine.
3. Change current working directory to the directory where ServerFinal.c is saved.
4. Type "gcc -o server ServerFinal.c" in current working directory.
5. Type "./server port_number" (port_Numner can be any number but try to use ports that are not private like 10000-50000).
6. Now enter 1 for FileZilla and 2 for Telnet. Anything else will give error and program will terminate.
7. If 1:
   1. Go to FileZilla and type ip of your machine, use any username and password and type port number taken as input in ./server.
   2. FileZilla will be connected to the server and list of files present in current working directory will be displayed in the remote directory column.  
   3. Now close the server by using ^C or simply closing the terminal. Wait for sometime so that server can unbind the connection.
   4. After about 20-25 seconds again run the server with the same port number used earlier and drag a file from local to remote in FileZilla without changing any detail and it will be saved on server and vice versa for downloading a file from the server.
   5. You can check downloaded file in respective folder.
   6. Close terminal and FileZilla.
   
8. If 2:
   1. Open another terminal and type "telnet ip port" (ip is ipv4 of your machine and port is any port except private).
   2. Type any command that you want to run on terminal.
   3. Output of the command typed will be displayed on client terminal. If there is an error in running, error is also displayed at the server.
   4. Close both terminals.
