#!/bin/bash


gcc -c Networking.c -o Networking.o
ar -rcs libNET.a *.o
rm *.o