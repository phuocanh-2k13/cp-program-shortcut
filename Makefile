CXX = g++
CXXFLAGS = -O2 -funroll-loops -std=c++17 -Wall -Wextra

TEMPLATE_DIR = template
BUILD_DIR = build
TARGET = main

SRC_MAIN = main.cpp
SRC_COMPUTE = compute/compute.cpp
SRC_WRAPPER = wrapper/wrapper.cpp
SRC = $(SRC_MAIN) $(SRC_COMPUTE) $(SRC_WRAPPER)

all: $(TARGET)
.PHONY: build test clean

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

build: $(TARGET)
	mkdir -p $(BUILD_DIR)
	mv $(TARGET) $(BUILD_DIR)/
	cp $(TEMPLATE_DIR)/template_default.cpp $(BUILD_DIR)/template_default.cpp
	cp $(TEMPLATE_DIR)/template_leetcode.cpp $(BUILD_DIR)/template_leetcode.cpp

test: build
	cd ./$(BUILD_DIR) && ./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
