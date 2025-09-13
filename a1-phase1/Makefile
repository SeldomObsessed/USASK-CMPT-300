# Makefile
# Logan Fossenier & William Morris
# hzv143 & wjm625
# 11343891 & 11278140
# CMPT332 Fall 2025

CC = gcc
CFLAGS = -g -O0
CPPFLAGS = -std=gnu90 -Wall -Werror -Wextra -Wsign-conversion -pedantic \
	-I/student/cmpt332/pthreads -I.

AMD = Linux-x86_64

OBJ_DIR = ./build/obj
LIB_DIR = ./build/lib
BIN_DIR = ./build/bin

LDFLAGS = -l:libpthreads.a
LIST_LDFLAGS = -L$(LIB_DIR)/$(AMD) -l:list.a
LIST_OBJS = $(OBJ_DIR)/$(AMD)/list_adders.o $(OBJ_DIR)/$(AMD)/list_movers.o \
	$(OBJ_DIR)/$(AMD)/list_removers.o

### Will this is random internet copypasta, I didn't make sure the
### windows part works

# Dynamically select which binaries to build based on the OS
ifeq ($(OS),Windows_NT)
	TARGETS = will_win_binary
else
	ifeq ($(shell uname -s),Linux)
		TARGETS = mytestlist
	endif
endif

.PHONY : all clean

all : $(TARGETS)

clean :
	rm -rf ./build/ mytestlist

$(OBJ_DIR)/$(AMD) :
	mkdir -p $(OBJ_DIR)/$(AMD)

$(LIB_DIR)/$(AMD) :
	mkdir -p $(LIB_DIR)/$(AMD)

$(BIN_DIR)/$(AMD) :
	mkdir -p $(BIN_DIR)/$(AMD)

# Make objects
$(OBJ_DIR)/$(AMD)/list_adders.o : list_adders.c | $(OBJ_DIR)/$(AMD)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) \
		list_adders.c -o $(OBJ_DIR)/$(AMD)/list_adders.o

$(OBJ_DIR)/$(AMD)/list_movers.o : list_movers.c | $(OBJ_DIR)/$(AMD)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) \
		list_movers.c -o $(OBJ_DIR)/$(AMD)/list_movers.o

$(OBJ_DIR)/$(AMD)/list_removers.o : list_removers.c | $(OBJ_DIR)/$(AMD)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) \
		list_removers.c -o $(OBJ_DIR)/$(AMD)/list_removers.o

$(OBJ_DIR)/$(AMD)/mytestlist.o : mytestlist.c | $(OBJ_DIR)/$(AMD)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) \
		mytestlist.c -o $(OBJ_DIR)/$(AMD)/mytestlist.o

# Make libraries
$(LIB_DIR)/$(AMD)/list.a : $(LIST_OBJS) | $(LIB_DIR)/$(AMD)
	ar -rcs $(LIB_DIR)/$(AMD)/list.a $(LIST_OBJS)

# Link binaries
$(BIN_DIR)/$(AMD)/mytestlist: $(LIB_DIR)/$(AMD)/list.a \
	$(OBJ_DIR)/$(AMD)/mytestlist.o | $(BIN_DIR)/$(AMD)
	$(CC) $(CFLAGS) $(OBJ_DIR)/$(AMD)/mytestlist.o \
		$(LIST_LDFLAGS) -o $(BIN_DIR)/$(AMD)/mytestlist
# Soft link to ./
mytestlist: $(BIN_DIR)/$(AMD)/mytestlist
	ln -sf $(BIN_DIR)/$(AMD)/mytestlist mytestlist

