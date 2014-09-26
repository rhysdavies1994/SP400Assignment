//Standard Includes
#include <iostream>
#include <fstream>
#include <string>


//Namespaces
using namespace std;

//Custom Includes
#include "main.h"
#include "pixel.h"





//Program Takes command line parameters (instructions, one or more images, output filename)

int main(int argc, char **argv)
{
	
	string instruction,image,output;
    
    //Handle command line parameters
    //First argument is instruction
    //Last argument is output folder
    //A secondary argument may be associated with instruction e.g flip h
    //Middle arguments are input files
	if(argc==4)
	{
		instruction = argv[1];
		image = argv[2];
		output = argv[argc-1];
	}
	else
	{
		cout << "3 Input parameters are needed\n";
		return 0;
	}
    
    //Test Command Arguements
	cout << "Arg 1 = " <<instruction << "\n";
	cout << "Arg 2 = " <<image << "\n";
	cout << "Arg 3 = " <<output << "\n";
    
    //	Your program should perform the following operations
	//copy
	if(instruction=="copy")
	{
		copy(image, output);
        
	}
    
    //flip
	else if(instruction =="flip")
	{
		flip();
        
	}
    
    //resize
	else if(instruction == "resize")
	{
		resize();
	}
    
    //tile
	else if(instruction == "tile")
	{
		tile();
	}
	
	
	return 0;
	
}

void copy(string image, string output)
{
	cout << "Copy function\n";
    
    //File IO
    string line;
    ifstream inputFile (image);
    ofstream outputFile;
    outputFile.open (output);
    
    
    if (inputFile.is_open())
    {
        while ( getline (inputFile,line) )
        {
            outputFile << line << '\n';
        }
        inputFile.close();
    }
    else
    {
        cout << "Unable to open file";
    }
    
    outputFile.close();
    
    
}

void flip()
{
	cout << "Flip function\n";
}

void resize()
{
	cout << "Resize function\n";
}

void tile()
{
	cout << "Tile function\n";
}

void newLine()
{
    cout << "\n";
}

