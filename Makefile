# this is a terrible makefile but it is good enough for now

all: main

main: main.o out/loadcsv.o
	cc -Wall -o main out/main.o out/loadcsv.o

out/main.o: main.c
	cc -c main.c

out/loadcsv.o: fileio/loadcsv.c
	cc -c -o out/loadcsv.o fileio/loadcsv.c