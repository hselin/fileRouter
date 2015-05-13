CC=g++
CFLAGS=-Wall -g -c
LD=ld
LDFLAGS=-r
SOURCES=CryptoInterface.cpp
OBJECTS=$(SOURCES:.cpp=.o)
ARFLAGS=
OUTPUT=crypto.o
ARC=ar

all: $(SOURCES) $(OUTPUT)
	
$(OUTPUT): $(OBJECTS) 
	$(LD) $(LDFLAGS) $(OBJECTS) -o $(OUTPUT)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(OUTPUT)