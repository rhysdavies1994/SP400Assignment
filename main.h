//
//  Header.h
//  
//
//  Created by Rhys J Davies on 26/09/2014.
//
//

#ifndef _Main_h
#define _Main_h
//Namespaces
using namespace std;
#include "PPMImage.h"

int main(int argc,char **argv);

void copy(PPMImage *image, FILE *output);
void flip(const char *direction, PPMImage *image, FILE *output);
void resize(double scaleFactor, PPMImage *image, FILE *output);
void tile(int numberImages,PPMImage **images, FILE *output);
void newLine();

#endif
