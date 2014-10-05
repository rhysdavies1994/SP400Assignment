#include <stdio.h>
main=main
CFLAGS=g++ -pedantic -Wall -ggdb
obj=$(main).o pixel.o PPMImage.o
cc=g++ -c -ggdb

$(main):    $(obj)
	$(CFLAGS) -o CCSEPAssignment $(obj)

$(main).o: pixel.o PPMImage.o
	$(cc) $(main).cpp

pixel.o:
	$(cc) pixel.cpp
	
PPMImage.o:
	$(cc) PPMImage.cpp

clean:
	rm -rf $(obj) $(main)
