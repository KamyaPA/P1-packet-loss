CC = gcc
CLINUXFLAGS =
CFLAGS = -Wall -pedantic -ansi $(CLINUXFLAGS)
EXTENTION = .exe
TARGET = a$(EXTENTION)
UNAME := $(shell uname)
UNAME_MAC := Darwin
UNAME_LINUX := Linux

BUILD := build/

ifeq ($(UNAME), $(UNAME_LINUX))
CLINUXFLAGS := -lm
EXTENTION := .out
endif

ifeq ($(UNAME), $(UNAME_MAC))
EXTENTION := .out
endif

$(TARGET): main.o conf.o list.o tree.o  create_function.o
	$(CC) $^ -o $@ $(CFLAGS)

main.o: main.c
	$(CC) $^ -c -o $@ $(CFLAGS)

conf.o: conf.c
	$(CC) $^ -c -o $@ $(CFLAGS)

list.o: list.c
	$(CC) $^ -c -o $@ $(CFLAGS)

tree.o: tree.c
	$(CC) $^ -c -o $@ $(CFLAGS)

create_function.o: create_function.c
	$(CC) $^ -c -o $@ $(CFLAGS)
