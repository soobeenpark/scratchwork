CC=gcc
CFLAGS=-I. -Wall -g

linkedlist:
	$(CC) -o linkedlist.bin LinkedList.c linkedlisttest.c $(CFLAGS)

queue:
	$(CC) -o queue.bin LinkedList.c Queue.c queuetest.c $(CFLAGS)

stack:
	$(CC) -o stack.bin LinkedList.c Stack.c stacktest.c $(CFLAGS)

unboundedarray:
	$(CC) -o unboundedarray.bin UnboundedArray.c unboundedarraytest.c $(CFLAGS)

clean:
	rm -rf *.bin
