# Nom de l'exécutable
TARGET = hash_resolver

# Compilation
CC = gcc
CFLAGS = -Wall -Wextra -g `pkg-config --cflags gtk+-3.0`
LDFLAGS = `pkg-config --libs gtk+-3.0` -lssl -lcrypto  # Ajout des bibliothèques OpenSSL

# Fichiers sources et objets
SRCS = backend.c interfaceg.c
OBJS = $(SRCS:.c=.o)

# Compilation principale et exécution
all: $(TARGET)
	@echo "Compilation réussie. Exécution du programme..."
	@./$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compilation des fichiers objets
%.o: %.c functions.h
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers compilés
clean:
	rm -f $(OBJS) $(TARGET)

# Nettoyage complet
mrproper: clean
	rm -f *~

