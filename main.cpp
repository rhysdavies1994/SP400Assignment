//Standard Includes
#include <iostream>
#include <fstream>

//Namespaces
using namespace std;

//Custom Includes
#include "main.h"
#include "pixel.h"





//Program Takes command line parameters (instructions, one or more images, output filename)

int main(int argc, char **argv)
{
	
	string instruction,image,outputFolder;
    Pixel *pOne = new Pixel(1,2,3);
    cout << pOne->toString() << pOne->toString();
    newLine();
    
    //Handle command line parameters
    //First argument is instruction
    //Last argument is output folder
    //A secondary argument may be associated with instruction e.g flip h
    //Middle arguments are input files
	if(argc==4)
	{
		instruction = argv[1];
		image = argv[2];
		outputFolder = argv[argc-1];
	}
	else
	{
		cout << "3 Input parameters are needed\n";
		return 0;
	}
    
    //Test Command Arguements
	cout << "Arg 1 = " <<instruction << "\n";
	cout << "Arg 2 = " <<image << "\n";
	cout << "Arg 3 = " <<outputFolder << "\n";
    
	//	Your program should perform the following operations
	//copy
	if(instruction=="copy")
	{
		copy(image, outputFolder);
        
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

void copy(string image, string outputFolder)
{
	cout << "Copy function\n";
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

