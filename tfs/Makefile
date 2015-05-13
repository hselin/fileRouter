CC=g++
CFLAGS=-Wall -g -D_FILE_OFFSET_BITS=64 -c
LD=ld
LDFLAGS=-r
SOURCES=TFSCore.cpp TFSInterface.cpp TFSObject.cpp TFSValueTypes.cpp TFSHandle.cpp TFSOperation.cpp TFSCache.cpp TFSBlock.cpp TFSBlockStore.cpp TFSBlockManager.cpp TFSWrapper.cpp
OBJECTS=$(SOURCES:.cpp=.o)
ARFLAGS=
OUTPUT=tfs.o
ARC=

all: $(SOURCES) $(OUTPUT)
	
$(OUTPUT): $(OBJECTS) 
	$(LD) $(LDFLAGS) $(OBJECTS) -o $(OUTPUT)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(OUTPUT)

