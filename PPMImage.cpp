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
	strcpy(magicNumber,"");
	strcpy(comments,"");
	sourceFileName="";
	numberColumns=0;
	numberRows=0;
	pixels=NULL;
	maxRGB=0;
}

/**************************************************************************
Function: 		(destructor)~PPMImage
Imports:		none
Exports:		none
Description:	Frees all memory associated with the PPMImage

**************************************************************************/
PPMImage::~PPMImage()
{
    for(int j=0;j<numberColumns;j++)
	{	
	
		for(int i=0;i<numberRows;i++)
		{
			delete pixels[j][i];
			pixels[j][i]=NULL;
		}
        
        delete[] pixels[j];
        pixels[j]=NULL;
	}
    

	delete[] pixels;
	pixels=NULL;
	
	//	4a - without this, memory leak
	//	free(sourceFileName);
	
}

PPMImage::PPMImage(int inNumberColumns,int inNumberRows,int inMaxRGB)
{
	
	strcpy(magicNumber,"P3");
	strcpy(comments,"");
	numberColumns=inNumberColumns;
	numberRows=inNumberRows;

	pixels = new Pixel**[numberColumns];
	
	for(int j=0;j<numberColumns;j++)
	{
		pixels[j]=new Pixel*[numberRows];
		
		for(int i=0;i<numberRows;i++)
		{
			pixels[j][i]=new Pixel();
		}
	}
	maxRGB=inMaxRGB;

}



void PPMImage::initFromFile(string inputFileName)
{
	FILE *inputFile;
	
	sourceFileName = inputFileName;
	
    Pixel *currentPixel;
    int inRed,inGreen,inBlue;
	
	int currentRow =0;
	int currentColumn =0;
	
    char *currentLine;
	bool isComment=true;
	
	int progress=0;
    

	
    //Open Files
    inputFile = fopen(inputFileName.c_str(), "r");
	
	//Vulerability 1a
	//If magicNumber is greater than 10, it will write over fixed size of 10
	//Get Magic Number, make sure its P3
    fscanf(inputFile ,"%s\n",magicNumber);
	
	
		//Parse Through comments until at amount of rows and columns
		do
		{
			//Vulnerability 2b
			//if a line is over 70 characters when reading in, heap will overflow
			currentLine=(char*)malloc(sizeof(char)*C_LINELENGTH);
		
			//read the current line from input image
			fgets(currentLine, C_LINELENGTH , inputFile);
			
			//if the currentline is a comment, copy to output file
			//comments have to be between magicnumber and amount rows&columns
			if(currentLine[0] == '#')
			{
				strcat(comments,currentLine);
			}
			//otherwise the current line is the amount of rows and columns
			else
			{
				sscanf(currentLine ,"%d %d",&numberColumns,&numberRows);
				
				isComment=false;
			}
			
			free(currentLine);
			currentLine=NULL;
			
			
			
		} while(isComment==true);
		
		
		//Allocate Memory for 2D array of pixels [rows][columns]
		pixels = new Pixel**[numberColumns];
		for(int j=0;j<numberColumns;j++)
		{
			pixels[j]=new Pixel*[numberRows];
			
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
				pixels[currentColumn][currentRow]=new Pixel(currentPixel->getRed(), currentPixel->getGreen(), currentPixel->getBlue());
							
				//increment rows/columns
				if(currentColumn<numberColumns-1)
				{
					currentColumn++;
				}
				else
				{
					currentColumn=0;
					currentRow++;
					
				}
				
				//4b - without this code below, memory leak
				//When reading through input file, forget to delete current pixel
				//delete pixel from memory
				//delete(currentPixel);
			
		}
	
    
    //Close Files
    fclose(inputFile);
	
}

string PPMImage::toString()
{
	stringstream value;
	
	value << magicNumber <<"\n";
    value << comments <<"\n";
	value << numberColumns << " " <<numberRows << "\n";
	value << maxRGB <<"\n";
	for(int y=0;y<numberRows;y++)
		{
		for(int x=0;x<numberColumns;x++)
		{		
			value << (pixels[x][y]->toString()).c_str() <<"\n";
		}
	}
	
	return value.str();
}

string PPMImage::pixelsToString()
{
	stringstream value;
	for(int y=0;y<numberRows;y++)
		{
		for(int x=0;x<numberColumns;x++)
		{		
			value << (pixels[x][y]->toString()).c_str() <<"\n";
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

int PPMImage::getNumberColumns()
{
	return numberColumns;
}

int PPMImage::getNumberRows()
{
	return numberRows;
}

int PPMImage::getMaxRGB()
{
	return maxRGB;
}

string PPMImage::getSourceFileName()
{
	return sourceFileName;
}

Pixel*** PPMImage::getPixels()
{
	return pixels;
}

Pixel* PPMImage::getPixel(int column, int row)
{
	return pixels[column][row];
}

void PPMImage::setPixel(int inRed, int inGreen, int inBlue, int column, int row)
{
	pixels[column][row]->setRed(inRed);
	pixels[column][row]->setGreen(inGreen);
	pixels[column][row]->setBlue(inBlue);
}



