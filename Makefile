#CC = g++
CC = icpc

CFLAGS = -Wall -g -std=c++11
LDFLAGS = -pthread

SRC = $(shell ls *.cpp)
OBJ = $(SRC:.c=.o)
BIN = mutex

RM = rm -f

.PHONY: all clean clear

all: clean build

build: $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ) $(LDFLAGS)

clean: 
	$(RM) *.o $(BIN)

clear:
	$(RM) *.csv
