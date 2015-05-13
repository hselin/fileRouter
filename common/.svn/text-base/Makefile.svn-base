CC=g++
CFLAGS=-Wall -g -c
LD=ld
LDFLAGS=-r
SOURCES=Log.cpp Util.cpp
OBJECTS=$(SOURCES:.cpp=.o)
ARFLAGS=
OUTPUT=common.o
ARC=ar

all: $(SOURCES) $(OUTPUT)
	
$(OUTPUT): $(OBJECTS) 
	$(LD) $(LDFLAGS) $(OBJECTS) -o $(OUTPUT)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(OUTPUT)

