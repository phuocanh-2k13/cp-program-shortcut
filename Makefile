CXX = g++
CXXFLAGS = -O2 -funroll-loops -std=c++17 -Wall -Wextra

TEMPLATE_DIR = template
BUILD_DIR = build

TARGET_MAIN = cp-setup
TARGET_INSTALL = install

SRC_MAIN = src/main.cpp
SRC_INSTALL = src/install.cpp

SRC_COMPUTE = compute/compute.cpp
SRC_WRAPPER = wrapper/wrapper.cpp

OBJS_MAIN = $(SRC_MAIN) $(SRC_COMPUTE) $(SRC_WRAPPER)

all: build

.PHONY: all build test clean

build: $(BUILD_DIR)/$(TARGET_MAIN) $(BUILD_DIR)/$(TARGET_INSTALL)
	@mkdir -p $(BUILD_DIR)/$(TEMPLATE_DIR)
	cp $(TEMPLATE_DIR)/template_default.cpp $(BUILD_DIR)/$(TEMPLATE_DIR)/
	cp $(TEMPLATE_DIR)/template_leetcode.cpp $(BUILD_DIR)/$(TEMPLATE_DIR)/
	@echo "Build success!"

$(BUILD_DIR)/$(TARGET_MAIN): $(OBJS_MAIN)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/$(TARGET_INSTALL): $(SRC_INSTALL)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@

test: CXXFLAGS += -DDEBUG -g
test: clean build
	./$(BUILD_DIR)/$(TARGET_MAIN)

clean:
	rm -rf $(BUILD_DIR)
