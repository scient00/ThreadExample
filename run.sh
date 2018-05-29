#!/bin/sh

mkdir -f run
make -f Makefile clean
make -f Makefile
./run/threadExample 
