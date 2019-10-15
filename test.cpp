#include<openssl/sha.h>
#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;
int main()
{
	char data[]="Hello,world!";
	size_t length = strlen(data);
	cout<<length;
    unsigned char hash[20];
	SHA1((unsigned char *)&data,length,(unsigned char *)&data);
	printf("%s\n",hash);
	
	
	return 0;
}
