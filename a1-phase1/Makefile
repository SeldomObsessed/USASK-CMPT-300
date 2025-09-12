# Makefile
# Logan Fossenier & William Morris
# hzv143 & wjm625
# 11343891 & 11278140
# CMPT332 Fall 2025

ARM_CC = arm-linux-gnueabihf-
PPC_CC = powerpc-linux-gnu-

CC = gcc
CFLAGS = -g -O0
CPPFLAGS = -std=gnu90 -Wall -Werror -Wextra -Wsign-conversion -pedantic \
	-I/student/cmpt332/pthreads -I.

AMD = Linux-x86_64
ARM = Linux-armv7l
PPC = Linux-ppc

OBJ_DIR = /build/obj
LIB_DIR = ./build/lib
BIN_DIR = ./build/bin

LDFLAGS = -l:libpthreads.a


### Will this is random internet copypasta, I didn't make sure the
### windows part works

# Dynamically select which binaries to build based on the OS
ifeq ($(OS),Windows_NT)
	TARGETS = will_win_binary
else
	ifeq ($(shell uname -s),Linux)
		TARGETS = mylibtest
	endif
endif

.PHONY : all clean

all : $(TARGETS)
