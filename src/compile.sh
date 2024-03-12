#!/bin/bash


gcc -c Networking.c -o Networking.o
gcc -c StrManip.c -o StrManip.o
ar -rcs libNET.a *.o
rm *.o