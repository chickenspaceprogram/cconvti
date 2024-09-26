# this is a terrible makefile but it is good enough for now
.PHONY: all clean test

# main program compilation
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

out/hashmap.o: token-tools/hashmap.c
	cc -Wall -c -o out/hashmap.o token-tools/hashmap.c

out:
	mkdir out

# tests
test: out out/tests.o out/hashmap-tests.o out/hashmap.o
	cc -Wall -o test out/tests.o out/hashmap-tests.o out/hashmap.o
	./test

out/tests.o: tests.c
	cc -Wall -c -o out/tests.o tests.c

out/hashmap-tests.o: token-tools/tests/hashmap-tests.c
	cc -Wall -c -o out/hashmap-tests.o token-tools/tests/hashmap-tests.c

# clean
clean:
	rm -rf out
	rm -f main
	rm -f flex-csv-parser/csv-parser.c
	rm -f test