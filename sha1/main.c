/* 
* sha1test.c 
* 
* Description: 
* This file will exercise the SHA-1 code performing the three 
* tests documented in FIPS PUB 180-1 plus one which calls 
* SHA1Input with an exact multiple of 512 bits, plus a few 
* error test checks. 
* 
* Portability Issues: 
* None. 
* 
*/  
  
#include <stdint.h>  
#include <stdio.h>  
#include <string.h>  
#include "sha1.h"  
/* 
* Define patterns for testing 
*/   
#define PrintArray(x) do{printf("Name:%s, Length:%ld\n", #x, sizeof(x));for(int i = 0; i < sizeof(x);i++){\
		printf("0x%02x ", x[i]);\
	}printf("\n\n");}while(0)
const char key[] = {00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00};
const char challenge[] = {00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,00,0x01,0x23};
char TEST[36] = {0};

int main()  
{  
    SHA1Context sha;  
    int i, j, err;  
    uint8_t Message_Digest[20];  
    uint8_t Message_Result[20];  
	
	PrintArray(key);
	PrintArray(challenge);
	
	err = SHA1Reset(&sha);  
	if (err)  
	{  
		fprintf(stderr, "SHA1Reset Error %d.\n", err );  
		return -1;
	}  
	memcpy(TEST, key, sizeof(key));
	memcpy(&TEST[sizeof(key)], challenge, sizeof(challenge));
	PrintArray(TEST);
	err = SHA1Input(&sha, (const unsigned char *) TEST, sizeof(TEST));  
	if (err)  
	{  
		fprintf(stderr, "SHA1Input Error %d.\n", err );  
		return -1; 
	}  
	
	err = SHA1Result(&sha, Message_Digest);  
	if (err)  
	{  
		fprintf(stderr,"SHA1Result Error %d, could not compute message digest.\n", err );  
		return -1;
	}  
	else  
	{  
		printf("SHA-1:\t");  
		for(i = 0; i < 20 ; ++i)  
		{  
			printf("%02X ", Message_Digest[i]);  
		}  
		printf("\n");  
	}    
	
	SHA1Reset(&sha);
	memcpy(&TEST[sizeof(key)], Message_Digest, sizeof(Message_Digest));
    err = SHA1Input(&sha, (const unsigned char *) TEST, sizeof(TEST));  
	if (err)  
	{  
		fprintf(stderr, "SHA1Input Error %d.\n", err );  
		return -1; 
	}  
	
	err = SHA1Result(&sha, Message_Result);  
	if (err)  
	{  
		fprintf(stderr,"SHA1Result Error %d, could not compute message digest.\n", err );  
		return -1;
	}  
	else  
	{  
		printf("SHA-1:\t");  
		for(i = 0; i < 20 ; ++i)  
		{  
			printf("%02X ", Message_Result[i]);  
		}  
		printf("\n");  
	}    
    return 0;  
}  
