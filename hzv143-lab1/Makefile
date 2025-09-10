#  Name: Fossenier, Logan
#  NSID: hzv143
#  Student Number: 11343891

ARM_CC = arm-linux-gnueabihf-
PPC_CC = powerpc-linux-gnu-

CC = gcc
CFLAGS = -g -O0
CPPFLAGS = -std=gnu90 -Wall -Werror -Wextra -Wsign-conversion -pedantic \
	-I/student/cmpt332/pthreads -I.

AMD = Linux-x86_64
ARM = Linux-armv7l
PPC = Linux-ppc

OBJ_DIR = ./build/obj
LIB_DIR = ./build/lib
BIN_DIR = ./build/bin

LDFLAGS = -l:libpthreads.a

# My make targets
.PHONY : all clean

# Make the executable
# sample-linux sample-linux-ppc
all :  sample-linux-arm

# Delete everything
clean :
	rm -rf ./build $(ALL)
	echo "All cleaned up"

# Path building
$(BIN_DIR)/$(AMD) :
	mkdir -p $(BIN_DIR)/$(AMD)
$(LIB_DIR)/$(AMD) :
	mkdir -p $(LIB_DIR)/$(AMD)
$(OBJ_DIR)/$(AMD) :
	mkdir -p $(OBJ_DIR)/$(AMD)

$(BIN_DIR)/$(ARM) :
	mkdir -p $(BIN_DIR)/$(ARM)
$(LIB_DIR)/$(ARM) :
	mkdir -p $(LIB_DIR)/$(ARM)
$(OBJ_DIR)/$(ARM) :
	mkdir -p $(OBJ_DIR)/$(ARM)

# Make objects
$(OBJ_DIR)/$(AMD)/sample-linux.o : sample-linux.c | $(OBJ_DIR)/$(AMD)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) \
		sample-linux.c -o $(OBJ_DIR)/$(AMD)/sample-linux.o

$(OBJ_DIR)/$(AMD)/linux-lib.o : linux-lib.c | $(OBJ_DIR)/$(AMD)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) \
		linux-lib.c -o  $(OBJ_DIR)/$(AMD)/linux-lib.o

$(OBJ_DIR)/$(ARM)/sample-raspi.o : sample-linux.c | $(OBJ_DIR)/$(ARM)
	$(ARM_CC)$(CC) -c $(CFLAGS) $(CPPFLAGS) \
		sample-linux.c -o $(OBJ_DIR)/$(ARM)/sample-raspi.o

$(OBJ_DIR)/$(ARM)/raspi-lib.o : linux-lib.c | $(OBJ_DIR)/$(ARM)
	$(ARM_CC)$(CC) -c $(CFLAGS) $(CPPFLAGS) \
		linux-lib.c -o $(OBJ_DIR)/$(ARM)/raspi-lib.o

# Make libraries
$(LIB_DIR)/$(AMD)/linux-lib.a : \
	$(OBJ_DIR)/$(AMD)/linux-lib.o | $(LIB_DIR)/$(AMD)
	ar -rcs $(LIB_DIR)/$(AMD)/linux-lib.a $(OBJ_DIR)/$(AMD)/linux-lib.o

$(LIB_DIR)/$(ARM)/raspi-lib.a : \
	$(OBJ_DIR)/$(ARM)/raspi-lib.o | $(LIB_DIR)/$(ARM)
	$(ARM_CC)ar -rcs $(LIB_DIR)/$(ARM)/raspi-lib.a \
		$(OBJ_DIR)/$(ARM)/raspi-lib.o

# Link binaries
$(BIN_DIR)/$(AMD)/sample-linux : \
	$(LIB_DIR)/$(AMD)/linux-lib.a $(OBJ_DIR)/$(AMD)/sample-linux.o \
	| $(BIN_DIR)/$(AMD)
	$(CC) $(CFLAGS) $(OBJ_DIR)/$(AMD)/sample-linux.o \
		-L/student/cmpt332/pthreads/lib/Linuxx86_64 \
		-L$(LIB_DIR)/$(AMD) $(LDFLAGS) -l:linux-lib.a \
			-o $(BIN_DIR)/$(AMD)/sample-linux

$(BIN_DIR)/$(ARM)/sample-linux-arm : \
	$(LIB_DIR)/$(ARM)/raspi-lib.a $(OBJ_DIR)/$(ARM)/sample-raspi.o \
	| $(BIN_DIR)/$(ARM)
	$(ARM_CC)$(CC) $(CFLAGS) $(OBJ_DIR)/$(ARM)/sample-raspi.o \
		-L/student/cmpt332/pthreads/lib/Linuxarmv7l \
		-L$(LIB_DIR)/$(ARM) $(LDFLAGS) -l:raspi-lib.a \
			-o $(BIN_DIR)/$(ARM)/sample-linux-arm

# Soft link to ./
sample-linux : $(BIN_DIR)/$(AMD)/sample-linux
	ln -sf $(BIN_DIR)/$(AMD)/sample-linux sample-linux

sample-linux-arm : $(BIN_DIR)/$(ARM)/sample-linux-arm
	ln -sf $(BIN_DIR)/$(ARM)/sample-linux-arm sample-linux-arm

