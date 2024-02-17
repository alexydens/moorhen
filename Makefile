# VARIABLES

# Operating system
#ifeq ($(OS),Windows_NT)
#	OPERATING_SYSTEM :=Windows
#else
#	OPERATING_SYSTEM :=Linux
#endif

# Shell used
#ifeq (OPERATING_SYSTEM,Linux)
	SHELL=/bin/sh
#else
#	SHELL=C:\Windows\System32\cmd.exe
#endif

# For compiling with gcc
#ifeq (OPERATING_SYSTEM,Linux)
	CC=/bin/gcc
#else
#	CC=C:\msys64\ucrt64\bin\gcc.exe
#endif
# Flags
CFLAGS = -std=c99 -pedantic -Wall -Wextra
CFLAGS += -Wno-unused-variable
LDFLAGS = -lm -lpthread -O3 -ffast-math

# Directories for build
SRC_DIR=src
INCLUDE_DIR=include
BUILD_DIR=build

# Test directory
TEST_DIR=test

# Name of generated library file
#ifeq (OPERATING_SYSTEM,Linux)
	LIBFILE=libmoorhen.a
#else
#	LIBFILE=moorhen.lib
#endif
# Name of generated test binary
#ifeq (OPERATING_SYSTEM,Linux)
	TESTFILE=test
#else
#	TESTFILE=test.exe
#endif

# FILE TARGETS:

# The library sources
$(BUILD_DIR)/base.o: $(SRC_DIR)/base.c
	$(CC) -c $< -I./$(INCLUDE_DIR)/ $(CFLAGS) -o $@
$(BUILD_DIR)/logging.o: $(SRC_DIR)/logging.c
	$(CC) -c $< -I./$(INCLUDE_DIR)/ $(CFLAGS) -o $@
$(BUILD_DIR)/arena_alloc.o: $(SRC_DIR)/arena_alloc.c
	$(CC) -c $< -I./$(INCLUDE_DIR)/ $(CFLAGS) -o $@

# The library itself
$(BUILD_DIR)/$(LIBFILE): $(BUILD_DIR)/base.o \
	$(BUILD_DIR)/logging.o \
	$(BUILD_DIR)/arena_alloc.o
	$(AR) rcs $@ $(BUILD_DIR)/*.o

# Testing the library
$(BUILD_DIR)/$(TESTFILE): $(BUILD_DIR)/$(LIBFILE)
	$(CC) $(TEST_DIR)/*.c $(BUILD_DIR)/$(LIBFILE) \
		-I./$(INCLUDE_DIR)/ $(CFLAGS) -DENABLE_ASSERT $(LDFLAGS) -o $@

# Testing the library
$(BUILD_DIR)/gdb_$(TESTFILE): $(BUILD_DIR)/$(LIBFILE)
	$(CC) -ggdb $(TEST_DIR)/*.c $(BUILD_DIR)/$(LIBFILE) \
		-I./$(INCLUDE_DIR)/ $(CFLAGS) -DENABLE_ASSERT $(LDFLAGS) -o $@

# PHONY TARGETS: NOT FILES
.PHONY: clean test gdb build

# Clear build directory
clean:
	rm -rf $(BUILD_DIR)/*

# Build the library
build: $(BUILD_DIR)/$(LIBFILE)

# Test the library
test: $(BUILD_DIR)/$(TESTFILE)
	./$(BUILD_DIR)/$(TESTFILE)

# Test the library
gdb: $(BUILD_DIR)/gdb_$(TESTFILE)
	./$(BUILD_DIR)/gdb_$(TESTFILE)
