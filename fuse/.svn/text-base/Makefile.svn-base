CC=gcc
CFLAGS=-g -Wall -D_FILE_OFFSET_BITS=64 -DFUSE_USE_VERSION=26 `pkg-config fuse --cflags` -c
LD=ld
LDFLAGS=-r
SOURCES=fuseInterface.c
OBJECTS=$(SOURCES:.c=.o)
ARFLAGS=
OUTPUT=fuse.o
ARC=

all: $(SOURCES) $(OUTPUT)
	
$(OUTPUT): $(OBJECTS) 
	$(LD) $(LDFLAGS) $(OBJECTS) -o $(OUTPUT)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(OUTPUT)
