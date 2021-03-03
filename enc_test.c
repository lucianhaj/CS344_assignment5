
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(){
	//Encrypts buffer into ciphertext
	char ciphertext[1000] = {0};
	char buffer[] = "THE RED GOOSE FLIES AT MIDNIGHT STOP";
	char buffer2[] = "LRBLUKKSC EUZGVWFWVQACONLYWTS NBPOYHY";

	 for(int i = 0; i < strlen(buffer); i++){

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
	printf("Encrypted: %s \n", ciphertext);
	
	 for(int i = 0; i < strlen(ciphertext); i++){

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
		int_cipher_char = int_msg_char - int_key_char;
		if(int_cipher_char < 0 ){
			int_cipher_char += 27;
			
		} 
		if(int_cipher_char == 26){
		ciphertext[i] = (char)(32);
		}
		else{
		ciphertext[i] = (char)(int_cipher_char+65);
		}
				  
				} 
	printf("Decrypted: %s \n", ciphertext);

				
}