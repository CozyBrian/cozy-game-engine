SRC_DIR = src
BUILD_DIR = build/debug
CC = clang++
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_NAME = example1
INCLUDE_PATHS = -I/include
LIBRARY_PATHS = -Llib
COMPILER_FLAGS = -std=c++11 -Wall -O0 -g
LINKER_FLAGS = -framework SDL2
FRAMEWORK_PATHS = -F/Library/Frameworks
FRAMEWORKS = -framework SDL2

all:
	$(CC) $(INCLUDE_PATHS) $(FRAMEWORK_PATHS) $(FRAMEWORKS) $(SRC_FILES) -o $(BUILD_DIR)/$(OBJ_NAME)
