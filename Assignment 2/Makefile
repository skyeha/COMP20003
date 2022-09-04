# Define C compiler & flags

CC = gcc 
CFLAGS = -Wall -g

# Sets of source files and object files
# SRC = dict1.c dict1_ops.c general.c 
OBJ = $(SRC:.c = .o)

# Stage 1
dict3: dict3.o data.o
	gcc $(CFLAGS) -o dict3 dict3.o data.o  

# Specify on how to get the .o files 
dict3.o: dict3.c 
	gcc -c dict3.c

data.o: data.c 
	gcc -c data.c 

clean:
	rm -f *.o dict3 