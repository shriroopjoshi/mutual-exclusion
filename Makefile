CC = g++

CFLAGS = -Wall -g -std=c++11
LDFLAGS = -pthread

SRC = *.cpp
OBJ = $(SRC:.c=.o)
BIN = mutex

RM = rm -f

.PHONY: all clean

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ) $(LDFLAGS)

clean: 
	$(RM) *.o $(BIN)

