CC = clang 
CFLAGS =  -g -O0 -Wall -Wextra -Wpedantic -std=c11 -Wstrict-aliasing
CFLAGS += -Wno-pointer-arith -Wno-newline-eof -Wno-unused-parameter -Wno-gnu-statement-expression
CFLAGS += -Wno-gnu-compound-literal-initializer -Wno-gnu-zero-variadic-macro-arguments
CFLAGS += -Ilib/glfw/include -Iinc -Ilib/glad/include

LDFLAGS = -lncurses 

TARGET = atlanta 

SRC = src
OBJ = obj
BIN = bin

SOURCES  = $(wildcard src/**/*.c) $(wildcard src/*.c)
OBJECTS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))


all: compile clean

compile: binary 
run: compile execute clean

libs:
	cd lib/glad && $(CC) -o src/glad.o -Iinclude -c src/gl.c
	cd lib/glfw && cmake . && make

binary: $(OBJECTS)
	-rm $(BIN)/$(TARGET)
	$(CC) -o $(BIN)/$(TARGET) $^ $(LDFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

execute:
	./$(BIN)/$(TARGET)

clean:
	-rm $(OBJECTS)
