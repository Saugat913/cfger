# Compiler
CC = gcc

# Compiler Flags
CFLAGS = -Wall -Iinclude/private -fPIC

# Source and Header Files
PUBLIC_INCLUDE_DIR= include/cfger
SRCDIR = src
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:.c=.o)



# Build Directory
BUILDDIR = build

# Target Library
TARGET_LIB_DIR=$(BUILDDIR)/lib
TARGET_INCLUDE_DIR=$(BUILDDIR)/include
TARGET_OBJ_DIR=$(BUILDDIR)/obj

TARGET_LIB = $(TARGET_LIB_DIR)/libcfger.a
TARGET_INCLUDE=$(TARGET_INCLUDE_DIR)/cfger

EXAMPLE_DIR= example
EXAMPLE_TARGET=$(EXAMPLE_DIR)/example
EXAMPLE= $(EXAMPLE_DIR)/main.c 


# Default target
all: $(BUILDDIR) $(TARGET_LIB) $(TARGET_INCLUDE)

# Create build directory
$(BUILDDIR):
	mkdir -p $(BUILDDIR)
	mkdir -p $(BUILDDIR)/lib
	mkdir -p $(BUILDDIR)/include
	mkdir -p $(BUILDDIR)/obj


# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Create static library from object files
$(TARGET_LIB): $(OBJ)
	ar rcs $(TARGET_LIB) $(OBJ)
	mv $(OBJ) $(BUILDDIR)/obj
	

# Copy include to build
$(TARGET_INCLUDE):
	cp -r $(PUBLIC_INCLUDE_DIR) $(TARGET_INCLUDE)


# run the example
example:$(EXAMPLE) $(EXAMPLE_DIR)/config.txt $(BUILDDIR) $(TARGET_LIB) $(TARGET_INCLUDE)
	$(CC) -I$(TARGET_INCLUDE_DIR) $(EXAMPLE) -o $(EXAMPLE_TARGET) -L$(TARGET_LIB_DIR) -lcfger
	


# Clean build directory and object files
clean:
	rm -rf $(BUILDDIR) $(OBJ)
	rm $(EXAMPLE_TARGET)

# Phony targets
.PHONY: all clean