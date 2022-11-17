# Compilation Flags
CXX = g++
CPPFLAGS = -I$(LIBDIR) -Wall -Wextra
CXXFLAGS=$(shell root-config --cflags)

# Libraries to inlcude e.g. ROOT
LIBS=$(shell root-config --libs) 

# Debug Flags
DEBUGFLAGS= -O0 -g -D _DEBUG

# Output name of the executable
MAIN = AnalyzeNue

# List the object files here
OBJ_FILES = bin/*.o

# Main Target
all: $(MAIN)

$(MAIN): $(OBJ_FILES)
	@echo
	@echo "\033[0;32mBuilding $(MAIN)\033[0;36m"
	$(CXX) $(LIBS) -o $@ $^
	@echo "\033[0;31mDone!"
	@echo

# Build the Object files
bin/%.o: src/%.cxx
	@mkdir -p bin
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEBUGFLAGS) -c $^
	@mv *.o bin

# Clean compilation
clean:
	@echo "\033[0;31m"
	rm AnalyzeNue bin/*
	@echo
