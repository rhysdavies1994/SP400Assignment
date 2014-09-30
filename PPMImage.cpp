//
//  PPMImage.cpp
//
//
//  Created by Rhys Jordan Davies on 27/09/2014.
//
//
#define C_LINELENGTH 70
#include "PPMImage.h"

PPMImage::PPMImage()
{
	magicNumber=(char*)malloc(sizeof(char)*5);
	strcpy(magicNumber,"P3");
	comments=NULL;
	amountRows=0;
	amountColumns=0;
	pixels=NULL;
	maxRGB=0;
}

PPMImage::PPMImage(int inAmountRows,int inAmountColumns,int inMaxRGB, Pixel ***inPixels)
{
	magicNumber=(char*)malloc(sizeof(char)*5);
	strcpy(magicNumber,"P3");
	amountRows=inAmountRows;
	amountColumns=inAmountColumns;
	maxRGB=inMaxRGB;
	pixels=inPixels;
	
}

// TO DO
//CONVERT THIS "COPY" FUNCTION CODE INTO A WORKING FUNCTION
//TO MAKE A PPM CLASS FROM A FILE
void PPMImage::initFromFile(string inputFileName)
{
	FILE *inputFile;
	
    Pixel *currentPixel;
    int inRed,inGreen,inBlue;
	
	int currentRow =0;
	int currentColumn =0;
	
    char *currentLine;
	bool isComment=true;
	
	int progress=0;
    
    
    currentLine=(char*)malloc(sizeof(char)*C_LINELENGTH);
	

	
    //Open Files
    inputFile = fopen(inputFileName.c_str(), "r");
	
	//Get Magic Number, make sure its P3
    fscanf(inputFile ,"%s\n",magicNumber);
	
	if(strcmp(magicNumber,"P3")==0)
	{
		//Parse Through comments until at amount of rows and columns
		do
		{
			//read the current line from input image
			fgets(currentLine, C_LINELENGTH , inputFile);
			
			//if the currentline is a comment, copy to output file
			if(currentLine[0] == '#')
			{
				//fprintf(outputFile,"%s",currentLine);
			}
			//otherwise the current line is the amount of rows and columns
			else
			{
				sscanf(currentLine ,"%d %d",&amountRows,&amountColumns);
				
				isComment=false;
			}
			
			//Clear currentLine from memory, then allocate for next use
			for(int i=0;i<C_LINELENGTH;i++)
			{
				currentLine[i]='\0';
			}
			free(currentLine);
			currentLine=(char*)malloc(sizeof(char)*C_LINELENGTH);
			
			
		} while(isComment==true);
		
		
		//Allocate Memory for 2D array of pixels [rows][columns]
		pixels = new Pixel**[amountRows];
		for(int j=0;j<amountRows;j++)
		{
			pixels[j]=new Pixel*[amountColumns];
			
		}
		
		//Find maxRGB value from inputFile
		fscanf(inputFile ,"%d\n",&maxRGB);
			
		
		//Read end of input file, write to output file
		while(!feof(inputFile))
		{

				//DEBUGGING: print current word and line
				//printf("currentword:%s\n",currentWord);
				//printf("Curr Row:%d, Col:%d\n",currentRow,currentColumn);
				
				int red=0;
				int green=0;
				int blue=0;

				fscanf(inputFile," %d %d %d ",&red,&green,&blue);

				//Create new pixel
				currentPixel=new Pixel();
				
				//Set up current pixel RGB Values
				currentPixel->setRed(red);
				currentPixel->setGreen(green);				
				currentPixel->setBlue(blue);
				
				
				//Use current pixel
				pixels[currentRow][currentColumn]=new Pixel(currentPixel->getRed(), currentPixel->getGreen(), currentPixel->getBlue());
							
				//increment rows/columns
				if(currentColumn<amountColumns-1)
				{
					currentColumn++;
				}
				else
				{
					currentColumn=0;
					currentRow++;
					
				}
				
				//delete pixel from memory
				delete(currentPixel);
			
		}
	}
	else
	{
		printf("This is not a PPM File");
	}
	
	free(currentLine);
	currentLine=NULL;
    
    //Close Files
    fclose(inputFile);
	
}

string PPMImage::toString()
{
	stringstream value;
	
	value << magicNumber <<"\n";
	value << amountRows << " " <<amountColumns << "\n";
	value << maxRGB <<"\n";
	
	for(int i=0;i<amountRows;i++)
	{
		
		for(int j=0;j<amountColumns;j++)
		{
			value << (pixels[i][j]->toString()).c_str() <<"\n";
		}
	}
	
	return value.str();
}

string PPMImage::pixelsToString()
{
	stringstream value;
	
	for(int i=0;i<amountRows;i++)
	{
		
		for(int j=0;j<amountColumns;j++)
		{
			value << (pixels[i][j]->toString()).c_str() <<"\n";
		}
	}
	
	return value.str();
}

char* PPMImage::getMagicNumber()
{
	return magicNumber;
}

char* PPMImage::getComments()
{
	return comments;
}

int PPMImage::getAmountRows()
{
	return amountRows;
}

int PPMImage::getAmountColumns()
{
	return amountColumns;
}

int PPMImage::getMaxRGB()
{
	return maxRGB;
}

Pixel*** PPMImage::getPixels()
{
	return pixels;
}

Pixel* PPMImage::getPixel(int row, int column)
{
	return pixels[row][column];
}

PPMImage::~PPMImage()
{
	free(magicNumber);
	magicNumber=NULL;
	
	free(comments);
	comments=NULL;
	
	delete(pixels);
	pixels=NULL;
	
	
}
