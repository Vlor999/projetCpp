CC=g++
CFLAGS=-Wall -Wextra -std=c++17
SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:.cpp=.o)
EXEC=bin/systemeGestionVentes

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(EXEC)
