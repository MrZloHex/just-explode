CC = gcc 
CFLAGS =  -s -O3 -Wall -Wextra -Werror -Wpedantic -std=c11 -Wstrict-aliasing
CFLAGS += -Wno-old-style-declaration -Wno-implicit-fallthrough
CFLAGS += -Ilib/glfw/include -Iinc -Ilib/glad/include

LDFLAGS = -lncurses 

TARGET = jsex 

SRC = src
OBJ = obj
BIN = bin

SOURCES = $(wildcard src/*.c)
OBJECTS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))


all: compile clean

compile: binary 
run: compile execute clean

binary: $(OBJECTS)
	-rm $(BIN)/$(TARGET)
	$(CC) -o $(BIN)/$(TARGET) $^ $(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

execute:
	./$(BIN)/$(TARGET)

clean:
	-rm $(OBJECTS)
