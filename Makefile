# this is a terrible makefile but it is good enough for now
.phony: all clean

all: main

main: out/main.o out/loadcsv.o
	cc -Wall -o main out/main.o out/loadcsv.o

out/main.o: out main.c
	cc -c -o out/main.o main.c

out/loadcsv.o: out fileio/loadcsv.c
	cc -c -o out/loadcsv.o fileio/loadcsv.c

out/csv_parser.o: out/csv_parser.c:
	cc -c -o out/csv_parser.o out/csv_parser.c

out/csv_parser.c: out flex_csv_parser/csv_parser.l
	flex -o out/csv_parser.c flex_csv_parser/csv_parser.l

clean:
	rm -rf out
	rm main

out:
	mkdir out