#! /bin/bash

for file in `find .. -name "*.[ch]"`; do 
    checkpatch.pl --no-tree --terse --strict --file $file; 
done
