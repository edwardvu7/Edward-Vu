#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

int main(int argc, char **argv){
	unsigned char hash[32];
	for(int i = 0; i < 32; ++i){
		if(argv[1][i*2] >= 'a' && argv[1][i*2] <='f'){
			hash[i] = (argv[1][i*2] - 'a' + 10)<< 4;
		}
		else if(argv[1][i*2] >= 'A' && argv[1][i*2] <= 'F'){
			hash[i] = (argv[1][i*2] - 'A' + 10)<<4;
		}
		else{
			hash[i] = (argv[1][i*2] - '0')<<4;
		}
		if(argv[1][i*2+1] >= 'a' && argv[1][i*2+1] <='f'){
                        hash[i] += (argv[1][i*2+1] - 'a' + 10);
                }
                else if(argv[1][i*2+1] >= 'A' && argv[1][i*2+1] <= 'F'){
                        hash[i] += (argv[1][i*2+1] - 'A' + 10);
                }
                else{
                        hash[i] += (argv[1][i*2+1] - '0');
                }
	}
	char buffer[100];
	unsigned char tempHash[32];
	int match = 1;
	while(fgets(buffer, sizeof(buffer), stdin) != NULL){
		size_t len = strlen(buffer);
		if(buffer[len - 1] == '\n'){
			buffer[len - 1] = 0;
		}
		len = strlen(buffer);
		for(int j = 0; j < len; ++j){
			match = 1;
			char temp[len + 1];
			for(int p = 0; p < len; ++p){
				temp[p] = buffer[p];
			}
			temp[len] = 0;
			if(j != 0){
				if(temp[j - 1] <= 'z' && temp[j - 1] >= 'a'){
					temp[j - 1] -= 32;
				}
				else if(temp[j - 1] <= 'Z' && temp[j - 1] >='A'){
					temp[j - 1] += 32;
				}
			}
			SHA256((unsigned char*) temp, strlen(temp), tempHash);
			for(int i = 0; i < 32; ++i){
				if(hash[i] != tempHash[i]){
					match = 0;
					break;
				}
			}
			if(match == 1){
				printf("Found password: SHA256(%s) = ", temp);
				for(int i = 0; i < 32; ++i){
					printf("%02x", hash[i]);
				}
				printf("\n");
				return 0;
			}			
		}
	}
	printf("Did not find a matching password\n");
	return 0;
}
