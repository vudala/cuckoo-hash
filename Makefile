# GRR20195689 Eduardo Vudala Senoski

CC = gcc
OBJECTS = cuckoo.o main.o
FLAGS = -Wall -g
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