# Define C compiler & flags

CC = gcc 
CFLAGS = -Wall -g

# Sets of source files and object files
# SRC = dict1.c dict1_ops.c general.c 
OBJ = $(SRC:.c = .o)

# Stage 1
dict3: dict3.o read.o
	gcc $(CFLAGS) -o dict3 dict3.o read.o 

dict3.o: dict3.c data.h read.h
	gcc -Wall -o dict3.o dict3.c -g -c

# Specify on how to get the .o files 
#data.o: data.c data.h
#	gcc -Wall -o data.o data.c -g -c

read.o: read.c read.h data.c data.h
	gcc -Wall -o read.o read.c -g -c

dict4: dict4.o read.o
	gcc $(CFLAGS) -o dict4 dict4.o read.o 

dict4.o: dict4.c data.h read.h
	gcc -Wall -o dict4.o dict4.c -g -c
clean:
	rm -f *.o dict3 