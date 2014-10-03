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
		firstPPM=new PPMImage();
		firstPPM->initFromFile(inputs[0]);
		
		copy(firstPPM, outputFile);
		delete firstPPM;
	}
    
    //flip
	else if(strcmp(instruction,"flip")==0)
	{
		//Create a PPMImage class from input
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
		delete images;
	}
	
	fclose(outputFile);
	
	
	//for(int i=2; i<argc-2;i++)
	//{
	//	int index=i-2;
	//	free(inputs[index]);
	//}
	free(inputs);
	
	
	return 0;
	
}



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
				scaledImage->setPixel(image->getPixel(newX,newY),x,y);
			}
	}

	//Print values to file
	value << scaledImage->getMagicNumber() <<"\n";
    value << scaledImage->getComments() <<"\n";
	value << scaledImage->getNumberColumns() << " " << scaledImage->getNumberRows() << "\n";
	value << scaledImage->getMaxRGB() <<"\n";
	value << scaledImage->pixelsToString();
	fprintf(output,"%s",(value.str()).c_str());

	
	
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

