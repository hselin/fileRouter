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



#if 0
/*
  gcc -Wall `pkg-config fuse --cflags --libs` fuseInterface.c -o fuseInterface
*/

#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <assert.h>

#include "tfs.h"
#include "../crypto/cryptoInterface.h"


//./hello  /testmnt/  -oallow_other -odefault_permissions -d
//./tfs  /testmnt/  -oallow_other -odefault_permissions -d
//fusermount -u /testmnt


static const char *hello_str = "Hello World!\n";
static const char *hello_path = "/hello";


static int fi_checkAccessPermission(tfsObjectPermissionInfoStruct *permissionInfo)
{
    return 0;
}

static int fi_processPath(const char *rawPath, char *processedPath)
{
    int status = 0;

    assert(rawPath);
    assert(processedPath);

    if((rawPath == NULL) || (processedPath == NULL))
    {
        return TFS_ERROR;
    }

    memset(processedPath, 0, TFS_PATH_MAX_LENGTH);

    status = snprintf(processedPath, TFS_PATH_MAX_LENGTH, "%s", rawPath);

    if(status >= TFS_PATH_MAX_LENGTH)
    {
        return TFS_ERROR;
    }

    return TFS_OK;
}

static int fi_createFileHandle(tfsObjectHeaderStruct *headerPtr, uint64_t *handle)
{
    
    //tell TFS to move object header to open
    if(TFSOpenObject(headerPtr) != TFS_OK)
    {
        tfsDbgPrint("INFO: fi_createFileHandle - TFSOpenObject\n");
        return -ENOENT; 
    }

    return TFS_OK;
}
///////////////////////////////////////////////////////////////



static int fi_getattr(const char *rawPath, struct stat *stbuf)
{
    int status = 0;
    char processedPath[TFS_PATH_MAX_LENGTH];
    tfsObjectHeaderStruct *headerPtr = NULL;

    if((rawPath == NULL) || (stbuf == NULL))
    {
        tfsDbgPrint("ERROR: fi_getattr - rawPath || stbuf is null\n");
        return -ENOENT;
    }

    if(fi_processPath(rawPath, processedPath) != TFS_OK)
    {
        tfsDbgPrint("ERROR: fi_getattr - fi_processPath\n");
        return -ENOENT; 
    }
    
    memset(stbuf, 0, sizeof(struct stat));


    headerPtr = TFSGetObjectHeaderByPath(processedPath);

    if(!headerPtr)
    {
        return -ENOENT;
    }
    else
    {
        if(headerPtr->type & TFS_OBJECT_TYPE_REGULAR_FILE)
        {
            stbuf->st_mode = S_IFREG;
            stbuf->st_nlink = 1;
            stbuf->st_size = headerPtr->size;
        }

        if(headerPtr->type & TFS_OBJECT_TYPE_DIRECTORY)
        {
            stbuf->st_mode = S_IFDIR;
            stbuf->st_nlink = 2;
        }

        //tfsDbgPrint("0x%llx\n", header.permissionInfo.permission & TFS_OBJECT_PERMISSION_UNIX_BITMAP);

        stbuf->st_mode |= (mode_t)(headerPtr->permissionInfo.permission & TFS_OBJECT_PERMISSION_UNIX_BITMAP);
        

        stbuf->st_uid = headerPtr->permissionInfo.uid;
        stbuf->st_gid = headerPtr->permissionInfo.gid;

        return 0;
    }
}




static int fi_opendir(const char *rawPath, struct fuse_file_info *fi)
{
    int status = 0;
    char processedPath[TFS_PATH_MAX_LENGTH];
    tfsObjectHeaderStruct *headerPtr = NULL;


    if((rawPath == NULL) || (fi == NULL))
    {
        tfsDbgPrint("ERROR: fi_opendir - parameter is null\n");
        return -ENOENT;
    }

    if(fi_processPath(rawPath, processedPath) != TFS_OK)
    {
        tfsDbgPrint("ERROR: fi_opendir - fi_processPath\n");
        return -ENOENT; 
    }

    headerPtr = TFSGetObjectHeaderByPath(processedPath);

    if(!headerPtr)
    {
        return -ENOENT;
    }
    else
    {

        if((headerPtr->type & TFS_OBJECT_TYPE_DIRECTORY) == 0)
        {
            tfsDbgPrint("ERROR: fi_opendir - not a directory object\n");
            return -ENOENT; 
        }

        //access permission check
        if(fi_checkAccessPermission(&headerPtr->permissionInfo))
        {
            tfsDbgPrint("INFO: fi_opendir - fi_checkAccessPermission not 0\n");
            return -ENOENT; 
        }

        //generate file handle
        if(fi_createFileHandle(headerPtr, &fi->fh) != TFS_OK)
        {
            tfsDbgPrint("INFO: fi_opendir - fi_createFileHandle\n");
            return -ENOENT; 
        }

        return 0;
    }
}










































