CC = clang
CFLAGS = -I. -Wall -Wextra -Wshadow -Werror -std=c99 -pedantic -g -ggdb
#CFLAGS += -DDEBUG=1

linkedlist:
	$(CC) -o linkedlist.bin LinkedList.c linkedlisttest.c $(CFLAGS)

queue:
	$(CC) -o queue.bin LinkedList.c Queue.c queuetest.c $(CFLAGS)

stack:
	$(CC) -o stack.bin LinkedList.c Stack.c stacktest.c $(CFLAGS)

unboundedarray:
	$(CC) -o unboundedarray.bin UnboundedArray.c unboundedarraytest.c $(CFLAGS)

hashdictionary:
	$(CC) -o hashdictionary.bin HashDictionary.c hashdictionarytest.c $(CFLAGS)

hashset:
	$(CC) -o hashset.bin HashSet.c hashsettest.c $(CFLAGS)

binarysearchtree:
	$(CC) -o binarysearchtree.bin BinarySearchTree.c binarysearchtreetest.c $(CFLAGS)

avltree:
	$(CC) -o avltree.bin AVLTree.c avltreetest.c $(CFLAGS)

format:
	clang-format -style=file -i *.c *.h

clean:
	rm -rf *.bin
