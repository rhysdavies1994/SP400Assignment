#include <stdio.h>
main=
CFLAGS=gcc -ansi -pedantic -Wall -g
obj=$(main).o
cc=gcc -c -g

$(main):    $(obj)
	$(CFLAGS) -o $(main) $(obj)

$(main).o:	$(main).c	$(main).h
	$(cc) $(main).c

clean:
	rm -rf $(obj) $(main)
