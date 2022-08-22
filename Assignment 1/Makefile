# Define C compiler & flags

CC = gcc 
CFLAGS = -Wall -g

# Sets of source files and object files
SRC = dict1.c dict1_ops.c general.c 
OBJ = $(SRC:.c = .o)

# Stage 1
dict1: dict1.o dict1_ops.o general.o
	gcc $(CFLAGS) -o dict1 dict1.o dict1_ops.o general.o 

# Specify on how to get the .o files 
dict1.o: dict1.c 
	gcc -c dict1.c

dict1_ops.o: dict1_ops.c 
	gcc -c dict1_ops.c 

# Stage 2:
dict2: dict2.o dict2_ops.o general.o
	gcc $(CFLAGS) -ggdb -o dict2 dict2.o dict2_ops.o general.o

dict2.o: dict2.c 
	gcc -c dict2.c 

dict2_ops.o: dict2_ops.c 
	gcc -c dict2_ops.c 

# general for dict1 and dict2
general.o: general.c 
	gcc -c general.c 
clean:
	rm -f *.o dict1 dict2