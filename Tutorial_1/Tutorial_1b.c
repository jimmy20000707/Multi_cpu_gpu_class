#include <stdio.h>
#include <string.h>

void encoder(char *str){
	for(int i = 0; str[i] ; i++){
		if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' ||
		   str[i] == 'o' || str[i] == 'u'){
			str[i]='p';
		}
		if(str[i] == 'A' || str[i] == 'E' || str[i] == 'I' ||
		   str[i] == 'O' || str[i] == 'U'){
			str[i]='p';
		}
	}
}

int main(){
	char message[256];
	printf("Enter your message: ");
	fgets(message,sizeof(message),stdin);
	size_t len = strlen(message);
	if(len > 0 && message[len-1] =='\n'){
		message[len-1] ='\0';
	}
	encoder(message);
	printf("Encoded message: %s\n",message);
}

