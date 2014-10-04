#define C_LINELENGTH 70

//Standard Includes
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include <ctime>

//Namespaces
using namespace std;

//Custom Includes
#include "main.h"
#include "pixel.h"



/*Faults:
////////////////////////////////////////////////////////////////////////

//Simple
1.Exactly two (2) stack-based buffer overflows.
	a) when read in magic number string, have fixed size of 10 characters, overflow this
	b) when read in comments string, has fixed size of 20 characters

2.Exactly two (2) heap-based buffer overflows.
	a) when taking input parameters, if more than 5 between input and output file then heap based overflow occurs
	b) When reading input file, if a line is over 70 characters, heap will overflow

3.Exactly two (2) format string vulnerabilities.
	a) When printing magic number to output file
	b) when printing comments to output file
	
4.Exactly three (3) memory leaks.
	a)When destructing PPMImage, forget to delete pixel pointers, only arrays
	b)When reading through input file, forget to delete current pixel
	c)Before leaving program, forgets to free inputs array
	
5.Exactly one (1) access-after-free of memory.
	When resizing, if scale value is equal to 1 a shallow copy is made, 
	yet still freed inside resize, when trying to print PPMImage's
	sourceFileName to file it will be accessing memory after free

6.Exactly one (1) double-free.
	When Tiling images, If only one image, reuse copy function to save code
	reuse, although this creates a shallow copy which is deleted, therefore
	deleting memory passed into tile function, which is also freed outside 
	of tile


//Advanced
Memory Access

Code Injection


////////////////////////////////////////////////////////////////////////
*/
//Program Takes command line parameters (instructions, one or more images, output filename)

