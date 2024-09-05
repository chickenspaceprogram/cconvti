# this is a terrible makefile but it is good enough for now
.phony: all clean

all: main

main: out/main.o out/csv_parser.o
	cc -Wall -ll -o main out/main.o out/csv_parser.o

out/main.o: out main.c
	cc -Wall -c -o out/main.o main.c

out/csv_parser.o: flex_csv_parser/csv_parser.c
	cc -Wall -ll -c -o out/csv_parser.o flex_csv_parser/csv_parser.c

flex_csv_parser/csv_parser.c: flex_csv_parser/csv_parser.l
	flex -o flex_csv_parser/csv_parser.c flex_csv_parser/csv_parser.l

clean:
	rm -rf out
	rm -f main
	rm -f flex_csv_parser/csv_parser.c

out:
	mkdir out