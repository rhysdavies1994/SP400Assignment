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



//Faults:
//Stack Based Buffer-overflow: 
//	1) when read in magic string, have fixed size of magicNumber, overflow this
//	2)


//Program Takes command line parameters (instructions, one or more images, output filename)

int main(int argc, char **argv)
{
	
	char *instruction, *instructionParameter, *outputFileName, *inputFileName;
	char **inputs = (char**)malloc(sizeof(char*)*(argc-3));
	
		
	
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
		
		for(int i=2; i<=argc-2;i++)
		{	
			int index=i-2;			
			int length=strlen(argv[i]);
			inputs[index]=(char*)malloc(sizeof(char)*length);
			inputs[index]=argv[i];
			
			if(strcmp(instruction,"flip")==0 || strcmp(instruction,"resize")==0)
			{
				hasInstructionParameter=true;
				instructionParameter=inputs[0];
			
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
	outputFile = fopen(outputFileName,"w");

	
    //	Your program should perform the following operations
	//copy
	if(strcmp(instruction,"copy")==0)
	{
		//Create a PPMImage class from input
		firstPPM=new PPMImage();
		firstPPM->initFromFile(inputs[0]);

		copy(firstPPM, outputFile);
		
	}
    
    //flip
	else if(strcmp(instruction,"flip")==0)
	{
		//Create a PPMImage class from input
		firstPPM=new PPMImage();
		firstPPM->initFromFile(inputs[1]);

		if(strcmp(instruction,"flip")==0 || strcmp(instruction,"resize")==0)
		{
		flip(instructionParameter, firstPPM,outputFile);
		}
		else
		{
			cout << "Flip needs 'h' or 'v' for horizontal or vertical flip\n";
		}
        
	}
    
    //resize
	else if(strcmp(instruction , "resize")==0)
	{
		
	}
    
    //tile
	else if(strcmp(instruction,"tile")==0)
	{

		tile(argc,inputs,outputFile);
	}
	fclose(outputFile);
	delete(firstPPM);
	
	for(int i=2; i<argc-2;i++)
		{	
		free(inputs[i]);			
		}
	free(inputs);

	
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
	value << image->getNumberColumns() << " " << image->getNumberRows() << "\n";
	value << image->getMaxRGB() <<"\n";
	
	if(strcmp(direction,"h")==0)
	{
		
		printf("NumberRows = %d\n",image->getNumberRows());
		printf("NumberColumns = %d\n",image->getNumberColumns());	
	
		
			
			for(int y=image->getNumberRows()-1;y>=0;y--)
			{
			for(int x=image->getNumberColumns()-1;x>=0;x--)
		{
				value << (image->getPixel(x,y)->toString()).c_str() <<"\n";
			}
		}
		
		
	}
	else if(strcmp(direction,"v")==0)
	{
	 	printf("NumberRows = %d\n",image->getNumberRows());
		printf("NumberColumns = %d\n",image->getNumberColumns());	
	
		
		for(int y=0;y<=image->getNumberRows()-1;y++)
		{
			for(int x=image->getNumberColumns()-1;x>=0;x--)
			{
					value << (image->getPixel(x,y)->toString()).c_str() <<"\n";
			}
		}
	}
	else
	{
		printf("Invalid Direction for Flip");
	}
	
	fprintf(output,"%s", (value.str()).c_str());
}

void resize(double scaleFactor, PPMImage *image, FILE *output)
{
	cout << "Resize function\n";
	
	stringstream value;
	int newNumberColumns=(((double)image->getNumberColumns()) *scaleFactor)+0.5;
	int newNumberRows=(((double)image->getNumberRows()) *scaleFactor)+0.5;

	value << image->getMagicNumber() <<"\n";
	value << image->getNumberColumns() << " " << image->getNumberRows() << "\n";
	value << image->getMaxRGB() <<"\n";

	//Do nearest neighbour resize stuff
	//tech-algorithm.com/articles/nearest-neighbour-image-scaling/
	
	

}

void tile(int numberImages, PPMImage **images, FILE *output)
{
	cout << "Tile function\n";

	//get magic number
	//get width=longest image width, height=all images + height
	//get highest maxRGB value
	//print rows of image 1 then 2 then 3 etc. if column != max width then fill rest of columns in row with 0 0 0 pixels until at max width
	//

	stringstream value;

	int newNumberColumns=(((double)image->getNumberColumns()) *scaleFactor)+0.5;
	int newNumberRows=(((double)image->getNumberRows()) *scaleFactor)+0.5;

	value << image->getMagicNumber() <<"\n";
	value << image->getNumberColumns() << " " << image->getNumberRows() << "\n";
	value << image->getMaxRGB() <<"\n";


}

void newLine()
{
    cout << "\n";
}

