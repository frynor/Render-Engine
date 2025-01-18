# Compiling like a sigma programmer XD

CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET= myprogram
SOURCES = main.c vector2.c 
HEADERS = vector2.h 
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
