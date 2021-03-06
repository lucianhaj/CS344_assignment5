
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
  key_length = -1;
  char buffer[65000];
  char buffer2[65000];
  char * length = NULL;
  struct sockaddr_in serverAddress, clientAddress;
  socklen_t sizeOfClientInfo = sizeof(clientAddress);

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
				
				memset(buffer, '\0', 65000);
				charsRead = recv(connectionSocket, buffer, 129999, 0);  /*<______RECEIVING____!!!!!!!!!!_*/
				
				
				
				
				
				
				
				 //Check that we received all the data
				
				 
				if (charsRead < 0){
				  error("ERROR reading from socket");
				}
				message_length = strlen(buffer)-1;
				
				
				printf("SERVER: The PLAINTEXT from client \"%s\"\n", buffer);

				//Send a success message back to the client
			/* 	charsRead = send(connectionSocket, 
								"I am the server, and I got your message", 39, 0); 
				if (charsRead < 0){
				  error("ERROR writing to socket");
				} 
				
				Read_all = 0; */
	/*************************************************************		
	Receive the key in the second transmisson and respond with success
	*************************************************************/
				memset(buffer2, '\0', 65000);
				charsRead = recv(connectionSocket, buffer2, 64999, 0);  /*<______RECEIVING__________!!!!!!!!!!_*/
				key_length = strlen(buffer2) - 1;
				
				
				
					 for(int i = 0; i < strlen(buffer)+1; i++){
						 if(buffer[i] == '@'){
						 Read_all = 1;
						 break;
						 }
				 }
						 
	

				printf("%d", Read_all);
				 while(Read_all == 0){
					 
				memset(buffer, '\0', 65000);
				charsRead = recv(connectionSocket, buffer, 64999, 0); 
				
				for(int i = 0; i < strlen(buffer)+1; i++){
						 if(buffer[i] == '@'){
						 Read_all = 1;
						 break;
						 }
				 }
				} 
			/* 	
				memset(buffer2, '\0', 65000);
				charsRead = recv(connectionSocket, buffer2, 64999, 0);
				key_length = strlen(buffer2) - 1; */
				
				/* if(key_length == -1){
				memset(buffer2, '\0', 65000);
				charsRead = recv(connectionSocket, buffer2, 64999, 0);
				key_length = strlen(buffer2) - 1;
					
				} */

			/* 	 while(key_length < strlen(buffer)){
				memset(buffer2, '\0', 65000);
				charsRead = recv(connectionSocket, buffer2, 64999, 0);  
				key_length = strlen(buffer2) - 1;
				} 

				 */
				//while(charsRead < message_length
				//Check that we received all the data
				
			/* 	printf("what is the key %s", buffer2);
				 for(int i = 0; i < strlen(buffer2); i++){
						 if(buffer2[i] == '@'){
						 Read_all = 1;
						 break;
						 }
				}
				printf("what was read_all %d *****************\n", Read_all);
				while(Read_all == 0){
					 
				memset(buffer2, '\0', 65000);
				charsRead = recv(connectionSocket, buffer2, 64999, 0);

				 for(int i = 0; i < strlen(buffer2); i++){
						 if(buffer2[i] == '@'){
						 Read_all = 1;
						 break;
						 }
				}				
				}
				printf("what was read_all %d *****************\n", Read_all);

				key_length = strlen(buffer2) - 1;
				if(key_length < message_length){
				error("Your message is longer than your key!");
				exit(1);	
					
				} */
				
				
				/********************************************
				Encrypt the input plaintext using the key 
				********************************************/
				
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
				
				
				 
				if (charsRead < 0){
				  error("ERROR reading from socket");
				}
				printf("key_length %d \n", key_length);
				printf("message_length %d \n", message_length); 

			
			
				
				charsRead = send(connectionSocket, ciphertext, strlen(ciphertext)+1, 0);/*<______SENDING___________!!!!!!!!!!_*/
			
				if (charsRead < 0){
				  error("ERROR writing to socket");
				}
				/* while(charsRead < message_length){
					
				charsRead = send(connectionSocket, ciphertext, strlen(ciphertext)+1, 0);
	
					
				} */
			
			
		 
				//printf("SERVER: The KEY from client:       \"%s\"\n", buffer2);
				
			
				// Send a success message back to the client
				charsRead = send(connectionSocket, /*<______SENDING___________!!!!!!!!!!_*/
								"I am the server, and I got your message", 39, 0); 
				if (charsRead < 0){
				  error("ERROR writing to socket");
				}
				
				
				
				
				
				
				
				
						
				
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
