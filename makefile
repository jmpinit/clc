PROG := clc

ifeq ($(OS),Windows_NT)
S := \\
else
S := /
endif

SRCDIR := src
OBJDIR := obj
BINDIR := bin

SOURCES =	clc.c \
			le.c \
			
INCLUDES = -Isrc$(S)inc -I/usr/local/include -I/usr/include/lua5.1
OBJECTS = $(patsubst %,$(OBJDIR)$(S)%,$(SOURCES:.c=.o))

CFLAGS := -Wall -pedantic -std=c99 -g -O0 -gstabs
LFLAGS =  -L/usr/local/lib -llua5.1
CC := gcc

all: $(PROG)

test: $(PROG)
	./bin/clc 0 1 0 1 "4*math.sin(x/2)+6"

run: $(PROG)
	bin$(S)$(PROG)
	
debug: $(PROG)
	gdb bin$(S)$(PROG)

# linking the program.
$(PROG): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BINDIR)$(S)$(PROG) $(LFLAGS)

# compiling source files.
$(OBJDIR)$(S)%.o: $(SRCDIR)$(S)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -s -o $@ $<

clean:
ifeq ($(OS),Windows_NT)
	del $(OBJECTS)
else
	rm $(OBJECTS)
endif

.PHONY: all clean

