
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


char alphabet_string[28] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '};


// Error function used for reporting issues
void error(const char *msg) {
  perror(msg);
  exit(1);
} 

// Set up the address struct for the server socket
void setupAddressStruct(struct sockaddr_in* address, 
                        int portNumber){
  // Clear out the address struct
  memset((char*) address, '\0', sizeof(*address)); 

  // The address should be network capable
  address->sin_family = AF_INET;
  // Store the port number
  address->sin_port = htons(portNumber);
  // Allow a client at any address to connect to this server
  address->sin_addr.s_addr = INADDR_ANY;
}

int main(int argc, char *argv[]){
	char * ciphertext = NULL;
	int int_msg_char = 0;
	int int_key_char = 0;
	int int_cipher_char = 0;
	int childStatus = 0;
	char * msg = NULL;
	char * key_string = NULL;
	char charValue[1];
	
	
  int connectionSocket, charsRead, Read_all, message_length, key_length, actual_pid;
  charsRead = 0;
  key_length = -1;
  char buffer[140000];
  char buffer1[70000];
  char buffer2[70000];
  char * length = NULL;
  struct sockaddr_in serverAddress, clientAddress;
  socklen_t sizeOfClientInfo = sizeof(clientAddress);
	for(int i = 0; i < 130000; i++){
		buffer[i] = 'z';
		
	}
  // Check usage & args
  if (argc < 2) { 
    fprintf(stderr,"USAGE: %s port\n", argv[0]); 
    exit(1);
  } 
  
  // Create the socket that will listen for connections
  int listenSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (listenSocket < 0) {
    error("ERROR opening socket");
  }

  // Set up the address struct for the server socket
  setupAddressStruct(&serverAddress, atoi(argv[1]));

  // Associate the socket to the port
  if (bind(listenSocket, 
          (struct sockaddr *)&serverAddress, 
          sizeof(serverAddress)) < 0){
    error("ERROR on binding");
  }

  // Start listening for connetions. Allow up to 5 connections to queue up
  listen(listenSocket, 5); 
  
  // Accept a connection, blocking if one is not available until one connects
  while(1){
	  
    // Accept the connection request which creates a connection socket
    connectionSocket = accept(listenSocket, 
                (struct sockaddr *)&clientAddress, 
                &sizeOfClientInfo); 
    if (connectionSocket < 0){
      error("ERROR on accept");
    }
	else{
		
		   pid_t spawnPid = fork();
		
	  switch(spawnPid){
		case -1:
		  perror("fork()\n");
		  exit(1);
		  break;
		case 0:
				message_length = 0;
				key_length = 0;
				Read_all = 0;
				
					 printf("SERVER: Connected to client running at host %d port %d\n", 
									  ntohs(clientAddress.sin_addr.s_addr),
									  ntohs(clientAddress.sin_port));

				// Read the client's message from the socket
	/***************************************************************		
	Receive the message in the first transmission and respond with sucess 
	***************************************************************/		
				Read_all = 0;
				//printf("what is the buffer initially %s", buffer);
				
				 while(1){

				charsRead = recv(connectionSocket, buffer, 139999, 0);  /*<______RECEIVING____!!!!!!!!!!_*/
			 	if(buffer[charsRead-1] == '%'){
				/* for(int i = 0; i < charsRead; i++){
					if(buffer[i] == '%'){
						printf("what is i %d:", i);
					Read_all = 1;
					break;
				} */
				break;
				}
				/* if(Read_all == 1){
					break;
				} */
				}  

				char * payloadptr = &buffer;
				int msg_length = 0;
				int key_length = 0;
				for(int i = 0; i < charsRead; i++){
					if(buffer[i] == '\n'){
					msg_length++;
					break; 
					
					}
					else{
						msg_length++;
					}
				}
				key_length = charsRead - msg_length - 1;
				
				
				printf("How long is the message: %d", msg_length);
				printf("How long is the message: %d", key_length);

				
				printf("what is read_all %d", Read_all);  
				
				
		/* 
				
				ciphertext = malloc((message_length + 1) * sizeof(char));

				
				 ciphertext[0] = '@';
				 for(int i = 1; i < message_length+1; i++){

				 int int_msg_char, int_key_char, int_cipher_char;
				 int_msg_char = 0;
				 int_key_char = 0;
				 int_cipher_char= 0;
				
				 
				if(buffer[i] == ' '){
					int_msg_char = 26;
				}
				else{
					int_msg_char = (int)buffer[i] - 65;
					
					
				}
				if(buffer2[i] == ' '){
					int_key_char = 26;
					
				} 
				else{
				 int_key_char = (int)buffer2[i] -65;

					
				}
			//	printf("msg char is: %d", int_msg_char);
			//	printf("key char is %d", int_key_char);
				int_cipher_char = int_msg_char + int_key_char;
				if(int_cipher_char > 26){
					int_cipher_char -= 27;
					
				} 
				if(int_cipher_char == 26){
				ciphertext[i] = (char)(32);
				}
				else{
				ciphertext[i] = (char)(int_cipher_char+65);
				}
				} 
				 */
				
				
				
				
				
				
						
				
				close(connectionSocket); 
				
			  return 0;
				

		default:
			 
		actual_pid = waitpid(spawnPid, &childStatus, WNOHANG);

		
		
			break; 
					}
			
		}
	
	}


			  close(listenSocket); 
		return 0;
}
