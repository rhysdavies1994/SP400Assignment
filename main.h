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
#include <math.h>

int main(int argc,char **argv);

void copy(PPMImage *image, FILE *output);
void flip(const char *direction, PPMImage *image, FILE *output);
void resize(double scaleFactor, PPMImage *image, FILE *output);
void tile(int amountImages,PPMImage **images, FILE *output);
void decryptImage(const char * inKey, PPMImage * inOutImage);

#endif
