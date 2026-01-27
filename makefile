# pacman -S mingw-w64-x86_64-make (IN MINGW64)
# Set-Alias make mingw32-make
# make, make run, make clean


CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -pedantic
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = $(wildcard *.cpp) # does not go into subfolders
OBJ = $(SRC:.cpp=.o)

TARGET = main.exe

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	del /Q $(OBJ) $(TARGET)

.PHONY: all clean run