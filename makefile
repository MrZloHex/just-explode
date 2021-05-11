CXX			:= g++
CXX_FLAGS	:= -c -Wall -Wextra 
SFML_FLAGS	:= -lsfml-graphics -lsfml-window -lsfml-system

MAIN_FILE	:= Main
ALG			:= Algorithm
ILL			:= Illustration
SRC_DIR		:= ./src
EXEC_FILE	:= just-explode


all: clean compile execute

clean:
	@echo "🧹 Cleaning ..."
	-rm $(MAIN_FILE).o $(ALG).o $(EXEC_FILE) 

compile: $(MAIN_FILE).o $(ALG).o
	@echo "🚧 Building ..."
	$(CXX) $(MAIN_FILE).o $(ALG).o -o $(EXEC_FILE)

$(MAIN_FILE).o:
	$(CXX) $(CXX_FLAGS) $(SRC_DIR)/$(MAIN_FILE).cpp

$(ALG).o:
	$(CXX) $(CXX_FLAGS) $(SRC_DIR)/$(ALG).cpp

$(ILL).o:
	$(CXX) $(CXX_FLAGS) $(SRC_DIR)/$(ILL).cpp

execute:
	@echo "🚀 Executing ..."
	./$(EXEC_FILE)