int main(int argc, char **argv)
{
	FILE *outputFile;
	FILE *logFile;
	time_t now;
	tm *currentTime;
	char *instruction, *instructionParameter, *outputFileName, *inputFileName;
	bool hasInstructionParameter=false;
	//Vulnerability 2a
	//when taking input parameters, if more than 5 between input and output file then heap based overflow occurs
	char **inputs = (char**)malloc(sizeof(char*)*5);
	

    
    ///////Handle command line parameters//////
    //First argument is instruction
    //Last argument is output folder
    //Middle arguments are input files/arguments
    //A secondary argument may be associated with instruction e.g flip h
    ///////////////////////////////////////////
	if(argc >= 4)
	{
		instruction = argv[1];
		
		for(int i=2; i<=argc-2;i++)
		{
			int index=i-2;
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

	
	outputFile = fopen(outputFileName,"w");
	logFile = fopen("logFile.txt","a");
	
    //Your program should perform the following operations
	//Copy
	if(strcmp(instruction,"copy")==0)
	{
		//Create a PPMImage class from input
		PPMImage *firstPPM;
		firstPPM=new PPMImage();
		firstPPM->initFromFile(inputs[0]);
		
		copy(firstPPM, outputFile);
		
		//Write to log file
		now = time(0);
		currentTime = localtime(&now);
		fprintf(logFile,"%d/%d/%d at %d-%d-%d: \"%s\" has been COPIED\n",
				currentTime->tm_mday,
				1 + currentTime->tm_mon,
				1900 + currentTime->tm_year,
				1 + currentTime->tm_hour,
				1 + currentTime->tm_min,
				1 + currentTime->tm_sec,
				firstPPM->getSourceFileName().c_str());

		
		delete firstPPM;
	}
    
    //Flip
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
		
		//Write to log file
		now = time(0);
		currentTime = localtime(&now);
		fprintf(logFile,"%d/%d/%d at %d-%d-%d: \"%s\" has been FLIPPED\n",
				currentTime->tm_mday,
				1 + currentTime->tm_mon,
				1900 + currentTime->tm_year,
				1 + currentTime->tm_hour,
				1 + currentTime->tm_min,
				1 + currentTime->tm_sec,
				firstPPM->getSourceFileName().c_str());
		
		delete firstPPM;
        
	}
    
    //Resize
	else if(strcmp(instruction , "resize")==0)
	{
		//Create a PPMImage class from input
		PPMImage *firstPPM;
		firstPPM=new PPMImage();
		firstPPM->initFromFile(inputs[1]);

		double scaleFactor=atof(instructionParameter);
		

		resize(scaleFactor,firstPPM,outputFile);
        
        //Vulnerability 5
        //When resizing, if scale value is equal to 1 a shallow copy is made, yet still freed inside resize, when trying to print PPMImage's sourceFileName to file it will be accessing memory after free
        //Write to log file
		now = time(0);
		currentTime = localtime(&now);
		fprintf(logFile,"%d/%d/%d at %d-%d-%d: \"%s\" has been RESIZED\n",
				currentTime->tm_mday,
				1 + currentTime->tm_mon,
				1900 + currentTime->tm_year,
				1 + currentTime->tm_hour,
				1 + currentTime->tm_min,
				1 + currentTime->tm_sec,
				firstPPM->getSourceFileName().c_str());
        
        //Delete 
        delete firstPPM;
	}
    
    //Tile
	else if(strcmp(instruction,"tile")==0)
	{
		//Get amount of images 
		//== numParameters - output(1) - instruction(1) - program name(1) 
		//== numParameters - 3
		int amountImages=argc-3;
		
		//Create list of PPMImages
		PPMImage **images = new PPMImage*[amountImages];
		
		//Create an PPMImage object for each input filename
		//Allocate memory for use
		for(int i=0; i<amountImages;i++)
		{
			images[i] = new PPMImage();
			images[i]->initFromFile(inputs[i]);
			
			//Write to log file
		now = time(0);
		currentTime = localtime(&now);
		fprintf(logFile,"%d/%d/%d at %d-%d-%d: \"%s\" has been TILED\n",
				currentTime->tm_mday,
				1 + currentTime->tm_mon,
				1900 + currentTime->tm_year,
				1 + currentTime->tm_hour,
				1 + currentTime->tm_min,
				1 + currentTime->tm_sec,
				images[i]->getSourceFileName().c_str());
		}
		
		//Call of tile function
		tile(amountImages,images,outputFile);
		
		//Free Memory used
		for(int i=0; i<amountImages;i++)
		{
			delete images[i];
		}
		delete[] images;
	}
	
	//Close files
	fclose(logFile);
	fclose(outputFile);
	
	//Vulnerability 4c
	//Before leaving program, forgets to free inputs array
	//Without the code below, a memory leak will occur
	//free(inputs);
	
	//Exit Program
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
	PPMImage *scaledImage;
	
	cout << "Resize function\n";
	
	stringstream value;
	
	
	//Vulnerability 6
	//When resizing, If scaling factor is 1, dont process to scale image, just create a shallow copy which will be deleted at end of resize function, and the passed in image is freed outside of function, causing a double free
	if(scaleFactor==1)
	{
	scaledImage=image;
	}
	else
	{
		int newX=0;
		int newY=0; 
		//Calculate new width and height
		int newNumberColumns=(((double)image->getNumberColumns()) *scaleFactor)+0.5;
		int newNumberRows=(((double)image->getNumberRows()) *scaleFactor)+0.5;
	
		//Create object for scaled Image to be stored in
		scaledImage=new PPMImage(newNumberColumns, newNumberRows,image->getMaxRGB());

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
	
	
	//Vulnerability 6
	//When Tiling images, If only one image, reuse copy function to save code reuse, although this creates a shallow copy which is deleted, therefore deleting memory passed into tile function, which is also freed outside of tile
	if(amountImages==1)
	{
		PPMImage *firstPPM;
		firstPPM=images[0];
		copy(firstPPM,output);
		
		delete firstPPM;
	}
	else if(amountImages>1)
	{
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
		}

		fprintf(output,"%s",(value.str()).c_str());
	}
	
}

void newLine()
{
    cout << "\n";
}

