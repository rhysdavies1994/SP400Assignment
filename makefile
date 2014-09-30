#include <stdio.h>
main=main
CFLAGS=g++ -pedantic -Wall -g
obj=$(main).o pixel.o PPMImage.o
cc=g++ -c -g

$(main):    $(obj)
	$(CFLAGS) -o $(main) $(obj)

$(main).o: pixel.o PPMImage.o
	$(cc) $(main).cpp

pixel.o:
	$(cc) pixel.cpp
	
PPMImage.o:
	$(cc) PPMImage.cpp

clean:
	rm -rf $(obj) $(main)