static int fi_readdir(const char *rawPath, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
    int status = 0;
    char processedPath[TFS_PATH_MAX_LENGTH];
    tfsObjectHeaderStruct header;

#if 0
    if((rawPath == NULL) || (buf == NULL) || (filler == NULL) || (fi == NULL))
    {
        tfsDbgPrint("ERROR: fi_readdir - parameter is null\n");
        return -ENOENT;
    }


    if(fi_processPath(rawPath, processedPath) != TFS_OK)
    {
        tfsDbgPrint("ERROR: fi_readdir - fi_processPath\n");
        return -ENOENT; 
    }

    status = TFSGetObjectHeader(processedPath, &header);
#endif
    
    if((buf == NULL) || (filler == NULL) || (fi == NULL))
    {
        tfsDbgPrint("ERROR: fi_readdir - parameter is null\n");
        return -ENOENT;
    }

    status = TFSGetObjectHeaderByFileHandle(fi->fh, &header);

    if(status != TFS_OK)
    {
        return -ENOENT;
    }
    else
    {
        //tfsAVLStruct *directoryEntriesAttribute = NULL;
        LIST_HEAD(attributeListHead);
        struct list_head *listEntry, *tempEntry = NULL;
        tfsAVLStruct *avlPtr = NULL;
        uint64_t numEntries = 0;
        uint64_t entryIndex = 0;
        tfsObjectAttributeValueDirectoryEntryStruct *directoryEntryList = NULL;
        //tfsObjectAttributeValueDirectoryEntryStruct *dirEntry = NULL;


#if 0
        if((header.type & TFS_OBJECT_TYPE_DIRECTORY) == 0)
        {
            tfsDbgPrint("ERROR: fi_readdir - not a directory object\n");
            return -ENOENT; 
        }

        //access permission check
        if(fi_checkAccessPermission(&header.permissionInfo))
        {
            tfsDbgPrint("INFO: fi_readdir - fi_checkAccessPermission not 0\n");
            return -ENOENT; 
        }
#endif

        status = TFSGetObjectAttribute(header.wwn, TFS_OBJECT_ATTRIBUTE_ID_DIRECTORY_ENTRIES, &attributeListHead);

        if(status != TFS_OK)
        {
            tfsDbgPrint("INFO: fi_readdir - TFSGetObjectAttribute\n");
            return -ENOENT;
        }

        assert(!list_empty(&attributeListHead));

        //default current and parent directory entries
        {
            filler(buf, ".", NULL, 0);
            filler(buf, "..", NULL, 0);
        }

        list_for_each_safe(listEntry, tempEntry, &attributeListHead)
        {
            avlPtr = list_entry(listEntry, tfsAVLStruct, list);
            assert(avlPtr);
            
            assert(avlPtr->attributeID == TFS_OBJECT_ATTRIBUTE_ID_DIRECTORY_ENTRIES);

            assert(avlPtr->length >= sizeof(tfsObjectAttributeValueDirectoryEntryStruct));
            assert((avlPtr->length % sizeof(tfsObjectAttributeValueDirectoryEntryStruct)) == 0);

            directoryEntryList = (tfsObjectAttributeValueDirectoryEntryStruct *) avlPtr->value;

            numEntries = (avlPtr->length / sizeof(tfsObjectAttributeValueDirectoryEntryStruct));

            for(entryIndex = 0; entryIndex < numEntries; entryIndex++)
            {                
                status = filler(buf, directoryEntryList[entryIndex].name, NULL, 0);
                assert(status == 0);

                if(status != 0)
                {
                    tfsDbgPrint("ERROR: fi_readdir - filler\n");
                    break;
                }
            }

            //remove entry and free avl
            list_del(listEntry);
            free(avlPtr);
        }

        assert(list_empty(&attributeListHead));

        return 0;
    }
}







static int fi_open(const char *path, struct fuse_file_info *fi)
{
    struct fuse_context *fuseContext = NULL;

   
    fuseContext = fuse_get_context();


    printf("\n\n!fi_open %s!\n\n", path);
    printf("fuseContext->uid: %d\n", fuseContext->uid);
    printf("fuseContext->gid: %d\n", fuseContext->gid);

    if (strcmp(path, hello_path) != 0)
        return -ENOENT;

    if ((fi->flags & 3) != O_RDONLY)
        return -EACCES;

    return 0;
}

static int fi_read(const char *path, char *buf, size_t size, off_t offset,
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

static struct fuse_operations fi_operations = {
    .getattr    = fi_getattr,
    .readdir    = fi_readdir,
    .open        = fi_open,
    .read        = fi_read,
    .opendir    = fi_opendir,
    .flag_nullpath_ok = 1,
};

int main(int argc, char *argv[])
{
    return fuse_main(argc, argv, &fi_operations, NULL);
}
#endif
