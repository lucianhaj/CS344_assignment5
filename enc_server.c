

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
	
	
  int connectionSocket, charsRead, charsRead1, charsWritten, charsWritten1, Read_all, message_length, key_length, actual_pid;
  charsRead = 0;
  charsRead1 = -1;
  charsWritten = 0;
  charsWritten1 = -1;
  key_length = -1;
  char buffer[140000] = {0};
  char buffer1[70000];
  char buffer2[70000];
  char * length = NULL;
  struct sockaddr_in serverAddress, clientAddress;
  socklen_t sizeOfClientInfo = sizeof(clientAddress);
	/* for(int i = 0; i < 130000; i++){
		buffer[i] = 0;
		
	} */
  // Check usage & args
  char challenge[5] = "hello";
  char recv_str[5] = {0}; 
  
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
		send(connectionSocket, "world", 5, 0);
		//sleep(1);
	 charsRead1 = recv(connectionSocket, recv_str, 5, 0);
				
	 if(strcmp(recv_str, "hello") != 0){
		charsWritten1 = send(connectionSocket, "false", 5, 0);
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
				int index = 0;
				 while(1){

				charsRead = recv(connectionSocket, &buffer[index], 139999, 0);  /*<______RECEIVING____!!!!!!!!!!_*/
			 	//printf("DS: many characters Read: %d", charsRead);

				
				//if(buffer[charsRead-1] == '%'){
				   for(int i = 0; i < 139999; i++){
					if(buffer[i] == '%'){
						//printf("what is i %d:", i);
					Read_all = 1;
					break; 
				}  
				   }
				//break;
				//}
				   if(Read_all == 1){
					break; 
				}
								
				 index += charsRead; 
				}   
				char * key_string = NULL;//= malloc(70000* sizeof(char));

				char * message = malloc(70000* sizeof(char));
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
				msg_length = charsRead - key_length -1;
				
				//printf("How long is the message: %d", msg_length);
				//printf("How long is the message: %d", key_length);

				
				//printf("what is read_all %d", Read_all);  
				//printf("what is the calculated message length %d", charsRead - key_length - 1 );
				
				strncpy(message, buffer, charsRead - key_length); 
				 
				//strncat(buffer, message, charsRead - key_length -1);
				//printf("what is the copied string %s", message);
				//printf("something");
			    // key_string = strstr(buffer, '\n');
				 //printf("what is %s", key_string);
			 	
				
				
				//for(int i = msg_length + 1; i < charsRead; i++){
					//printf("what is the character at %d:  %c", i, buffer[i]);
					key_string = &buffer[msg_length];
					
					
					
					
				//}
				//printf("what is the copied string %s", key_string); 

				/* char * key_string_ptr = strstr(&buffer, '/n');
				printf("what is key_string_ptr %s", key_string_ptr);  */
				//
				
				//printf("what is key_string[12345] : %c", key_string[2]);

				char * ciphertext = malloc((msg_length ) * sizeof(char));

				
				// ciphertext[0] = '@';
				 for(int i = 0; i < msg_length-1; i++){

				 int int_msg_char, int_key_char, int_cipher_char;
				 int_msg_char = 0;
				 int_key_char = 0;
				 int_cipher_char= 0;
				if(key_string[i] == 0){
				break; 	
				}
				else if(message[i] == 0){
				break;
				}
				 
				if(message[i] == ' '){
					int_msg_char = 26;
				}
				else{
					int_msg_char = (int)message[i] - 65;
					
				}
				if(key_string[i] == ' '){
					int_key_char = 26;
					
				} 
				else{
				 int_key_char = (int)key_string[i] -65;

					
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
				//printf("what is the ciphertext %c", ciphertext[i]);
				} 
				// printf("what is the ciphertext %s", ciphertext);
				
				
				ciphertext[msg_length-1] = '%';
				//printf("what is the last ciphertext character:%c", ciphertext[key_length-1]);

				
				
				// do{
				charsWritten = send(connectionSocket, ciphertext, key_length, 0);
				//printf("how many characters written: %d", charsWritten);
				
				
				//}while(charsWritten < key_length); 
						
				
				close(connectionSocket); 
				
			  return 0;
				

		default:
			 
		actual_pid = waitpid(spawnPid, &childStatus, WNOHANG);

		
		
			break; 
					}
			
		}
		/* else{
	charsWritten1 = send(connectionSocket, "false", 5, 0);
	
			
			
		} */
	
	}


			  close(listenSocket); 
		return 0;
}


