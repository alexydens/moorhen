# VARIABLES

# Operating system
ifeq ($(OS),Windows_NT)
	OPERATING_SYSTEM = Windows
else
	OPERATING_SYSTEM = $(shell uname)
endif

# Shell used
ifeq (OPERATING_SYSTEM,Linux)
	SHELL=/bin/sh
else
	SHELL=C:\Windows\System32\cmd.exe
endif

# For compiling with gcc
ifeq (OPERATING_SYSTEM,Linux)
	CC=/bin/gcc
else
	CC=C:\msys64\ucrt64\bin\gcc.exe
endif
# Flags
CFLAGS = -std=c99 -pedantic -Wall -Wextra
LDFLAGS = -lm -lpthread -O3 -ffast-math

# Directories for build
SRC_DIR=src
INCLUDE_DIR=include
BUILD_DIR=build

# Test directory
TEST_DIR=test

# Name of generated library file
ifeq (OPERATING_SYSTEM,Linux)
	LIBFILE=libmoorhen.a
else
	LIBFILE=moorhen.lib
endif
# Name of generated test binary
ifeq (OPERATING_SYSTEM,Linux)
	TESTFILE=test
else
	TESTFILE=test.exe
endif

# FILE TARGETS:

# The library itself
$(BUILD_DIR)/$(LIBFILE):
	$(CC) $(SRC_DIR) -I./$(INCLUDE_DIR)/ $(CFLAGS) $(LDFLAGS) -o $@

# Testing the library
$(BUILD_DIR)/$(TESTFILE): $(BUILD_DIR)/$(LIBFILE)
	$(CC) $(TEST_DIR)/*.c $(BUILD_DIR)/$(LIBFILE) \
		-I./$(INCLUDE_DIR)/ $(CFLAGS) $(LDFLAGS) -o $@

# PHONY TARGETS: NOT FILES
.PHONY: clean test

# Clear build directory
clean:
	rm -rf $(BUILD_DIR)/build

# Test the library
test: $(BUILD_DIR)/$(TESTFILE)
	./$(BUILD_DIR)/$(TESTFILE)
