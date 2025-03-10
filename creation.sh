#!/bin/bash

# Liste des projets à creer
listElem=(
    "systemeEnregistrementBancaire"
    "systemeGestiondeLibrairie"
    "systemeReservationBus"
    "systemeGestionPaie"
    "systemeGestionduRepertoireTelephonique"
    "systemeReservationFerroviaire"
    "systemeGestionVentes"
    "systemeGestiondeBaseDonneesetudiants"
    "systemeBulletinScolaire"
    "systemeFacturationdeSupermarche"
    "systemeAnnuaireTelephonique"
)

# Creation de chaque projet avec sa structure
for elem in "${listElem[@]}"; do
    if [ -d "$elem" ]; then
        echo "Le repertoire '$elem' existe dejà, passage au suivant..."
    else
        echo "Creation du projet : $elem"
        mkdir -p "$elem"/{bin,src,include,data}

        # Creation du Makefile avec support pour `make run`
        cat <<EOF > "$elem/Makefile"
CC=g++
CFLAGS=-Wall -Wextra -std=c++17
SRC=\$(wildcard src/*.cpp)
OBJ=\$(SRC:.cpp=.o)
EXEC=bin/$elem
INCLUDE=include/

all: bin \$(EXEC)

bin:
	mkdir -p bin

\$(EXEC): \$(OBJ)
	\$(CC) \$(CFLAGS) \$(OBJ) -o \$(EXEC)

bin/%.o: src/%.cpp \$(INCLUDE)/*.hpp
	\$(CC) \$(CFLAGS) -I\$(INCLUDE) -c \$< -o \$@

run: all
	@if [ -f \$(EXEC) ]; then \\
		echo "Exécution de \$(EXEC)..."; \\
		\$(EXEC); \
	else \\
		echo "Erreur : l'exécutable \$(EXEC) n'existe pas. Compilez avec 'make'."; \\
	fi

clean:
	rm -f bin/*.o \$(EXEC)

EOF

        # Creation du README
        cat <<EOF > "$elem/README.md"
# Projet : $elem

## Structure du projet
- **bin/** : Contient les fichiers executables.
- **src/** : Contient les fichiers sources (.cpp).
- **include/** : Contient les fichiers d'en-tête (.hpp).
- **Makefile** : Pour compiler et executer le projet.

## Compilation
Utilisez la commande suivante pour compiler le projet :
\`\`\`sh
make
\`\`\`

## Execution
L'executable est situe dans **bin/** et peut être lance avec :
\`\`\`sh
make run
\`\`\`

## Nettoyage
Pour supprimer les fichiers objets et l'executable :
\`\`\`sh
make clean
\`\`\`
EOF
        cat <<EOF > "$elem/src/main.cpp"
#include <iostream>
int main() {
    std::cout << "Hello, World!" << std::endl;
    return EXIT_SUCCESS;
}
EOF

        # Creation d'un .gitignore (au niveau global)
        echo -e "bin/\n*.o" > "$elem/.gitignore"

        echo "Projet '$elem' initialise avec succes."
    fi
done

echo "Tous les projets ont ete crees avec succes."
