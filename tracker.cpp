#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<stdio.h>
#include<vector>
#include<bits/stdc++.h>

#include<unistd.h>         //for close() function
#include<sys/socket.h>     //to use socket(),bind()
#include<netinet/in.h>
#include<arpa/inet.h>		//all 2,3 and 4th header file are being used for inet_addr

#include<cstdlib>
#include<pthread.h>
using namespace std;

//Helper function to convert a sentence into array of words
string[] wordbreak(string temp)
{
	string t[],t1="";
	int i=0;
	for(auto x:temp)
	{
		if(x==' ')
		{
			t[i++]=t1;
			t1="";
		}
		else
		{
			t1=t1+x;
		}
	}
	return t;
}


//Structure to create a user account 
struct user
{
	string uname;
	string passwd;
	bool grant=false;
}userarr[100]={'NULL','NULL'};



//Function to check user credentials to login
bool logincheck(string un,string pwd)
{
	for(int i=0;userarr[i].uname!='NULL';i++)
	{
		if(userarr[i].uname==un)
		{
			if(userarr[i].passwd==pwd)
			{
				return userarr[i].grant=true;
			}
		}
	}
	return false;
}

//structure to store basic file info
struct file
{
	int fileid;
	string filename;
	string sha;
};


//structure to store basic info of a client
struct client
{
	int clientid;
	group g1[10]={.groupid=-5};			//-5 denotes that there is no such group 
	file f1[100]={.fileid=-1};			//-1 denotes that there is no such file
};

//structure to create group
struct group
{
	int groupid;
	int noofclients;
	string groupowner;
	string client[100]="NULL";
}g[100]={.groupid=-5};
int j=0;
//Function to divide the functionality as per given command
void *threadFn(void *i)
{
	cout<<"In thread  "<<endl;
	string temp=i;
    string cmd1[]=wordbreak(temp);
     switch(cmd1[0])
     {
     	case "create_user":
     	{
     		userarr[++i].uname=cmd1[1];
     		userarr[++i].passwd=cmd1[2];
     		break;
     	}
     	case "login":
     	{
     		bool g=logincheck(cmd1[1],cmd1[2]);
     		if(g==true)
     		{
     			cout<<"Access granted\n";
     		}
     		else
     		{
     			cout<<"Not a valid user\n";
     		}
     		break;
     	}
     	case "create_group":
     	{
     		group g[j++]=new group();
     		g1=cmd1[1];
     		g1.groupowner=currentclientinfo;  //extract currentclientinfo
     	}
     	case "join_group":
     	{
     		for(int i=0;)
     			
     		break;
     	}
     	case "leave_group":
     	{
     		// 1.open cocerned data structure storing the client details 
     		// 2.delete the entry for the concerned group
     		// 3.check in group details if none clients are there then delete the group itself 
     		break;
     	}
     	case "list_requests":
     	{
     		//don't kow what to do ask someone
     		break;
     	}
     	case "accept_request":
     	{
// 		//Ask someone
     		break;
     	}
     	case "list_groups":
     	{
     		/*1.open the concerned group data structure
     		2.display all the groups with group ids maybe the clients under them too */
     		break;
     	}
     	case "list_files":
     	{
     		/*1.open the list files present in tracker
     		2.display it*/
     		break;
     	}
     	case "upload_file":
     	{
     		/*1.think of the structure first
     		*/
    		break;
     	}
     	case "download_file":
     	{
     		/*1.think of the structure first
     		*/
     		break;
     	}
     	case "logout":
     	{
     		/*1.change that grant variable for this particular client to false again*/
     		break;
     	}
     	case "Show_downloads":
     	{
     		/*1.complete rest first*/
     		break;
     	}
     	case "stop_share":
     	{
     		/*1.complete rest first*/
     		break;
     	}
     	case "quit":
     	{
     		cout<<"Shutting down the tracker...\n";
     		exit(1);
     	}
   	default:
   		cout<<"Enter valid command!!!\n";
    }
}
int main(int argc,char **argv)
{
	/*string filename=argv[1];
	string temp=argv[2];
	stringstream num(temp);
	int trackno=0;
	num>>trackno;				//trackno is supposed to start from 0 
	ifstream fi(argv[1]);
	string s;
	if(fi.is_open())
	{			
		for(int i=0;i<trackno;i++)
			getline(fi,s);
	}
	getline(fi,s);
	string samp="Shraddha is a good girl";
	istringstream iss(samp);
   	do
  	{
  		string tok="";
  		iss>>tok;
  		cout<<tok<<endl;
  	}while(iss);
	/*stringstream num1(token);
	int portno=0;
	num1>>portno;
    token = strtok(NULL, " "); 			
    string ip=token;
    cout<<portno<<"	"<<ip;*/


//--------------------------------------------------------------
  	//Lets say we have port no. and ip of concerned tracker with us now
  	//SERVER PART OF TRACKER
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
    char message[500];
    int temp;
    temp=recv(new_socket,&message,sizeof(message),0);
    printf("%s",message);
    close(new_socket);

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
    //-------------------------------------------------------------------------------------------------
    //connection part completed now.
    //message recieved->create a seperate thread->send the message to that

    pthread_t t1;
	int i=0;
	int rc=pthread_create(&t1,NULL,threadFn,(void *)&message);
	if(rc)
	{
		cout<<"Error..."<<rc<<endl;
		exit(-1);
	}
	pthread_exit(NULL);
    //create_user part
    
   

	return 0;
}
