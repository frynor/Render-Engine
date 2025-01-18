CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET= myprogram
SOURCES = main.c vector2.c 
HEADERS = vector2.h 
OBJECTS = $(SOURCES:.c=.o)


# Default target
all: $(TARGET)

# Linking the binary

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

# Compiling the source code

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

.PHONY: clean
clean:
	rm -f $(OBJECTS) $(TARGET)
