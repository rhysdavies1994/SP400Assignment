#include <stdio.h>
main=main
CFLAGS=g++ -pedantic -Wall -g
obj=$(main).o pixel.o
cc=g++ -c -g

$(main):    $(obj)
	$(CFLAGS) -o $(main) $(obj)

$(main).o: pixel.o
	$(cc) $(main).cpp

pixel.o:
	$(cc) pixel.cpp

clean:
	rm -rf $(obj) $(main)
