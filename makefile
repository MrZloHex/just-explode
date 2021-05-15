CXX			:= g++
CXX_FLAGS	:= --std=c++20 -c -Wall -Wextra
SFML_FLAGS	:= -lsfml-graphics -lsfml-window -lsfml-system

MAIN_FILE	:= Main
ALG			:= Algorithm
FUN			:= Functions
SRC_DIR		:= ./src/code
EXEC_FILE	:= just-explode

all: clean compile execute

clean:
	@echo "🧹 Cleaning ..."
	-rm $(MAIN_FILE).o $(ALG).o $(FUN).o $(EXEC_FILE) 

compile: $(MAIN_FILE).o $(ALG).o $(FUN).o
	@echo "🚧 Building ..."
	$(CXX) $(MAIN_FILE).o $(ALG).o $(FUN).o -o $(EXEC_FILE) $(SFML_FLAGS)

$(MAIN_FILE).o:
	$(CXX) $(CXX_FLAGS) $(SRC_DIR)/$(MAIN_FILE).cpp

$(ALG).o:
	$(CXX) $(CXX_FLAGS) $(SRC_DIR)/$(ALG).cpp

$(FUN).o:
	$(CXX) $(CXX_FLAGS) $(SRC_DIR)/$(FUN).cpp

execute:
	@echo "🚀 Executing ..."
	./$(EXEC_FILE)
