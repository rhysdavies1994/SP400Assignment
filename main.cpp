// classes example
#include <iostream>
#include "rectangle.h"
using namespace std;


//Program Takes command line parameters (instructions, one or more images, output filename)

int main(int argc, char **argv)
{
	
	string instruction,image,outputFolder;
	
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
	cout << "Arg 1 = " <<instruction << "\n";
	cout << "Arg 2 = " <<image << "\n";
	cout << "Arg 3 = " <<outputFolder << "\n";
	
	
	//	Your program should perform the following operations
	//		copy
	//		flip
	//		resize
	//		tile
	
	
	if(instruction=="copy")
	{
		cout << "Copy function\n";
	}
	else if(instruction =="flip")
	{
		cout << "Flip function\n";
	}
	else if(instruction == "resize")
	{
		cout << "Resize function\n";
	}
	else if(instruction == "tile")
	{
		cout << "Tile function\n";
	}
	
	
	
	
	
	//How to handle argument
	//	arg[1] = instruction
	//	if(arg 1 is flip
	//		arg2 is value
	//	for( currentLength to lastLength)
	//    	{
	//		run program
	//		}
	//	arg[last] = output
	
	return 0;
	
}

void copy(string image, string outputFolder)
{
	
}

void flip()
{
	
}

void resize()
{
	
}

void tile()
{
	
}


