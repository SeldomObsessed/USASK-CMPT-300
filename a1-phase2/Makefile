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
WIN = Windows-x86_64
OBJ_DIR = ./build/obj
LIB_DIR = ./build/lib
BIN_DIR = ./build/bin
UBC_DIR = /student/cmpt332/pthreads/lib/Linuxx86_64


WIN_LDFLAGS = -L$(LIB_DIR)/$(WIN) -l:square.a
UBC_LDFLAGS = -L$(UBC_DIR) -l:libpthreads.a
LIST_LDFLAGS = -L$(LIB_DIR)/$(AMD) -l:list.a
LIST_OBJS = $(OBJ_DIR)/$(AMD)/list_adders.o $(OBJ_DIR)/$(AMD)/list_movers.o \
	$(OBJ_DIR)/$(AMD)/list_removers.o $(OBJ_DIR)/$(AMD)/list_mem.o

# Dynamically select which binaries to build based on the OS
ifeq ($(OS),Windows_NT)
	TARGETS = partA1
else ifeq ($(shell uname -s),Linux)
		TARGETS = mytestlist
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

# Windows dirs
$(OBJ_DIR)/$(WIN) :
	mkdir -p $(OBJ_DIR)/$(WIN)

$(LIB_DIR)/$(WIN) :
	mkdir -p $(LIB_DIR)/$(WIN)

$(BIN_DIR)/$(WIN) :
	mkdir -p $(BIN_DIR)/$(WIN)

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

$(OBJ_DIR)/$(AMD)/list_mem.o : list_mem.c | $(OBJ_DIR)/$(AMD)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) \
		list_mem.c -o $(OBJ_DIR)/$(AMD)/list_mem.o

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

# Make PartA files

# Objects

$(OBJ_DIR)/$(WIN)/partA1.o : partA1.c | $(OBJ_DIR)/$(WIN)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) partA1.c -o $(OBJ_DIR)/$(WIN)/partA1.o

$(OBJ_DIR)/$(AMD)/partA2.o : partA2.c | $(OBJ_DIR)/$(AMD)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) partA2.c -o $(OBJ_DIR)/$(WIN)/partA2.o

$(OBJ_DIR)/$(AMD)/partA3.o : partA3.c | $(OBJ_DIR)/$(AMD)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) partA3.c -o $(OBJ_DIR)/$(WIN)/partA3.o

$(OBJ_DIR)/$(AMD)/partA4.o : partA4.c | $(OBJ_DIR)/$(AMD)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) partA4.c -o $(OBJ_DIR)/$(WIN)/partA4.o

$(OBJ_DIR)/$(WIN)/square.o : square.c | $(OBJ_DIR)/$(WIN)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) square.c -o $(OBJ_DIR)/$(WIN)/square.o

# Libraries

$(LIB_DIR)/$(WIN)/square.a : $(OBJ_DIR)/$(WIN)/square.o | \
	$(LIB_DIR)/$(WIN)
	ar -rcs $(LIB_DIR)/$(WIN)/square.a $(OBJ_DIR)/$(WIN)/square.o

# Link binaries

partA1 : $(LIB_DIR)/$(WIN)/square.a \
	$(OBJ_DIR)/$(WIN)/partA1.o | $(BIN_DIR)/$(WIN)
	$(CC) $(CFLAGS) $(OBJ_DIR)/$(WIN)/partA1.o $(WIN_LDFLAGS) \
	-o partA1

partA2 : $(LIB_DIR)/$(WIN)/square.a $(UBC_DIR)/libpthreads.a \
	$(OBJ_DIR)/$(AMD)/partA2.o | $(BIN_DIR)/$(AMD)
	$(CC) $(CFLAGS) $(OBJ_DIR)/$(AMD)/partA2.o $(UBC_LDFLAGS) $(WIN_LDFLAGS) \
	-o $(BIN_DIR)/$(AMD)/partA2

partA3 : $(LIB_DIR)/$(WIN)/square.a \
	$(OBJ_DIR)/$(AMD)/partA3.o | $(BIN_DIR)/$(AMD)
	$(CC) $(CFLAGS) $(OBJ_DIR)/$(AMD)/partA3.o $(WIN_LDFLAGS) -lpthread \
	-o $(BIN_DIR)/$(AMD)/partA3

partA4 : $(LIB_DIR)/$(WIN)/square.a \
	$(OBJ_DIR)/$(AMD)/partA4.o | $(BIN_DIR)/$(AMD)
	$(CC) $(CFLAGS) $(OBJ_DIR)/$(AMD)/partA4.o $(WIN_LDFLAGS) \
	-o $(BIN_DIR)/$(AMD)/partA4

# Soft link to ./

#partA1 : $(BIN_DIR)/$(WIN)/partA1
#	ln -sf $(BIN_DIR)/$(WIN)/partA1 partA1
# commented out because windows doesn't like sf links

partA2 : $(BIN_DIR)/$(AMD)/partA2
	ln -sf $(BIN_DIR)/$(AMD)/partA2 partA2

partA3 : $(BIN_DIR)/$(AMD)/partA3
	ln -sf $(BIN_DIR)/$(AMD)/partA3 partA3

partA4 : $(BIN_DIR)/$(AMD)/partA4
	ln -sf $(BIN_DIR)/$(AMD)/partA4 partA4

