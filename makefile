CXX			:= g++
CXX_FLAGS	:= -c

MAIN_FILE	:= main
SRC_DIR		:= ./src
EXEC_FILE	:= just-explode


all: clean compile execute

clean:
	@echo "🧹 Cleaning ..."
	-rm $(MAIN_FILE).o $(EXEC_FILE)

compile: $(MAIN_FILE).o
	@echo "🚧 Building ..."
	$(CXX) $(MAIN_FILE).o -o $(EXEC_FILE) -lsfml-graphics -lsfml-window -lsfml-system

$(MAIN_FILE).o:
	$(CXX) $(CXX_FLAGS) $(SRC_DIR)/$(MAIN_FILE).cpp

execute:
	@echo "🚀 Executing ..."
	./$(EXEC_FILE)