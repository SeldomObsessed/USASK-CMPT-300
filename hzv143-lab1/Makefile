#  Name: Fossenier, Logan
#  NSID: hzv143
#  Student Number: 11343891

CROSS_COMPILE=arm-linux-gnueabihf-.

CC = arm-linux-gnueabihf-gcc
CFLAGS = -g -O0
CPPFLAGS = -std=gnu90 -Wall -Werror -Wextra -Wsign-conversion -pedantic -I. \
	-I/student/cmpt332/pthreads

BUILD_DIR = ./build/$(shell uname -s)-$(shell uname -m)
LIB_DIR = ./lib/$(shell uname -s)-$(shell uname -m)
BIN_DIR = ./bin/$(shell uname -s)-$(shell uname -m)

LDFLAGS = -L$(LIB_DIR) -L/student/cmpt332/pthreads/lib/Linuxarmv7l

LIB_OBJS = ########

# My make targets
.PHONY : all clean clean-hard

# Make the executable
all : sample-linux

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



