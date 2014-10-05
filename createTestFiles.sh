#!/bin/bash 
for i in {1..1000} 
do 
echo "P3 
# %$i\$s 
1 1 
255
1 2 3" > test.ppm 
./main copy test.ppm out/test-$i.ppm  
done
