# this is a terrible makefile but it is good enough for now
.phony: all clean

all: main

main: out out/main.o out/loadcsv.o
	cc -Wall -o main out/main.o out/loadcsv.o

out/main.o: main.c
	cc -c -o out/main.o main.c

out/loadcsv.o: fileio/loadcsv.c
	cc -c -o out/loadcsv.o fileio/loadcsv.c

clean:
	rm -rf out
	rm main

out:
	mkdir out