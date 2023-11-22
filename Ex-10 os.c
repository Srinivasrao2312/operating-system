#include <stdio.h> 
#define MAX 10 


struct mesg_buffer { 
	long mesg_type; 
	char mesg_text[100]; 
} message; 

int main() 
{  
	int msgid; 

	 
	message.mesg_type = 1; 

	printf("Write Data : "); 
	fgets(message.mesg_text,MAX,stdin); 

	
	printf("Data send is : %s \n", message.mesg_text); 

	return 0; 
} 
