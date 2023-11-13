CC=gcc -Iinclude/
CFLAGS=
LIBS=-lraylib -lm -lpthread -ldl -lX11
SRC=src/main.c
OBJ=$(SRC:.c=.o)
EXEC=main

all: dirs $(EXEC)

dirs:
	mkdir -p bin

$(EXEC): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o bin/$(EXEC) $(LIBS)

clean:
	rm -f $(OBJ) bin/$(EXEC)

.PHONY: all clean 
