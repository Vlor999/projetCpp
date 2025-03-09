CC=g++
CFLAGS=-Wall -Wextra -std=c++17
SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:.cpp=.o)
EXEC=bin/systemeAnnuaireTelephonique
INCLUDE=include/

all: bin $(EXEC)

bin:
	mkdir -p bin

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

bin/%.o: src/%.cpp $(INCLUDE)/*.hpp
	$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

run: all
	@if [ -f $(EXEC) ]; then \
		echo "Exécution de $(EXEC)..."; \
		$(EXEC); 	else \
		echo "Erreur : l'exécutable $(EXEC) n'existe pas. Compilez avec 'make'."; \
	fi

clean:
	rm -f bin/*.o $(EXEC)

