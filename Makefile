CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = test_arraylist
SRC = main.cpp
HDR = arraylist.hpp

all: $(TARGET)

$(TARGET): $(SRC) $(HDR)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean