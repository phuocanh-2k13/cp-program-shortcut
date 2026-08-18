CXX = g++
CXXFLAGS = -O2 -funroll-loops -std=c++17 -Wall -Wextra

TEMPLATE_DIR = template
BUILD_DIR = build
TARGET = main
SRC = main.cpp

all: $(TARGET)
PHONY: build test clean

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

build: $(TARGET)
	mkdir -p $(BUILD_DIR)
	mv $(TARGET) $(BUILD_DIR)/
	mv $(TEMPLATE_DIR)/* $(BUILD_DIR)/

test: build
	./$(BUILD_DIR)/$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
