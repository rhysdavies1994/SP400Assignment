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



/*Faults:
////////////////////////////////////////////////////////////////////////

//Simple
1.Exactly two (2) stack-based buffer overflows.
	1) when read in magic number string, have fixed size of 10 characters, overflow this
	2) when read in comments string, has fixed size of 20 characters

2.Exactly two (2) heap-based buffer overflows.
	1) when taking input parameters, if more than 5 between input and output file then heap based overflow occurs
	2)

3.Exactly two (2) format string vulnerabilities.
	1) When printing magic number to output file
	2) when printing comments to output file
	
4.Exactly three (3) memory leaks.

5.Exactly one (1) access-after-free of memory.

6.Exactly one (1) double-free.

//Advanced
Memory Access

Code Injection


////////////////////////////////////////////////////////////////////////
*/
//Program Takes command line parameters (instructions, one or more images, output filename)

int main(int argc, char **argv)
{
	
	char *instruction, *instructionParameter, *outputFileName, *inputFileName;
	
	//Vulnerability 2.1
	//working 
	//char **inputs = (char**)malloc(sizeof(char*)*(argc-3));
	char **inputs = (char**)malloc(sizeof(char*)*5);
	
	
	
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
//			int length=strlen(argv[i]);
//			inputs[index]=(char*)malloc(sizeof(char)*length);
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
		PPMImage *firstPPM;
		firstPPM=new PPMImage();
		firstPPM->initFromFile(inputs[0]);
		
		copy(firstPPM, outputFile);
		
		delete firstPPM;
	}
    
    //flip
	else if(strcmp(instruction,"flip")==0)
	{
		//Create a PPMImage class from input
		PPMImage *firstPPM;
		firstPPM=new PPMImage();
		firstPPM->initFromFile(inputs[1]);
		
		if(strcmp(instructionParameter,"h")==0 || strcmp(instructionParameter,"v")==0)
		{
			flip(instructionParameter, firstPPM,outputFile);
		}
		else
		{
			cout << "Flip needs 'h' or 'v' for horizontal or vertical flip\n";
		}
		
		delete firstPPM;
        
	}
    
    //resize
	else if(strcmp(instruction , "resize")==0)
	{
		//Create a PPMImage class from input
		PPMImage *firstPPM;
		firstPPM=new PPMImage();
		firstPPM->initFromFile(inputs[1]);

		double scaleFactor=atof(instructionParameter);

		resize(scaleFactor,firstPPM,outputFile);
        
        delete firstPPM;
	}
    
    //tile
	else if(strcmp(instruction,"tile")==0)
	{
		int amountImages=argc-3;
		PPMImage **images = new PPMImage*[amountImages];
		
		for(int i=0; i<amountImages;i++)
		{
			images[i] = new PPMImage();
			images[i]->initFromFile(inputs[i]);
		}
		
		//Call of tile function
		tile(amountImages,images,outputFile);
		
		
		for(int i=0; i<amountImages;i++)
		{
			delete images[i];
		}
		delete[] images;
	}
	
	fclose(outputFile);
	
	
	free(inputs);
	
	
	return 0;
	
}



void copy(PPMImage *image, FILE *output)
{
    cout << "Copy Function\n";
	
	//3a
	fprintf(output,image->getMagicNumber());
	fprintf(output,"\n");
	
	//3b
	fprintf(output,image->getComments());
	fprintf(output,"%d %d\n",image->getNumberColumns(), image->getNumberRows());
	fprintf(output,"%d\n",image->getMaxRGB());
	

	for(int y=0;y<image->getNumberRows();y++)
	{
		for(int x=0;x<image->getNumberColumns();x++)
		{
			fprintf(output,"%d %d %d \n", 
					image->getPixel(x,y)->getRed(),
					image->getPixel(x,y)->getGreen(),
					image->getPixel(x,y)->getBlue());
		}
	}

    
}

void flip(const char *direction, PPMImage *image, FILE *output)
{
	cout << "Flip function\n";
	
	stringstream value;
	
	value << image->getMagicNumber() <<"\n";
    value << image->getComments() <<"\n";
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
	int newX=0;
	int newY=0; 
	//Calculate new width and height
	int newNumberColumns=(((double)image->getNumberColumns()) *scaleFactor)+0.5;
	int newNumberRows=(((double)image->getNumberRows()) *scaleFactor)+0.5;
	
	//Create object for scaled Image to be stored in
	PPMImage *scaledImage=new PPMImage(newNumberColumns, newNumberRows,image->getMaxRGB());

	//Do nearest neighbour resize
	//Learnt from: tech-algorithm.com/articles/nearest-neighbour-image-scaling/
	
	for(int y=0;y<newNumberRows;y++)
	{
		for(int x=0;x<newNumberColumns;x++)
			{
				newX = (int)floor(x/scaleFactor);
				newY = (int)floor(y/scaleFactor);
				
				int currentRed=image->getPixel(newX,newY)->getRed();
				int currentGreen=image->getPixel(newX,newY)->getGreen();
				int currentBlue=image->getPixel(newX,newY)->getBlue();
				
				scaledImage->setPixel(currentRed, currentGreen, currentBlue,x,y);
			}
	}

	//Print values to file
	value << scaledImage->getMagicNumber() <<"\n";
    value << scaledImage->getComments() <<"\n";
	value << scaledImage->getNumberColumns() << " " << scaledImage->getNumberRows() << "\n";
	value << scaledImage->getMaxRGB() <<"\n";
	value << scaledImage->pixelsToString();
	fprintf(output,"%s",(value.str()).c_str());

	delete scaledImage;
	
}

void tile(int amountImages, PPMImage **images, FILE *output)
{
	cout << "Tile function\n";
	stringstream value;
	//get magic number
	//get width=longest image width, height=all images + height
	//get highest maxRGB value
	//print rows of image 1 then 2 then 3 etc. if column != max width then fill rest of columns in row with 0 0 0 pixels until at max width
	//
	int numberColumns=0;
	int numberRows=0;
	int maxRGB=0;
	
	for(int i=0;i<amountImages;i++)
	{
		if(images[i]->getNumberColumns() > numberColumns)
		{
			numberColumns=images[i]->getNumberColumns();
		}
		
		if(images[i]->getMaxRGB() > maxRGB)
		{
			maxRGB=images[i]->getMaxRGB();
		}
		
		numberRows = numberRows + images[i]->getNumberRows();
        
        
	}
	
	
	value << images[0]->getMagicNumber();
	value << numberColumns << " " << numberRows << "\n";
	value << maxRGB <<"\n";
	
	for(int i=0;i<amountImages;i++)
	{
		for(int y=0;y<images[i]->getNumberRows();y++)
		{		
			for(int x=0;x<numberColumns;x++)
			{
				int imageNumberColumns = images[i]->getNumberColumns();				
				if(imageNumberColumns > x)
				{
					value << images[i]->getPixel(x,y)->toString() <<"\n";
				}
				else
				{
					value << " 0 0 0 \n";
				}
			}
		}
		//value << images[i]->pixelsToString();
	}

	fprintf(output,"%s",(value.str()).c_str());
	
}

void newLine()
{
    cout << "\n";
}

