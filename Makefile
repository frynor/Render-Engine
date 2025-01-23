# Compiling like a sigma programmer XD

IDIR = include
SDIR = src
ODIR = obj
CC = gcc
CFLAGS = -I$(IDIR) -Wall -Wextra -O2 -lncurses -lm
TARGET= myprogram


SOURCES = main.c $(wildcard $(SDIR)/*.c) 
HEADERS = $(wildcard $(IDIR)/*.h)
OBJECTS = $(patsubst %.c, $(ODIR)/%.o, $(notdir $(SOURCES)))

# Default target name
all: $(TARGET)

# Linking the binary

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ -lm

# Compiling the source code (chad makefile)

$(ODIR)/%.o: $(SDIR)/%.c $(HEADERS)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ODIR)/main.o: main.c $(HEADERS)
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET)
