#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<string>
using namespace std;


void chunkFile(char *fullFilePath,char *chunkName)
{
	ifstream fileStream;
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
			fullChunkName.append(to_string(counter));

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


/*void joinFile(char *chunkName,char *fileOutput)
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
			fileName.append(to_str(counter));
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

}*/
int main()
{
	chunkFile("/home/shraddha/Desktop/OS2/Filechunk","file1chunk");
	//joinFile("file1chunk","newcopy1");
	return 0;
}