CC=g++
CFLAGS=-I.

%.o: %.cpp
	$(CC) -std=c++11 -c -o $@ $< $(CFLAGS)

scanner: main.o testScanner.o scanner.o
	$(CC) -std=c++11 -Wall -o scanner main.o testScanner.o scanner.o

winclean:
	del /Q /S *.o

linclean:
	rm -f scanner
	rm -f *.o

run:
	scanner input.fs19
