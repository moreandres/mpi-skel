#! /bin/bash

for file in `find .. -name "*.[ch]"`; do
    checkpatch.pl --no-tree --terse --strict --file $file | grep ERROR
    [ $? -gt 0 ] || exit 1 
done
