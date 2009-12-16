#! /bin/bash

sparse -werror -I ../inc ../inc/*.h ../src/*.c ../lib/*.c || exit 77
