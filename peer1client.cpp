#include<iostream>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>     //to use socket(),bind()
#include<netinet/in.h>
#include<arpa/inet.h>		//all 2,3 and 4th header file are being used for inet_addr
using namespace std;

/*
void chunkFile(char *,char *);
*/
int main()
{
	//1.Socket Creation
	int sockid=socket(PF_INET,SOCK_STREAM,0);    //SOCK_STREAM is for TCP,For datagram socket it will be SOCK_DGRAM
	if(sockid<0)
	{
		cout<<"Error in connection"<<endl;
		exit(1);
	}
	else
	{
		cout<<"Socket created successfully"<<endl;
	}
	
	//2.Connect
	struct sockaddr_in serveraddr;
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(2000);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");

	int status=connect(sockid,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	if(status<0)
	{
		cout<<"Connection Failed"<<endl;
		exit(1);
	}
	else
	{
		cout<<"Connection Successfull"<<endl;
	}


	//3.Send
	/*FILE *fp=fopen("/home/shraddha/Downloads/Passbook.pdf","rb");
	fseek(fp,0,SEEK_END);
	int size=ftell(fp),n;			//returns pointer to file
	rewind(fp);
	char Buffer[1000];*/
	char message[100]="Heya girl...Cheer up!!!";
    send(sockid,&message,sizeof(message),0);
	//chunkFile("/home/shraddha/Downloads/Passbook.pdf","actual_chunks");
	/*while((n=fread(Buffer,sizeof(char),500,fp))>0&&size>0)
	{
		send(sockid,Buffer,n,0);
		memset(Buffer,'\0',500);
		size=size-n;
	}
	
    fclose(fp);*/
	/*int x=10;
	send(sockid,&x,sizeof(x),0);*/
	//4.Recieve

	//5.Close the connection
	int s2=close(sockid);
    if(s2==0)
    {
    	cout<<"successfully closed on client side..."<<endl;
    	exit(1);
    }
    else
    {
    	cout<<"Closing failed on client side"<<endl;
    }

	return 0;

}
/*

void chunkFile(char *fullFilePath,char *chunkName)
{
	ifstream filesStream;
	fileStream.open(fullFilePath,ios::in|ios::binary);

	//File open success
	if(fileStream.is_open())
	{
		ofstream output;
		int counter=1;

		string fullChunkName;

		char *buffer=new char[512];		//buffer to hold chunk
		while(!fileStream.eof())
		{
			fullChunkName.clear();		//Creating a name for buffer
			fullChunkName.append(chunkName);
			fullChunkName.append(".");

			char intBuf[10];			//chunkname.1
			itoa(counter,intBuf,10);
			fullChunkName.append(intBuf);

			//New chunk file for output
			output.open(fullChunkName.c_str(),ios::out|ios::trunc|ios::binary);

			if(output.is_open())
			{
				fileStream.read(buffer,512);
				output.write(buffer,fileStream.gcount());
				output.close();

				counter++;
			}
		}

		delete(buffer);

		fileStream.close();
		cout<<"Chunks made successfully"<<counter-1<<" files created."<<endl;
	}
	else
		cout<<"Error opening file"<<endl;
}
*/