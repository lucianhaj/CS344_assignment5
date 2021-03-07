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
  char buffer[70000];
  char buffer2[70000];
  char buffer3[140000];
  num = 0;
  charsRead = 0;

	// code to parse input
  size_t size = 1000;
  char * key_string = malloc(70000* sizeof(char));
  char * message = malloc(70000* sizeof(char));
  char * data = malloc(140000 * sizeof(char));
  int x = 0;
  
  //message[0] = '@';
 
   FILE * plain = fopen(argv[1],  "r");
   FILE * key = fopen(argv[2],  "r"); 
 
 
 
 char ackowledgemnt;
 
	//dup2(plain, 0);
  
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
	fgets(buffer, sizeof(buffer)-1, plain);
	fgets(buffer2, sizeof(buffer2)-1, key);
		buffer2[strlen(buffer2)] = '%';


	strcat(data, buffer);
	strcat(data, buffer2);
	fclose(plain);
	fclose(key);
	//data = strcat(message, key);
	
	 /********************************
		Send message
 ********************************/
 
 
 
	// printf("what is the data %s\n", data);
	printf("what is the length of message %d:\n", strlen(buffer)); 


	 do{
	charsWritten = send(socketFD, data, strlen(data), 0);
	//printf("how many characters written: %d", charsWritten);
	
	
	}while(charsWritten < strlen(data)); 
 
 int message_length, key_length;
			
			
			
			
			//while(1){

				charsRead = recv(socketFD, buffer3, strlen(buffer), 0);  /*<______RECEIVING____!!!!!!!!!!_*/
				/*  if(buffer3[charsRead-1] == '%'){
				
				 break;
				}  */
				/* if(Read_all == 1){
					break;
				} */
				//}
				 /* for(int i = 0; i < charsRead+1; i++){
					if(buffer3[i] == '0'){
					buffer3[i] = '\n';
					break;
					} */
				//} 				
				//printf("what is buffer3 %c", buffer3[charsRead-1]);
			buffer3[charsRead-1] = '\n';
			//buffer3[charsRead-1] = '\n';
			printf("%s", buffer3);
 
 
 
 
 
 
 
 



  // Close the socket
  close(socketFD); 
  return 0;
}
