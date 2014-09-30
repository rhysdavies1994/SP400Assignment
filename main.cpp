#define C_LINELENGTH 70

//Standard Includes
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */

//Namespaces
using namespace std;

//Custom Includes
#include "main.h"
#include "pixel.h"






//Program Takes command line parameters (instructions, one or more images, output filename)

int main(int argc, char **argv)
{
	
	string instruction, instructionParameter, outputFileName, inputFileName;
	string *inputs = new string[argc-3];
	PPMImage *firstPPM;
	bool hasInstructionParameter=false;
    
    //Handle command line parameters
    //First argument is instruction
    //Last argument is output folder
    //A secondary argument may be associated with instruction e.g flip h
    //Middle arguments are input files
	if(argc >= 4)
	{
		instruction = argv[1];
		
		for(int i=2; i<argc-2;i++)
		{
			inputs[i]=argv[i];
			
			if(instruction=="flip" || instruction=="resize")
			{
				hasInstructionParameter=true;
				instructionParameter=inputs[2];
			
			}
		
			
		}

		outputFileName = argv[argc-1];
	}
	else
	{
		cout << "3 Input parameters are needed\n";
		return 0;
	}
    
    //Test Command Arguements
//	cout << "Arg 1 = " <<instruction << "\n";
//	cout << "Arg 2 = " <<image << "\n";
//	cout << "Arg 3 = " <<output << "\n";
    
		
	FILE *outputFile;
	outputFile = fopen(outputFileName.c_str(),"w");

	
    //	Your program should perform the following operations
	//copy
	if(instruction=="copy")
	{
		//Create a PPMImage class from input
		firstPPM=new PPMImage();
		firstPPM->initFromFile(inputs[2]);

		copy(firstPPM, outputFile);
		
	}
    
    //flip
	else if(instruction =="flip")
	{
		//Create a PPMImage class from input
		firstPPM=new PPMImage();
		firstPPM->initFromFile(inputs[3]);

		if(instructionParameter=="h" || instructionParameter=="v")
		{
		flip(instructionParameter.c_str(), firstPPM,outputFile);
		}
		else
		{
			cout << "Flip needs 'h' or 'v' for horizontal or vertical flip";
		}
        
	}
    
    //resize
	else if(instruction == "resize")
	{
		
	}
    
    //tile
	else if(instruction == "tile")
	{
		
	}
	fclose(outputFile);
	delete(firstPPM);
	
	return 0;
	
}

//Easy way to copy ppm - just copy every line to new file
//void copy(string image, string output)
//{
//	cout << "Copy function\n";
//
//    //File IO
//    string line;
//    ifstream inputFile (image);
//    ofstream outputFile;
//    outputFile.open (output);
//
//
//    if (inputFile.is_open())
//    {
//        while ( getline (inputFile,line) )
//        {
//            outputFile << line << '\n';
//        }
//        inputFile.close();
//    }
//    else
//    {
//        cout << "Unable to open file";
//    }
//
//    outputFile.close();
//
//
//}

void copy(PPMImage *image, FILE *output)
{
    cout << "Copy Function\n";
	
	fprintf(output,"%s",(image->toString()).c_str());
    
}

void flip(const char *direction, PPMImage *image, FILE *output)
{
	cout << "Flip function\n";
	
	stringstream value;
	
	value << image->getMagicNumber() <<"\n";
	value << image->getAmountRows() << " " << image->getAmountColumns() << "\n";
	value << image->getMaxRGB() <<"\n";
	
	if(strcmp(direction,"h")==0)
	{
		
		
		for(int i=image->getAmountRows()-1;i>0;i--)
		{
			
			for(int j=0; j<image->getAmountColumns()-1;j++)
			{
				value << (image->getPixel(i,j)->toString()).c_str() <<"\n";
			}
		}
		
		
	}
	else if(strcmp(direction,"v")==0)
	{
	 
	}
	else
	{
		printf("Invalid Direction for Flip");
	}
	
	fprintf(output,"%s", (value.str()).c_str());
}

void resize(int scaleFactor, PPMImage *image, FILE *output)
{
	cout << "Resize function\n";
}

void tile(PPMImage **images, FILE *output)
{
	cout << "Tile function\n";
}

void newLine()
{
    cout << "\n";
}

