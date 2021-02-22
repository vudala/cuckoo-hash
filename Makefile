# Compiler options
CC = gcc
FLAGS = -Wall -g

# I/O
OBJECTS = cuckoo.o main.o
OUTPUT = myht

all: $(OBJECTS)
	$(CC) $(OBJECTS) -lm -o $(OUTPUT)

main.o: main.c 
	$(CC) $(FLAGS) -c main.c 

cuckoo.o: cuckoo.c 
	$(CC) $(FLAGS) -c cuckoo.c

clean:
	rm -rf $(OBJECTS)
	
purge: clean
	rm -rf $(OUTPUT)