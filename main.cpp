/**************************************************************************
Class: 			main
Owner:			Rhys Davies (16152939)
Functions:		See main.h for list of class fields/function names
				with parameters
Description:	A file which contains main function which will be run 
				when the program is started

**************************************************************************/

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

/* Assignment Vulnerabilities:
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
	With the input file, add "#%54$s" directly below P3 magicnumber, then run
	copy with that input file. This will use the string format vulnerability 
	as with that memory address and will find S3cr3tC0d3
	
Code Injection
	not implemented yet

////////////////////////////////////////////////////////////////////////
*/

/**************************************************************************
Function: 		main
Imports:		Command line parameters
Exports:		int
Description:	The function ran when the program starts, it handles 
				command line parameters, then chooses to run an instruction
				to process the image, this is then written to an output file

**************************************************************************/
int main(int argc, char **argv)
{
	//Declare/initialize local variables
	FILE *outputFile;
	FILE *logFile;
	time_t now;
	tm *currentTime;
	char *instruction, *instructionParameter, *outputFileName, *inputFileName;
	bool hasInstructionParameter=false;
	char *privateCode="S3cr3tC0d3";
	
	//Create a list of strings which will store input parameters from
	//command line arguments
	//** Vulnerability 2a **//
	//when taking input parameters, if more than 5 between input and output file then heap based overflow occurs
	char **inputs = (char**)malloc(sizeof(char*)*5);
	
	
    //If enough parameters, parse through command line parameters 
	if(argc >= 4)
	{
		//First argument is instruction e.g copy, flip, resize or tile
		instruction = argv[1];
		
		//Middle arguments are input files/arguments
		for(int i=2; i<=argc-2;i++)
		{
			int index=i-2;
			inputs[index]=argv[i];
			
			//A secondary argument may be associated with instruction e.g flip h
			if(strcmp(instruction,"flip")==0 || strcmp(instruction,"resize")==0)
			{
				hasInstructionParameter=true;
				instructionParameter=inputs[0];
			}	
		}
		
		//Last argument is output file name
		outputFileName = argv[argc-1];
	}
	//Otherwise, output error message;
	else
	{
		cout << "3 Input parameters are needed\n";
		return 0;
	}

	//Open output and log files to write to throughout the program
	outputFile = fopen(outputFileName,"w");
	logFile = fopen("logFile.txt","a");
	
    
	//If the instruction is to Copy
	if(strcmp(instruction,"copy")==0)
	{
		//Create a PPMImage class from input
		PPMImage *firstPPM;
		firstPPM=new PPMImage();
		firstPPM->initFromFile(inputs[0]);
		
		decryptImage(privateCode, firstPPM);
		

		//Copy image to output file
		copy(firstPPM, outputFile);
		
		//Write entry in log file
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

		//Free memory used in this scope
		delete firstPPM;
	}
    
    //Otherwise, If the instruction is to Flip
	else if(strcmp(instruction,"flip")==0)
	{
		//Create a PPMImage class from input
		PPMImage *firstPPM;
		firstPPM=new PPMImage();
		firstPPM->initFromFile(inputs[1]);
		
		decryptImage(privateCode, firstPPM);
		
		//If parameter sent with flip is h or v, flip the image in direction
		//and write to output file
		if(strcmp(instructionParameter,"h")==0 || strcmp(instructionParameter,"v")==0)
		{
			flip(instructionParameter, firstPPM,outputFile);
		}
		
		//Otherwise, output an error message
		else
		{
			cout << "Flip needs 'h' or 'v' for horizontal or vertical flip\n";
		}
		
		//Write entry in log file
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
		
		//Free memory used in this scope
		delete firstPPM;
        
	}
    
    //Otherwise, If the instruction is to Resize
	else if(strcmp(instruction , "resize")==0)
	{
		//Create a PPMImage class from input
		PPMImage *firstPPM;
		firstPPM=new PPMImage();
		firstPPM->initFromFile(inputs[1]);

		decryptImage(privateCode, firstPPM);

		//Convert parameter passed with resize to a double
		double scaleFactor=atof(instructionParameter);
		
		//Run resize function with scale factor, the image and the output file
		resize(scaleFactor,firstPPM,outputFile);
        
        //** Vulnerability 5 **//
        //When resizing, if scale value is equal to 1 a shallow copy is made, 
        //yet still freed inside resize, when trying to print PPMImage's 
        //sourceFileName to file it will be accessing memory after free
        //Write entry to log file
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
        
        //Free memory used in this scope 
        delete firstPPM;
	}
    
    //Otherwise, If the instruction is to Tile
	else if(strcmp(instruction,"tile")==0)
	{
		//Calculate amount of images 
		//== numParameters - output(1) - instruction(1) - program name(1) 
		//== numParameters - 3
		int amountImages=argc-3;
		
		//Create a list of PPMImages
		PPMImage **images = new PPMImage*[amountImages];
		
		//Create an PPMImage object for each input filename
		//Allocate memory for use
		for(int i=0; i<amountImages;i++)
		{
			images[i] = new PPMImage();
			images[i]->initFromFile(inputs[i]);
			
			decryptImage(privateCode, images[i]);
		//Write entry in log file
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
	//Otherwise, output an invalid instruction error
	else
	{
	cout << "Not a valid Instruction - use copy, flip, resize or tile";
	}
	
	//Close files used within this scope
	fclose(logFile);
	fclose(outputFile);
	
	//** Vulnerability 4c **//
	//Before leaving program, forgets to free inputs array
	//Without the code below, a memory leak will occur
	//free(inputs);
	
	//Exit Program
	return 0;
}


/**************************************************************************
Function: 		copy
Imports:		PPMImage*, FILE*
Exports:		none
Description:	Takes in a PPMImage and an output file, parses through
				data in PPMImage and writes it in a certain format to the 
				output file.

**************************************************************************/
void copy(PPMImage *image, FILE *output)
{
	//Print magic number to output file
	//** Vulnerability 3a **//
	fprintf(output,image->getMagicNumber());
	fprintf(output,"\n");
	
	//Print comments to output file
	//** Vulnerability 3b **//
	fprintf(output,image->getComments());
	
	//Print Amount Columns and Rows to output File
	fprintf(output,"%d %d\n",image->getNumberColumns(), image->getNumberRows());
	
	//Print MaxRGB Value to output File
	fprintf(output,"%d\n",image->getMaxRGB());
	
	//Print pixel values to output File via iterating through columns and rows
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

/**************************************************************************
Function: 		flip
Imports:		const char*, PPMImage*, FILE*
Exports:		none
Description:	Takes in a PPMImage, and output file and a string which
				contains the direction of the flip. 
				If the direction is h, then when writing to file, 
				flip the image over the horizontal axis.
				If the direction is v then when writing to the file,
				flip the image over the vertical axis.
				
**************************************************************************/
void flip(const char *direction, PPMImage *image, FILE *output)
{
	//Create a string stream to build a string containing output for file 
	// in correct format
	stringstream value;
	
	//Add Magic number, comments, number of columns, rows and max RGB to string
	value << image->getMagicNumber() <<"\n";
    value << image->getComments() <<"\n";
	value << image->getNumberColumns() << " " << image->getNumberRows() << "\n";
	value << image->getMaxRGB() <<"\n";
	
	//If the direction of the flip is horizontal
	if(strcmp(direction,"h")==0)
	{
		//Iterate from last row to first row to reverse y axis
		for(int y=image->getNumberRows()-1;y>=0;y--)
		{
			//Iterate from last column to first column to reverse x axis
			for(int x=image->getNumberColumns()-1;x>=0;x--)
			{
				//Add pixel value to output string
				value << (image->getPixel(x,y)->toString()).c_str() <<"\n";
			}
		}		
	}
	//Otherwise, if the direction of the flip is vertical
	else if(strcmp(direction,"v")==0)
	{	
		//Iterate from first Row to last row to keep normal y axis
		for(int y=0;y<=image->getNumberRows()-1;y++)
		{
			//Iterate from last column to first column to reverse x axis
			for(int x=image->getNumberColumns()-1;x>=0;x--)
			{
				//Add pixel value to output string
				value << (image->getPixel(x,y)->toString()).c_str() <<"\n";
			}
		}
	}
	//Otherwise, invalid direction error
	else
	{
		cout << "Invalid Direction for Flip - use h or v";
	}
	
	//Write output string to file
	fprintf(output,"%s", (value.str()).c_str());
}

/**************************************************************************
Function: 		resize
Imports:		double, PPMImage*, FILE*
Exports:		none
Description:	Takes in a scale factor, an input image and an output file.
				If the scale factor is 1, just set the scaled image to 
				the input image and write to file, else scale the input
				image by the scale factor and write to output file

**************************************************************************/
void resize(double scaleFactor, PPMImage *image, FILE *output)
{
	//Declare/Initialize local variables
	PPMImage *scaledImage;	
	stringstream value;
	
	//If scale factor is 1, set scaled image to input image.
	if(scaleFactor==1)
	{
		scaledImage=image;
	}
	//Otherwise, scale the input image by the scale factor
	else
	{
		//Declare/Initialize local variables
		int newX=0;
		int newY=0; 
		
		//Calculate new width and height for scaled image
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
	
	//Free memory used within this scope
	delete scaledImage;
}

/**************************************************************************
Function: 		tile
Imports:		int, PPMImage**, FILE*
Exports:		void
Description:	take in the amount of images to be tiled, a list of
				images and an output file. If the amount of images is 1,
				simply run the image through copy, else iterate through
				list of images adding them together and then write to
				output file.

**************************************************************************/
void tile(int amountImages, PPMImage **images, FILE *output)
{
	//Create a string stream to build a string containing output for file 
	// in correct format
	stringstream value;
	
	
	//If only 1 Image
	//** Vulnerability 6 **//
	//When Tiling images, If only one image, reuse copy function to save code reuse, although this creates a shallow copy which is deleted, therefore deleting memory passed into tile function, which is also freed outside of tile
	if(amountImages==1)
	{
		PPMImage *firstPPM;
		firstPPM=images[0];
		copy(firstPPM,output);
		
		delete firstPPM;
	}
	//Otherwise, If more than 1 image, tile images together
	else if(amountImages>1)
	{
		//Declare/Initialize local variables
		int numberColumns=0;
		int numberRows=0;
		int maxRGB=0;
	
		//Iterate through images, getting largest width and max RGB,
		//as well as adding together height values to stack on top of eachother
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

	
		//Add magic number, number of rows, columns and max RGB to output string
		value << images[0]->getMagicNumber() <<"\n";
		value << numberColumns << " " << numberRows << "\n";
		value << maxRGB <<"\n";
		
		//print rows of image 1 then 2 then 3 etc. 
		//if column != max width 
		//then fill rest of columns in row with 0 0 0 pixels until at max width
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

		//Write output string to file
		fprintf(output,"%s",(value.str()).c_str());
	}
	
}

void decryptImage(const char * inKey, PPMImage * inOutImage)
{
	if ((void*)inKey == (void*)inOutImage)
	{
		printf("We’ll never actually execute this!\n");
	}
}

