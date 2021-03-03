#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <fcntl.h>

#include <string.h>
#include <sys/types.h>  // ssize_t
#include <sys/socket.h> // send(),recv()
#include <netdb.h>      // gethostbyname()

/**
* Client code
* 1. Create a socket and connect to the server specified in the command arugments.
* 2. Prompt the user for input and send that input as a message to the server.
* 3. Print the message received from the server and exit the program.
*/

// Error function used for reporting issues
void error(const char *msg) { 
  perror(msg); 
  exit(0); 
} 



// Set up the address struct
void setupAddressStruct(struct sockaddr_in* address, 
                        int portNumber, 
                        char* hostname){
 
  // Clear out the address struct
  memset((char*) address, '\0', sizeof(*address)); 

  // The address should be network capable
  address->sin_family = AF_INET;
  // Store the port number
  address->sin_port = htons(portNumber);

  // Get the DNS entry for this host name
  struct hostent* hostInfo = gethostbyname(hostname); 
  if (hostInfo == NULL) { 
    fprintf(stderr, "CLIENT: ERROR, no such host\n"); 
    exit(0); 
  }
  // Copy the first IP address from the DNS entry to sin_addr.s_addr
  memcpy((char*) &address->sin_addr.s_addr, 
        hostInfo->h_addr_list[0],
        hostInfo->h_length);
}

int main(int argc, char *argv[]) {
	
  int socketFD, portNumber, charsWritten, charsRead, num, Received_all;
  struct sockaddr_in serverAddress;
  char buffer[1000];
  char buffer2[1000];
  num = 0;

	// code to parse input
  size_t size = 1000;
  char * key_string = malloc(1000* sizeof(char));
  char * message = malloc(1000* sizeof(char));
  int x = 0;
  
  message[0] = '@';
 
   int plain = open(argv[1],  O_RDONLY);
   int key = open(argv[2],  O_RDONLY); 
 
 
 
 char buff[2000];
 
	dup2(plain, 0);
  
  // Check usage & args
  if (argc < 3) { 
    fprintf(stderr,"USAGE: %s hostname port\n", argv[0]); 
    exit(0); 
  } 

  // Create a socket
  socketFD = socket(AF_INET, SOCK_STREAM, 0); 
  if (socketFD < 0){
    error("CLIENT: ERROR opening socket");
  }

   // Set up the server address struct
  setupAddressStruct(&serverAddress, atoi(argv[3]), "localhost");

  // Connect to server
  if (connect(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
    error("CLIENT: ERROR connecting");
  }
  // Get input message from user
  //printf("CLIENT: Enter text to send to the server, and then hit enter: ");
  // Clear out the buffer array
	memset(buffer, '\0', sizeof(buffer));
  // Get input from the user, trunc to buffer - 1 chars, leaving \0
	//printf("what is the sizeof the buffer %d", strlen(buffer));
	fgets(buffer, sizeof(buffer)-1, stdin);
	strcat(message, buffer);
	message[strlen(message)-1] = 0;
 
 
 
 
 
 /********************************
		Send message
 ********************************/
  charsWritten = send(socketFD, message, strlen(message), 0); 
  if (charsWritten < 0){
    error("CLIENT: ERROR writing to socket");
  }
  if(charsWritten < strlen(buffer)){
    printf("CLIENT: WARNING: Not all data written to socket!\n");
  }
  while(charsWritten < strlen(message)){
	  
  charsWritten = send(socketFD, message, strlen(message), 0); 
  
	  
  }
	
	
	close(plain);
	
	
	
	
	
	
	
	
	

  // Get return message from server
  // Clear out the buffer again for reuse
  memset(buffer, '\0', sizeof(buffer));
  // Read data from the socket, leaving \0 at end
  charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0); 
  if (charsRead < 0){
    error("CLIENT: ERROR reading from socket");
  }
  //printf("CLIENT: I received this from the server: \"%s\"\n", buffer);




 


  /*****************************************************************
	Send key
   ****************************************************************/



	dup2(key, 0);

	
  memset(buffer2, '\0', sizeof(buffer2));
  // Get input from the user, trunc to buffer - 1 chars, leaving \0
	//printf("what is the sizeof the buffer %d", strlen(buffer2));

	fgets(buffer2, sizeof(buffer2)-1, stdin);


  // Send message to server
  // Write to the server
  charsWritten = send(socketFD, buffer2, strlen(buffer2)-2, 0); 
  if (charsWritten < 0){
    error("CLIENT: ERROR writing to socket");
  }
  if(charsWritten < strlen(buffer2)-2){
    printf("CLIENT: WARNING: Not all data written to socket!\n");
  }
	
	
	
	
	
	
	
	
	
	
	close(key);
	
	
	/*************************
	Receive the ciphertext 
	
	*************************/
	Received_all = 0;
	memset(buffer, '\0', sizeof(buffer));
  // Read data from the socket, leaving \0 at end
  charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0); 
  
   for(int i = 0; i < strlen(buffer); i++){
						 if(buffer[i] == '@'){
						 Received_all = 1;
						 }
				}
				 while(Received_all == 0){
					 
				memset(buffer, '\0', 1000);
				charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0); 

				 for(int i = 0; i < strlen(buffer); i++){
						 if(buffer[i] == '@'){
						 Received_all = 1;
						 }
				}				
				}
				
 
  
  
  
 // buffer[strlen(buffer)] = '\n';
  
  
  if (charsRead < 0){
    error("CLIENT: ERROR reading from socket");
  }
 // printf("CLIENT: The CIPHERTEXT from server:\"%s\"", buffer);
	printf("%s\n", buffer);
	
	
	
	
	

  // Get return message from server
  // Clear out the buffer again for reuse
  memset(buffer2, '\0', sizeof(buffer2));
  // Read data from the socket, leaving \0 at end
  charsRead = recv(socketFD, buffer2, sizeof(buffer2) - 1, 0); 
  if (charsRead < 0){
    error("CLIENT: ERROR reading from socket");
  }
 // printf("CLIENT: I received this from the server: \"%s\"\n", buffer2);









  // Close the socket
  close(socketFD); 
  return 0;
}
