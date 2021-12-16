CC = gcc
CLINUXFLAGS =
CFLAGS = -Wall -pedantic $(CLINUXFLAGS)
EXTENTION = .exe
TARGET = a$(EXTENTION)
UNAME := $(shell uname)
UNAME_MAC := Darwin
UNAME_LINUX := Linux

FILES :=  main.o conf.o list.o tree.o create_function.o router.o routing_tree.o


BUILD := build/

ifeq ($(UNAME), $(UNAME_LINUX))
CLINUXFLAGS := -lm
EXTENTION := .out
endif

ifeq ($(UNAME), $(UNAME_MAC))
EXTENTION := .out
endif

$(TARGET): $(FILES)
	$(CC) $^ -o $@ $(CFLAGS)

%.o: %.c
	$(CC) $^ -c -o $@ $(CFLAGS)

