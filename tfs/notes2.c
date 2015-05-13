string s1 = "/abc/ hello /hello world!";
vector <string> words1 = Fwk::words(s1, '/');
string prefix1 = Fwk::prefix(s1, '/');
string lastWord1 = Fwk::lastWord(s1, '/');
    
string s2 = "abc/ hello /hello world!/";
vector <string> words2 = Fwk::words(s2, '/');
string prefix2 = Fwk::prefix(s2, '/');
string lastWord2 = Fwk::lastWord(s2, '/');


string s3 = " hello world! ";
vector <string> words3 = Fwk::words(s3, '/');
string prefix3 = Fwk::prefix(s3, '/');
string lastWord3 = Fwk::lastWord(s3, '/');

void TFSIOInterface::objectAdd(ObjectPath path, TFSObject::Ptr object)
{
    core_->log()->entryNew(Fwk::Log::info(), "TFSIOInterface::objectAdd - %s", path.pathString().c_str());

    ObjectPath prefix = path.prefix();
    ObjectPathComponent lastComponent = path.lastComponent();

    TFSObject::Ptr parentObj = core_->object(prefix);
    TFSDirectoryObject::Ptr parentDir = dynamic_cast <TFSDirectoryObject *> (parentObj.ptr());

    if(parentObj == NULL)
    {
        //can not get parent directory
        core_->log()->entryNew(Fwk::Log::info(), "TFSIOInterface::objectAdd - can not find prefix %s", prefix.pathString().c_str());
        throw Fwk::NameNotFoundException("TFSIOInterface::objectAdd");
    }

    //if(parentObj->type().value() != ObjectType::directory())
    if(parentDir.ptr() == NULL)
    {
        throw Fwk::UnexpectedTypeException("TFSIOInterface::objectAdd");
    }

    try
    {
        object->pathNew(path);
        core_->objectAdd(path, object);
        parentDir->entryNew(lastComponent);
    }
    catch (...)
    {
        throw;
    }    
}



tfs : tfs.o fuseInterface.o
	gcc -g `pkg-config fuse --libs` -o tfs tfs.o fuseInterface.o

tfs.o : tfs.c
	gcc -g -Wall `pkg-config fuse --cflags` -c tfs.c

fuseInterface.o : fuseInterface.c
	gcc -g -Wall `pkg-config fuse --cflags` -c fuseInterface.c

clean:
	rm tfs *.o


/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.

  gcc -Wall `pkg-config fuse --cflags --libs` hello.c -o hello
*/

#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>

//./hello  /testmnt/  -oallow_other -odefault_permissions -d

#include "../tfs/TFSWrapper.h"

static const char *hello_str = "Hello World!\n";
static const char *hello_path = "/hello";

static int hello_getattr(const char *path, struct stat *stbuf)
{
	int res = 0;

	memset(stbuf, 0, sizeof(struct stat));
	if (strcmp(path, "/") == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
        stbuf->st_uid = 1001;
        stbuf->st_gid = 1002;
	} else if (strcmp(path, hello_path) == 0) {
		stbuf->st_mode = S_IFREG | 0440;
		stbuf->st_nlink = 1;
		stbuf->st_size = strlen(hello_str);
        stbuf->st_uid = 1001;
        stbuf->st_gid = 1002;
	} else
		res = -ENOENT;

	return res;
}

static int hello_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			 off_t offset, struct fuse_file_info *fi)
{
	(void) offset;
	(void) fi;

	if (strcmp(path, "/") != 0)
		return -ENOENT;

	filler(buf, ".", NULL, 0);
	filler(buf, "..", NULL, 0);
	filler(buf, hello_path + 1, NULL, 0);

	return 0;
}

static int hello_open(const char *path, struct fuse_file_info *fi)
{
    struct fuse_context *fuseContext = NULL;

   
    fuseContext = fuse_get_context();

    printf("fuseContext->uid: %d\n", fuseContext->uid);
    printf("fuseContext->gid: %d\n", fuseContext->gid);

	if (strcmp(path, hello_path) != 0)
		return -ENOENT;

	if ((fi->flags & 3) != O_RDONLY)
		return -EACCES;

	return 0;
}

static int hello_read(const char *path, char *buf, size_t size, off_t offset,
		      struct fuse_file_info *fi)
{
	size_t len;
	(void) fi;
	if(strcmp(path, hello_path) != 0)
		return -ENOENT;

