# Compiling like a sigma programmer XD

IDIR = include
CC = gcc
CFLAGS = -I$(IDIR) -Wall -Wextra -O2
TARGET= myprogram
SOURCES = main.c $(wildcard $(IDIR)/*.c) 
HEADERS = $(wildcard $(IDIR)/*.h)
OBJECTS = $(SOURCES:.c=.o)


# Default target name
all: $(TARGET)

# Linking the binary

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ -lm

# Compiling the source code (chad makefile)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET)
