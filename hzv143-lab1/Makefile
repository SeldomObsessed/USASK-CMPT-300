#  Name: Fossenier, Logan
#  NSID: hzv143
#  Student Number: 11343891

ARM=arm-linux-gnueabihf-
PPC=powerpc-linux-gnu-

CC = gcc
CFLAGS = -g -O0
CPPFLAGS = -std=gnu90 -Wall -Werror -Wextra -Wsign-conversion -pedantic -I. \
	-I/student/cmpt332/pthreads

AMD_ARCH = Linux-x86_64
ARM_ARCH = Linux-armv7l
PPC_ARCH = Linux-ppc

BUILD_DIR = ./build/obj
LIB_DIR = ./build/lib
BIN_DIR = ./build/bin

LDFLAGS = -L/student/cmpt332/pthreads/lib/Linuxarmv7l

# My make targets
.PHONY : all clean

# Make the executable
all : sample-linux sample-linux-arm sample-linux-ppc

# Delete everything for this system
clean :
	rm -rf $(BUILD_DIR) $(LIB_DIR) $(BIN_DIR) sample-linux
	rmdir build/ lib/ bin/
	echo "All cleaned up"

# Full wipe all systems (for a hand-in, say)
clean-hard :
	rm -rf build/ lib/ bin/ sample-linux
	echo "Hard cleaned up"

# Path building
$(BUILD_DIR) :
	mkdir -p $(BUILD_DIR)

$(LIB_DIR) :
	mkdir -p $(LIB_DIR)

$(BIN_DIR) :
	mkdir -p $(BIN_DIR)

# Create object files
$(BUILD_DIR)/linux-lib.o : linux-lib.c | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) \
		linux-lib.c -o $(BUILD_DIR)/linux-lib.o

$(BUILD_DIR)/sample-linux.o : sample-linux.c | $(BUILD_DIR)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) \
		sample-linux.c -o $(BUILD_DIR)/sample-linux.o

# Create library
$(LIB_DIR)/linux-lib.a : $(BUILD_DIR)/linux-lib.o | $(LIB_DIR)
	arm-linux-gnueabihf-ar -rcs $(LIB_DIR)/linux-lib.a $(BUILD_DIR)/linux-lib.o

# Link binary
$(BIN_DIR)/sample-linux : \
	$(LIB_DIR)/linux-lib.a $(BUILD_DIR)/sample-linux.o | $(BIN_DIR)
	$(CC) $(CFLAGS) \
		$(BUILD_DIR)/sample-linux.o \
		$(LDFLAGS) -l:linux-lib.a -l:libpthreads.a \
			-o $(BIN_DIR)/sample-linux

# Soft link to the main dir
sample-linux : $(BIN_DIR)/sample-linux
	ln -sf $(BIN_DIR)/sample-linux sample-linux



