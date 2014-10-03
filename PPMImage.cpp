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
	
	strcpy(magicNumber,"P3");
	numberColumns=0;
	numberRows=0;
	pixels=NULL;
	maxRGB=0;
}

PPMImage::~PPMImage()
{
	
	
    for(int j=0;j<numberColumns;j++)
	{
		
		for(int i=0;i<numberRows;i++)
		{
            delete pixels[j][i];
            pixels[j][i]=NULL;
		}
        
        delete pixels[j];
        pixels[j]=NULL;
	}
    
    
	delete pixels;
	pixels=NULL;
	
	
}

PPMImage::PPMImage(int inNumberColumns,int inNumberRows,int inMaxRGB)
{
	
	strcpy(magicNumber,"P3");
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

PPMImage::PPMImage(int inNumberColumns,int inNumberRows,int inMaxRGB, Pixel ***inPixels)
{
	
	strcpy(magicNumber,"P3");
	numberColumns=inNumberColumns;
	numberRows=inNumberRows;
	maxRGB=inMaxRGB;
	pixels=inPixels;
	
}


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
	
	
		//Parse Through comments until at amount of rows and columns
		do
		{
			//read the current line from input image
			fgets(currentLine, C_LINELENGTH , inputFile);
			
			//if the currentline is a comment, copy to output file
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
			
			//Clear currentLine from memory, then allocate for next use
			for(int i=0;i<C_LINELENGTH;i++)
			{
				currentLine[i]='\0';
			}
			free(currentLine);
			currentLine=(char*)malloc(sizeof(char)*C_LINELENGTH);
			
			
		} while(isComment==true);
		
		
		//Allocate Memory for 2D array of pixels [rows][columns]
		//pixels = new Pixel**[numberColumns];
		//for(int j=0;j<numberColumns;j++)
		//{
		//	pixels[j]=new Pixel*[numberRows];
		//	
		//}

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
				
				//delete pixel from memory
				delete(currentPixel);
			
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

Pixel*** PPMImage::getPixels()
{
	return pixels;
}

Pixel* PPMImage::getPixel(int column, int row)
{
	return pixels[column][row];
}

void PPMImage::setPixel(Pixel* pixel, int column, int row)
{
	pixels[column][row] = pixel;
}



