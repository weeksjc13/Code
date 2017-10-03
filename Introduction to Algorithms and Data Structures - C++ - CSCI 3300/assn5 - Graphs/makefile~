CFLAGS = -g -Wall -O 
CC     = g++
LINK   = g++

graph: graph.o pqueue.o
	$(LINK) -o graph graph.o pqueue.o

graph.o: graph.cpp pqueue.h
	$(CC) $(CFLAGS) -c graph.cpp

pqueue.o: pqueue.cpp pqueue.h
	$(CC) $(CFLAGS) -c pqueue.cpp

clean: 
	rm graph graph.o pqueue.o trace.o
