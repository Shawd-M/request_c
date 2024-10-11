# Définir les cibles du makefile
EXE = webserver
SRC_DIR = src
INC_DIR = include

# Définir les options de compilation
CC = gcc
CFLAGS = -I$(INC_DIR) 
# -Wall -Wextra -Werror -std=c99

# Définir les fichiers source et d'en-tête du projet
SRC = $(wildcard $(SRC_DIR)/*.c) main.c
INC = $(wildcard $(INC_DIR)/*.h)
OBJ = $(SRC:.c=.o)

# $@Le nom de la cible
# $<Le nom de la première dépendance
# $^La liste des dépendances
# Définir les règles de compilation
all : $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(INC)
	$(CC) $(CFLAGS) -o $@ -c $<

# Définir les règles de nettoyage
.PHONY: clean re
re: clean all
clean:
	rm -f $(OBJ) $(EXE)
