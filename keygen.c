#include <time.h>
#include <math.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>




	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
int main(int argc, char *argv[]) {	
srand(time(NULL));
int random_int = 0; 
int length = atoi(argv[1]);
int i = 0; 
char alphabet_string[28] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', ' '};


char * key_string = malloc((length + 2) * sizeof(char));
char * character = NULL;
char c;
for(i = 0; i < length; i++){
	random_int = rand() % 27;
	//printf("random int: %d \n", random_int);
	key_string[i] = alphabet_string[random_int]; 
}
key_string[i] = '\n';


for(i = 0; i < length+1; i++){
	
	fputc(key_string[i], stdout);
	
	
}

}