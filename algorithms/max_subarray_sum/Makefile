CC=g++
CFLAGS=-Wall -g

src = max-subarray-sum.cpp

mss: mss.o
	g++ mss.o -o $@ $(CFLAGS)

mss.o: $(src)
	g++ -g -c $(src) -o mss.o

clean:
	rm -f mss.o mss
