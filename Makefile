# this is a terrible makefile but it is good enough for now
.PHONY: all clean

all: main

main: out/main.o out/csv-parser.o out/num-parsing.o
	cc -Wall -ll -o main out/main.o out/csv-parser.o out/num-parsing.o

out/main.o: out main.c
	cc -Wall -c -o out/main.o main.c

out/csv-parser.o: flex-csv-parser/csv-parser.c
	cc -Wall -c -o out/csv-parser.o flex-csv-parser/csv-parser.c

out/num-parsing.o: flex-csv-parser/num-parsing.c
	cc -Wall -c -o out/num-parsing.o flex-csv-parser/num-parsing.c

flex-csv-parser/csv-parser.c: flex-csv-parser/csv-parser.l
	flex -o flex-csv-parser/csv-parser.c flex-csv-parser/csv-parser.l

clean:
	rm -rf out
	rm -f main
	rm -f flex-csv-parser/csv-parser.c

out:
	mkdir out