	len = strlen(hello_str);
	if (offset < len) {
		if (offset + size > len)
			size = len - offset;
		memcpy(buf, hello_str + offset, size);
	} else
		size = 0;

	return size;
}

static struct fuse_operations hello_oper = {
	.getattr	= hello_getattr,
	.readdir	= hello_readdir,
	.open		= hello_open,
	.read		= hello_read,
};


int fuseInit(int argc, char *argv[])
{
	return fuse_main(argc, argv, &hello_oper, NULL);
}




int tfswrapper_open(const char *rawPath, struct fuse_file_info *fi)
{
    struct fuse_context *fuseContext = NULL;

   
    fuseContext = fuse_get_context();

    printf("fuseContext->uid: %d\n", fuseContext->uid);
    printf("fuseContext->gid: %d\n", fuseContext->gid);

	if (strcmp(path, hello_path) != 0)
		return -ENOENT;

	if ((fi->flags & 3) != O_RDONLY)
		return -EACCES;

	return 0;
}


fileObj = Fwk::ptr_cast<TFSRegularFileObject, TFSObject>(handle->object());

if(fileObj.ptr() == NULL)
{
    core->log()->entryNew(Fwk::Log::warning(), "tfswrapper_write - cannot find object associated with handle");
    return -EINVAL; //fd is attached to an object which is unsuitable for writing. 
}


OperationResult TFSHandle::read(ReadOperation readOp)
{
    OperationResult result;
    TFSRegularFileObject::Ptr fileObj = NULL;

    fileObj = Fwk::ptr_cast<TFSRegularFileObject, TFSObject>(object_);

    if(fileObj.ptr() == NULL)
    {
        if(readOp.log().ptr())
            readOp.log()->entryNew(Fwk::Log::warning(), "TFSHandle::read - cannot find object associated with handle");

        throw Fwk::UnexpectedTypeException("TFSHandle::read");
    }

    //lock the file obj


    //do the read
    MemoryMapOption option(MemoryMapOption::mapRead(), readOp.offset(), readOp.length());

    U8 *srcBuffer = fileObj->mmap(option);

    if(srcBuffer == NULL)
    {
        if(readOp.log().ptr())
            readOp.log()->entryNew(Fwk::Log::warning(), "TFSHandle::read - cannot map file at offset 0xllx with length 0x%llx", readOp.offset(), readOp.length());

        throw Fwk::InternalException("TFSHandle::read");
    }

    memcpy(readOp.dstBuffer(), srcBuffer, readOp.length());

    //unlock the file obj

    result.bytesReadIs(readOp.length());

    return result;
}

OperationResult TFSHandle::write(WriteOperation writeOp)
{
    OperationResult result;
    TFSRegularFileObject::Ptr fileObj = NULL;

    fileObj = Fwk::ptr_cast<TFSRegularFileObject, TFSObject>(object_);

    if(fileObj.ptr() == NULL)
    {
        if(writeOp.log().ptr())
            writeOp.log()->entryNew(Fwk::Log::warning(), "TFSHandle::write - cannot find object associated with handle");

        throw Fwk::UnexpectedTypeException("TFSHandle::write");
    }

    //lock the file obj


    //do the write
    MemoryMapOption option(MemoryMapOption::mapWrite(), writeOp.offset(), writeOp.length());

    U8 *dstBuffer = fileObj->mmap(option);

    if(dstBuffer == NULL)
    {
        if(writeOp.log().ptr())
            writeOp.log()->entryNew(Fwk::Log::warning(), "TFSHandle::write - cannot map file at offset 0xllx with length 0x%llx", writeOp.offset(), writeOp.length());

        throw Fwk::InternalException("TFSHandle::write");
    }

    memcpy(dstBuffer, writeOp.srcBuffer(), writeOp.length());

    //unlock the file obj

    result.bytesWrittenIs(writeOp.length());

    return result;
}

memcpy(readOp->dstBuffer() + readOp->result()->bytesRead(), srcBuffer, intCount);
readOp->result()->bytesReadInc(intCount);



if(srcBuffer == NULL)
{
    if(readOp->log().ptr())
        readOp->log()->entryNew(Fwk::Log::warning(), "TFSRegularFileObject::handleReadIO - cannot get block 0x%llx", blockNumber);

    throw Fwk::InternalException("TFSRegularFileObject::handleReadIO");
}