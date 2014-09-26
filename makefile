#include <stdio.h>
main=main
CFLAGS=g++ -pedantic -Wall -g
obj=$(main).o
cc=g++ -c -g

$(main):    $(obj)
	$(CFLAGS) -o $(main) $(obj)

$(main).o:	$(main).cpp
	$(cc) $(main).cpp


clean:
	rm -rf $(obj) $(main)
