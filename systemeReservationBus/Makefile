CC=g++
CFLAGS=-Wall -Wextra -std=c++17
SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:.cpp=.o)
EXEC=bin/systemeReservationBus

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	@if [ -f $(EXEC) ]; then \
		echo "Execution de $(EXEC)..."; \
		$(EXEC); \
	else \
		echo "Erreur : l'executable $(EXEC) n'existe pas. Compilez avec 'make'."; \
	fi

clean:
	rm -f src/*.o $(EXEC)
