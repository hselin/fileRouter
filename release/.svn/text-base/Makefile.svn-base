CC=g++
CFLAGS=-Wall -g -D_FILE_OFFSET_BITS=64 -c
LIBS=libcryptopp.a
DEPOBJS=common.o crypto.o fuse.o tfs.o
LDFLAGS=-g -Wall `pkg-config fuse --libs` -D_FILE_OFFSET_BITS=64 $(DEPOBJS) $(OBJECTS) $(LIBS) -o
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
ARFLAGS=rcs
OUTPUT=tfs
ARC=ar

all: $(OUTPUT)
	
$(OUTPUT): $(OBJECTS)
	$(CC) $(LDFLAGS) $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.a
	rm -f *.o
	rm -f $(OUTPUT)

#libcommon.a libtfs.a libfuseinterface.a 
#-L. -lcommon -ltfs -lfuseinterface 
