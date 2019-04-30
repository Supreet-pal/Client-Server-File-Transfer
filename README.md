![Image](Images/Image1.jpg)

# Rapid Transfer 
Rapid transfer is an application that allows quick transfer of all types of files including media, binary, text fiels and others. It is a client-server application where client can upload or download the files from the server.

### Technical Specifications
- It is build in `C` programming language using `UNIX` utilities. 
-  It makes use of `socket programming` to communicate with other systems.
- The `IP address` with `port number` is utilized for connection establishment.

### How it works
- The server-side program listens for the client requests.
- The client-side program hets the IP address + port number of the server from the command line argument.
- Then client-side sends the connection request to the server.
- Server accepts the request and the connection is established.
- Client uploads or downloades the files from thes server to its system.
- Client can (re)name the files before downloading.

### Configuring the application
- Download the project files. 
- The client program should reside on the client system and the server program should be on the server-side system.
- Run the server program using 
> chmod +x server.c
gcc -o server server.c
./server <port number>

- Now run the client side using
> chmod +x client.c
gcc -o client client.c
./client <IP address> <port number>

- Now follow the instructions to upload or download the files from the server.