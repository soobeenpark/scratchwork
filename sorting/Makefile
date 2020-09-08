CC=g++
CFLAGS=-Wall -g

src = sort.cpp

sort: sort.o
	g++ sort.o -o sort $(CFLAGS)

sort.o: $(src)
	g++ -g -c $(src) -o sort.o

clean:
	rm -f sort.o sort
