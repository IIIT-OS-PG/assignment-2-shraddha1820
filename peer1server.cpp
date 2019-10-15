#include<iostream>
#include<unistd.h>         //for clode() function
#include<sys/socket.h>     //to use socket(),bind()
#include<netinet/in.h>
#include<arpa/inet.h>		//all 2,3 and 4th header file are being used for inet_addr
#include<string.h>
using namespace std; 
/*
void joinFile(char *,char *);
int getFileSize(ifstream *);
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
	
	//2.Binding
	struct sockaddr_in serveraddr;
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_port=htons(2000);
	serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	int ad=sizeof(sockaddr);
	int ret=bind(sockid,(struct sockaddr *)&serveraddr,sizeof(serveraddr));

	if(ret<0)
	{
		cout<<"Error in binding"<<endl;
		exit(1);
	}
	else
	{
		cout<<"Binding done successfully"<<endl;
	}
	
	//3.Listen
	int qlimit=5;						//No.peers which can wait for server
    int status=listen(sockid,qlimit);   //listen for any requests for connection
	
    if(status<0)
    {
    	cout<<"Listening Failed...";
    	exit(1);
    }
    else
    {
    	cout<<"Listening done successfully"<<endl;
    }

    //4.Accept
    int new_socket=accept(sockid,(struct sockaddr *)&serveraddr,(socklen_t*)&ad);
    //5.Recieve
    FILE *fp=fopen("new.pdf","wb");
    char Buffer[1000];
    int file_size,temp,n;
    temp=recv(new_socket,&file_size,sizeof(file_size),0);
  	cout<<file_size<<endl;
  	while((n=recv(new_socket,Buffer,500,0))>0&&file_size>0)
  	{
  		fwrite(Buffer,sizeof(char),temp,fp);
  		memset(Buffer,'\0',500);
  		
  		file_size=file_size-n;
  	}
   /* int x;
  	recv(new_socket,&x,sizeof(x),0);
  	cout<<x;*/
  	close(new_socket);
  
    //6.Send
    /*
    int count=send(sockid,msg,strlen(msg),0);
    if(count<0)
    {
    	cout<<"Some error in sending the message ";
    	exit(1);
    }
    else
    {
    	cout<<count<<" bytes successfully transferred..."<<endl;
    }
    */
    //7.close
    int s2=close(sockid);
    if(s2==0)
    {
    	cout<<"successfully closed on server side..."<<endl;
    	exit(1);
    }
    else
    {
    	cout<<"Closing failed on server side";
    }

    fclose(fp);
	return 0;

}

/*
void joinFile(char *chunkName,char *fileOutput)
{
	string fileName;

	ofStream outputfile;
	outputfile.open(fileOutput,ios::out|ios::binary);
	if(outputfile.is_open())
	{
		bool filefound=true;
		int counter=1;
		int filesize=0;

		while(filefound)
		{
			filefound=false;

			fileName.clear();	//constructing chunk name to gather later
			fileName.append(chunkName);
			fileName.append(".");

			char intBuf[10];
			_itoa(counter,intBuf,10);
			fileName.append(intBuf);

			ifstream fileInput;	  //to read chunk
			fileInput.open(fileName.c_str(),ios::in|ios::binary);

			//if opened successfully
			if(fileInput.is_open())
			{
				filefound=true;
				fileSize=getFileSize(&fileInput);
				char *inputBuffer=new char[fileSize];

				fileInput.read(inputBuffer,fileSize);
				outputfile.write(inputBuffer,fileSize);
				delete(inputBuffer);

				fileInput.close();
			}

			count++;
		}
		outputfile.close();
		cout<<"File assembly complete!"<<endl;
	}
	else
		cout<<"Error:unable to open file for output."<<endl;

}


int getFileSize(ifstream *file)				//returns filesize
{
	file->seekg(0,ios::end);
	int filesize=file->tellg();
	file->seekg(ios::beg);
	return filesize;
}
*/