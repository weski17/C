CXX = g++
CXXFLAGS= -std=c++11 -Wall -Wextra
TARGET = stack_program

SOURCES = stack.cpp

$(TARGET): $(SOURCES)
    $(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

.PHONY: clean run

clean:
    rm -f $(TARGET)

run: $(TARGET)
    ./$(TARGET)