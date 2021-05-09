CXX			:= g++
CXX_FLAGS	:= -c -Wall -Wextra -Werror
SFML_FLAGS	:= -lsfml-graphics -lsfml-window -lsfml-system

MAIN_FILE	:= Main
CLASSES		:= Algorithm
SRC_DIR		:= ./src
EXEC_FILE	:= just-explode


all: clean compile execute

clean:
	@echo "🧹 Cleaning ..."
	-rm $(MAIN_FILE).o $(CLASSES).o $(EXEC_FILE)

compile: $(MAIN_FILE).o $(CLASSES).o
	@echo "🚧 Building ..."
	$(CXX) $(MAIN_FILE).o $(CLASSES).o -o $(EXEC_FILE) $(SFML_FLAGS)

$(MAIN_FILE).o:
	$(CXX) $(CXX_FLAGS) $(SRC_DIR)/$(MAIN_FILE).cpp

$(CLASSES).o:
	$(CXX) $(CXX_FLAGS) $(SRC_DIR)/$(CLASSES).cpp

execute:
	@echo "🚀 Executing ..."
	./$(EXEC_FILE)