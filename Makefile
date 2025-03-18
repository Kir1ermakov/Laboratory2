CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TEST_FLAGS = -lgtest -lgtest_main -pthread

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# Исходные файлы
SRCS = $(SRC_DIR)/сreation.cpp
TEST_SRCS = $(TEST_DIR)/creation_test.cpp

# Объектные файлы
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TEST_OBJS = $(TEST_SRCS:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/%.o)

all: directories main test

directories:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(TEST_DIR)

# Компиляция основной программы
main: $(BUILD_DIR)/main
$(BUILD_DIR)/main: $(SRC_DIR)/main.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Компиляция тестов
test: $(BUILD_DIR)/runTests
	./$(BUILD_DIR)/runTests

$(BUILD_DIR)/runTests: $(TEST_SRCS) $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(TEST_FLAGS)

# Правило для компиляции .cpp в .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all directories test clean