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
	
	string instruction,image,output;
    
    //Handle command line parameters
    //First argument is instruction
    //Last argument is output folder
    //A secondary argument may be associated with instruction e.g flip h
    //Middle arguments are input files
	if(argc==4)
	{
		instruction = argv[1];
		image = argv[2];
		output = argv[argc-1];
	}
	else
	{
		cout << "3 Input parameters are needed\n";
		return 0;
	}
    
    //Test Command Arguements
	cout << "Arg 1 = " <<instruction << "\n";
	cout << "Arg 2 = " <<image << "\n";
	cout << "Arg 3 = " <<output << "\n";
    
    //	Your program should perform the following operations
	//copy
	if(instruction=="copy")
	{
		copy(image, output);
        
	}
    
    //flip
	else if(instruction =="flip")
	{
		flip();
        
	}
    
    //resize
	else if(instruction == "resize")
	{
		resize();
	}
    
    //tile
	else if(instruction == "tile")
	{
		tile();
	}
	
	
	return 0;
	
}

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

void copy(string image, string output)
{
    cout << "Copy Function\n";
    
    FILE *inputFile;
    FILE *outputFile;
    Pixel *currentPixel;
    int inRed,inGreen,inBlue;
    int amountRows,amountColumns;
    int maxRGB;
    char *magicNumber;
    char *currentLine;
    int i=0;
    
    magicNumber=(char*)malloc(sizeof(char)*5);
    currentLine=(char*)malloc(sizeof(char)*70);
    
    //Open Files
    inputFile = fopen(image.c_str(), "r");
    outputFile = fopen(output.c_str(),"w");

    fscanf(inputFile ,"%s\n",magicNumber);
    fscanf(inputFile ,"%d %d\n",&amountRows,&amountColumns);
    fscanf(inputFile ,"%d\n",&maxRGB);
    
    fprintf(outputFile,"%s\n",magicNumber);
    fprintf(outputFile ,"%d %d\n",amountRows,amountColumns);
    fprintf(outputFile ,"%d\n",maxRGB);
    
    while(!feof(inputFile))
    {
        fgets(currentLine, 1024, inputFile);
        //fscanf(inputFile, "%s\n",currentLine);
        fprintf(outputFile, "%s",currentLine);
    
        for(i=0;i<70;i++)
        {
            currentLine[i]='\0';
        }
        free(currentLine);
        magicNumber=(char*)malloc(sizeof(char)*70);
    
    }
    
    //fscanf(inputFile , " %d %d %d",inRed,inGreen,inBlue);
    //currentPixel= new Pixel(inRed,inGreen,inBlue);
    //fprintf(outputFile, "%s",currentPixel->toString());
    
    
    
    
    //Close Files
    fclose(inputFile);
    fclose(outputFile);
}

void flip()
{
	cout << "Flip function\n";
}

void resize()
{
	cout << "Resize function\n";
}

void tile()
{
	cout << "Tile function\n";
}

void newLine()
{
    cout << "\n";
}

