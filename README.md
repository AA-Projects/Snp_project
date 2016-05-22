# Snp_project on FTP Server
Details:
1. ReadDir.c: This was made to learn fetching file names of particular type of files in this case (.txt).
2. ServerInc.c: This was made to learn how to connect a self made server to a self made client and transferring files among them.
3. Server1.c: This was made to connect our server to a global client like filezilla or telnet.
4. server2.c: This was made to debug commands like PWD, TYPE and QUIT, sent by the client (here FileZilla) to the server.
5. Server3.c: In this debugging was done for the commands like SYST, PORT and LIST sent by the client to the server.
6. Server4.c: In this storing a file on the server using STOR command was implemented.
7. Server5.c: In this retrieving a file from the server using RETR command was implemented.
8. ServerFinal.c: This is the final server which can connect and transfer files from/to FileZilla and any other self made client giving desired reply to the server easily.


# Commands for running:
1. Download ServerFinal.c.
2. Change ip address inside the program and type there ip of your machine.
3. Change current working directory to the directory where ServerFinal.c is saved.
4. Type gcc -o server ServerFinal.c in current working directory.
5. Type ./server port_number (port_Numner can be any number but try to use ports that are not private like 10000-50000).
6. Now go to FileZilla and type ip of your machine, use any username and password and type port number taken as input in ./server.
7. FileZilla will be connected to the server and list of files preent in current working directory will be displayed in the remote directory column.
8. Now simply close the server by using ^C or simply closing the terminal. Wait afor sometime so that server can unbing the connection.
9. After about 20-25 seconds again run the server with the same port number used earlier and drag a file from local to remote and it will be saved on server and vice versa for downloading a file from the server.
