EXEC = RBTree
CC = g++
CFLAGS = -c -Wall

$(EXEC)	:main.o util.o rbtree.o
	$(CC) -o $(EXEC) main.o util.o rbtree.o
	
main.o	:main.cpp main.h data_structures.h util.h rbtree.h
	$(CC) $(CFLAGS) main.cpp	
	
util.o	:util.cpp util.h data_structures.h
	$(CC) $(CFLAGS) util.cpp	

rbtree.o	:rbtree.cpp rbtree.h data_structures.h
	$(CC) $(CFLAGS) rbtree.cpp

clean	:
	rm *.o $(EXEC)
