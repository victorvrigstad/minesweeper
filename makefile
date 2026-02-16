# pacman -S mingw-w64-x86_64-make (IN MINGW64)
# Set-Alias make mingw32-make
# make, make run, make clean


CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -pedantic -Iinclude
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = $(wildcard src/*.cpp) # does not go into subfolders
OBJ = $(patsubst src/%.cpp,%.o,$(SRC))

TARGET = main.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LIBS)

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	del /Q $(OBJ) $(TARGET) 2>nul

.PHONY: all clean run