/**************************************************************************
Class: 			PPMImage
Owner:			Rhys Davies (16152939)
Functions:		See PPMImage.h for list of class fields/function names
				with parameters
Description:	A Container Class for representing a RGBPixel, 
				this will be used inside of image classes to 
				build up the image.

**************************************************************************/

#define C_LINELENGTH 70
#include "PPMImage.h"

/**************************************************************************
Function: 		(constructor)PPMImage
Imports:		none
Exports:		none
Description:	Initializes all class fields to default values

**************************************************************************/
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
Description:	Called when a PPMImage is deleted,
				Frees all memory associated with the PPMImage

**************************************************************************/
PPMImage::~PPMImage()
{
	//Increment through Columns
    for(int j=0;j<numberColumns;j++)
	{	
		//Increment through rows
		for(int i=0;i<numberRows;i++)
		{
			//**Vulnerability 4a**//
			//Without code below - memory leak
			//Delete pixel object
			//delete pixels[j][i];
			//pixels[j][i]=NULL;
		}
		
		//Delete array of pixels
        delete[] pixels[j];
        pixels[j]=NULL;
	}
    
	//Delete array of array of pixels
	delete[] pixels;
	pixels=NULL;
	
	
	
}

/**************************************************************************
Function: 		(constructor)PPMImage
Imports:		int, int, int
Exports:		none
Description:	Takes input parameters for some class fields (numberRows,
				numberRows and Max RGB, then initialises the rest and 
				initializes pixel array

**************************************************************************/
PPMImage::PPMImage(int inNumberColumns,int inNumberRows,int inMaxRGB)
{
	//Initialise to default values
	strcpy(magicNumber,"P3");
	strcpy(comments,"");
	
	//Set values passed in
	numberColumns=inNumberColumns;
	numberRows=inNumberRows;
	maxRGB=inMaxRGB;
	
	//Initialise pixel array to defaults
	pixels = new Pixel**[numberColumns];
	for(int j=0;j<numberColumns;j++)
	{
		pixels[j]=new Pixel*[numberRows];
		
		for(int i=0;i<numberRows;i++)
		{
			pixels[j][i]=new Pixel();
		}
	}
	

}


/**************************************************************************
Function: 		initFromFile
Imports:		string
Exports:		none
Description:	Takes in the name of a file and attempts to build the
				object from information in the file, allocates memory
				where needed and deletes memory where used, this does not
				output to another file

**************************************************************************/
void PPMImage::initFromFile(string inputFileName)
{
	//Declare/Initalise variables
	FILE *inputFile;
    Pixel *currentPixel;
    int inRed,inGreen,inBlue;
	int currentRow =0;
	int currentColumn =0;
    char *currentLine;
	bool isComment=true;
	int progress=0;
   
   	//Set source file name from input parameter
	sourceFileName = inputFileName;
	
    //Open input file
    inputFile = fopen(inputFileName.c_str(), "r");
	
	//Get magic number from input file
	//** Vulnerability 1a **//
	//If magicNumber is greater than 10, it will write over fixed size of 10
    fscanf(inputFile ,"%s\n",magicNumber);
	
		//comments have to be between magic number and amount of rows and columns
		//Parse Through comments until at amount of rows and columns
		do
		{
			//Allocate memory for current line on the heap
			//** Vulnerability 2b **//
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
			
			//De-allocate current line
			free(currentLine);
			currentLine=NULL;
		
		} while(isComment==true);
		
		
		//Allocate Memory for 2D array of pixels [rows][columns]
		//Initialize values to default
		pixels = new Pixel**[numberColumns];
		for(int j=0;j<numberColumns;j++)
		{
			pixels[j]=new Pixel*[numberRows];
			
			for(int i=0;i<numberRows;i++)
			{
			pixels[j][i]=new Pixel();
			}
			
		}
		
		//Read maxRGB value from inputFile
		fscanf(inputFile ,"%d\n",&maxRGB);
				
		//Read until end of input file, write pixels to output file
		while(!feof(inputFile))
		{
			//Initialize local variables		
			int red=0;
			int green=0;
			int blue=0;

			//Read in red green and blue values for pixels from input file
			fscanf(inputFile," %d %d %d ",&red,&green,&blue);

			//Create new pixel
			currentPixel=new Pixel();
		
			//Set up current pixel RGB Values
			currentPixel->setRed(red);
			currentPixel->setGreen(green);				
			currentPixel->setBlue(blue);
				
			//Use current pixel values to make a deep copy of pixel
			//when initializing PPMImage
			pixels[currentColumn][currentRow]->setRGB(
								currentPixel->getRed(),
								currentPixel->getGreen(),
								currentPixel->getBlue());
					
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
		
			//** Vulnerability 4b **//
			// - without this code below, memory leak
			//When reading through input file, forget to delete current pixel
			//delete pixel from memory
			//delete(currentPixel);
		}
	
    //Close Files
    fclose(inputFile);
	
}

/**************************************************************************
Function: 		toString
Imports:		none
Exports:		string
Description:	Merges all class fields into one string for viewing data

**************************************************************************/
string PPMImage::toString()
{
	//Create string stream to build a string for returning
	stringstream value;
	
	//output magic number, comments, number of rows and columns, max RGB
	value << magicNumber <<"\n";
    value << comments <<"\n";
	value << numberColumns << " " <<numberRows << "\n";
	value << maxRGB <<"\n";
	
	//output each pixel stored in pixel array
	for(int y=0;y<numberRows;y++)
	{
		for(int x=0;x<numberColumns;x++)
		{		
			value << (pixels[x][y]->toString()).c_str() <<"\n";
		}
	}
	
	return value.str();
}

/**************************************************************************
Function: 		pixelsToString
Imports:		none
Exports:		string
Description:	Merges all of the pixel array to a string for viewing data

**************************************************************************/
string PPMImage::pixelsToString()
{
	//Create string stream to build a string for returning
	stringstream value;
	
	//output each pixel stored in pixel array
	for(int y=0;y<numberRows;y++)
	{
		for(int x=0;x<numberColumns;x++)
		{		
			value << (pixels[x][y]->toString()).c_str() <<"\n";
		}
	}
	
	return value.str();
}


/**************************************************************************
Function:		Getters
Imports:		none
Exports:		class field type
Description:	Each getter returns the class field for acces outside of
				the class

**************************************************************************/
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

/**************************************************************************
Function:		setPixel
Imports:		int,int,int,int,int
Exports:		none
Description:	takes in RGB values as well as a column and row, this then
				gets the pixel at this location and sets the RGB values

**************************************************************************/
void PPMImage::setPixel(int inRed, int inGreen, int inBlue, int column, int row)
{
	pixels[column][row]->setRed(inRed);
	pixels[column][row]->setGreen(inGreen);
	pixels[column][row]->setBlue(inBlue);
}



