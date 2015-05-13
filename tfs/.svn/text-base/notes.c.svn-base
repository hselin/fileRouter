#if 0
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
#endif


#if 0
struct stat
{
    dev_t     st_dev;     /* ID of device containing file */
    ino_t     st_ino;     /* inode number */
    mode_t    st_mode;    /* protection */
    nlink_t   st_nlink;   /* number of hard links */
    uid_t     st_uid;     /* user ID of owner */
    gid_t     st_gid;     /* group ID of owner */
    dev_t     st_rdev;    /* device ID (if special file) */
    off_t     st_size;    /* total size, in bytes */
    blksize_t st_blksize; /* blocksize for filesystem I/O */
    blkcnt_t  st_blocks;  /* number of blocks allocated */
    time_t    st_atime;   /* time of last access */
    time_t    st_mtime;   /* time of last modification */
    time_t    st_ctime;   /* time of last status change */
};

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
#endif

hash((uint8_t *)processedPath, TFS_PATH_MAX_LENGTH, pathHash, TFS_HASH_SIZE);
uint8_t pathHash[TFS_HASH_SIZE];

#if 0
    if (strcmp(rawPath, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
        stbuf->st_uid = 1001;
        stbuf->st_gid = 1002;
    } else if (strcmp(rawPath, hello_path) == 0) {
        stbuf->st_mode = S_IFREG | 0440;
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen(hello_str);
        stbuf->st_uid = 1001;
        stbuf->st_gid = 1002;
    } else 
        return -ENOENT;

    return 0;
#endif

#if 0
    (void) offset;
    (void) fi;

    printf("\n\n!fi_readdir %s!\n\n", rawPath);
    if(rawPath==NULL)
    {
        printf("\n\n!fi_readdir rawPath is NULL!\n\n");
    }

    if (strcmp(rawPath, "/") != 0)
        return -ENOENT;

    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    filler(buf, hello_path + 1, NULL, 0);
    return 0;
#endif

//dirEntry = (tfsObjectAttributeValueDirectoryEntryStruct *) avlPtr->value.byteArrayVal;


#if 0
int TFSGetObjectHeader(uint64_t handle, tfsObjectHeaderStruct *header)
{
    int status = 0;

    assert(header);

    if(header == NULL)
    {
        tfsDbgPrint("ERROR: TFSGetObjectHeader - parameter is null\n");
        return TFS_ERROR;
    }

    memset(header, 0, sizeof(tfsObjectHeaderStruct));

    TFSGenerateAlias(path, TFS_PATH_MAX_LENGTH, alias, TFS_ALIAS_SIZE);

    status = TFSLookupObjectHeaderByAlias(alias, header);

    if(status != TFS_OK)
    {
        tfsDbgPrint("ERROR: TFSGetObjectHeader - TFSLookupObjectHeader(%s)\n", path);
        return TFS_ERROR;
    }  

    return TFS_OK;
}
#endif







#pragma once
#ifndef TFS_H
#define TFS_H

#include <stdint.h>

#include "../common/list.h"

//(include trailing NULL)
#define TFS_PATH_MAX_LENGTH                 (1024)
#define TFS_OBJECT_NAME_MAX_LENGTH          (256)

#define TFS_OK                  (0)
#define TFS_ERROR               (-1)


//#define TFS_DBG_PRINT(fmt, ...) do { fprintf(stdout, fmt, __VA_ARGS__); } while (0)


void tfsDbgPrint(const char *format, ...);



/*
    Type
    [0 - 15]  object type
    [16 - 63] reserved
*/

#define TFS_OBJECT_TYPE_REGULAR_FILE        (0x1)
#define TFS_OBJECT_TYPE_DIRECTORY           (0x2)


/*
    permission
    [0 - 15]  unix permission bits
    [16 - 63] reserved
*/
#define TFS_OBJECT_PERMISSION_UNIX_BITMAP   (0xFFFF)

typedef struct{
    uint64_t uid;
    uint64_t gid;
    uint64_t permission;
} tfsObjectPermissionInfoStruct;

typedef struct{
    uint64_t aTime;
    uint64_t mTime;
    uint64_t cTime;
} tfsObjectAccessTimeInfoStruct;

typedef struct{
    uint64_t wwn;
    uint64_t type;
    uint64_t size;
    tfsObjectPermissionInfoStruct permissionInfo;
    tfsObjectAccessTimeInfoStruct accessTimeInfo;
} tfsObjectHeaderStruct;



typedef struct{
    tfsObjectHeaderStruct header;
} tfsObjectStruct;


typedef struct{    
    uint64_t attributeID;
    struct list_head list;
    uint64_t length;
    uint8_t value[0];
} tfsAVLStruct;


/*
union {
    uint64_t u64Val;
    void *ptrVal;
    uint8_t byteArrayVal[0];
} value;
*/

//attribute
typedef struct{
    char name[TFS_OBJECT_NAME_MAX_LENGTH];
} tfsObjectAttributeValueDirectoryEntryStruct;


#define TFS_OBJECT_ATTRIBUTE_ID_DIRECTORY_ENTRIES       (0x10000)








#define TFS_ALIAS_SIZE               (32)














int TFSGetObjectHeader(char *path, tfsObjectHeaderStruct *header);
int TFSGetObjectAttribute(uint64_t objWWN, uint64_t attributeID, struct list_head *listHead);


















#if 0
/*

    TFS_Element


    tcp connection
        packets <---> blocks
*/

class TFS_File
{
    char name[256];

};

class TFS_DataEncryption
{
    uint8_t key[32];
};


//multiple of 128 bits
class TFS_DataUnit
{

public:
    //header
    uint8_t hash[32];
    

    //data
    uint8_t data[256 * 1024];

};
#endif

#endif

































#if 0

class TFS_Flow_Name
{
    private:
        string name;

    public:

};

class TFS_Flow
{

private:
    TFS_Flow_Name flowName;    

    //hash of hashes?

    
};


class TFS_Packet
{
}


class TFS_Packet
{
}

#endif



#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

#include "tfs.h"





static const char *hello_str = "Hello World!\n";
static const char *hello_path = "/hello";


void tfsDbgPrint(const char *format, ...)
{
    va_list ap;
    va_start(ap, format);

    vfprintf(stdout, format, ap);
}


int TFSLookupObjectInDB(uint8_t *alias, tfsObjectHeaderStruct *header)
{
    assert(alias);
    assert(header);

    return TFS_ERROR;
}

int TFSLookupObjectInCore(uint8_t *alias, tfsObjectHeaderStruct *header)
{
    assert(alias);
    assert(header);

    //btree or hash


    if(*alias == 0x1)
    {
        header->type = TFS_OBJECT_TYPE_DIRECTORY;
        header->permissionInfo.uid = 1000;
        header->permissionInfo.gid = 1000;
        header->permissionInfo.permission = TFS_OBJECT_PERMISSION_UNIX_BITMAP & 0x1FF;
        return TFS_OK;
    }

    if(*alias == 0x2)
    {
        header->type = TFS_OBJECT_TYPE_REGULAR_FILE;
        header->permissionInfo.uid = 1000;
        header->permissionInfo.gid = 1000;
        header->permissionInfo.permission = TFS_OBJECT_PERMISSION_UNIX_BITMAP & 0x1FF;
        header->size = strlen(hello_str);
        return TFS_OK;
    }

    return TFS_ERROR;
}

void TFSGenerateAlias(char *path, uint32_t pathLength, uint8_t *alias, uint32_t aliasLength)
{
    assert(path);
    assert(alias);


    if (strcmp(path, "/") == 0)
    {
        memset(alias, 0x1, aliasLength);

        return;
    }
    
    if (strcmp(path, "/file_0") == 0)
    {
        memset(alias, 0x2, aliasLength);
        return;
    }

    if (strcmp(path, "/file_1") == 0)
    {
        memset(alias, 0x2, aliasLength);
        return;
    }

    memset(alias, 0x3, aliasLength);

    return;
}

int TFSLookupObjectHeaderByAlias(uint8_t *alias, tfsObjectHeaderStruct *header)
{
    assert(alias);
    assert(header);

    //lookup in memory first
    if(TFSLookupObjectInCore(alias, header) == TFS_OK)
    {
        //got it

        return TFS_OK;
    }

    //lookup in db...
    if(TFSLookupObjectInDB(alias, header) == TFS_OK)
    {
        //got it

        return TFS_OK;
    } 
    
    return TFS_ERROR;
}





/*
    1. lookup object header in cache
       return if found
    2. lookup object header in opened object list
       return if found
    3. lookup obj in db
        add to cache
        return obj header
*/



int TFSGetObjectHeader(char *path, tfsObjectHeaderStruct *header)
{
    int status = 0;
    uint8_t alias[TFS_ALIAS_SIZE];

    assert(path);
    assert(header);

    if((alias == NULL) || (header == NULL))
    {
        //tfsDbgPrint("ERROR: TFSGetObjectHeader - path || header is null\n");
        return TFS_ERROR;
    }

    memset(header, 0, sizeof(tfsObjectHeaderStruct));
    memset(alias, 0, sizeof(alias));

    TFSGenerateAlias(path, TFS_PATH_MAX_LENGTH, alias, TFS_ALIAS_SIZE);

    status = TFSLookupObjectHeaderByAlias(alias, header);

    if(status != TFS_OK)
    {
        //tfsDbgPrint("ERROR: TFSGetObjectHeader - TFSLookupObjectHeader(%s)\n", path);
        return TFS_ERROR;
    }  

    return TFS_OK;
}


tfsObjectHeaderStruct *TFSGetObjectHeaderByPath(char *path)
{
    tfsObjectHeaderStruct *headerPtr = NULL;

    //look up in cache
    TFSLookupObjectInCache();

    //look up in opened object list


    //look up in db


    return headerPtr;
}

int TFSOpenObject(tfsObjectHeaderStruct *header)
{

    return TFS_OK;
}



int TFSGetObjectAttribute(uint64_t objWWN, uint64_t attributeID, struct list_head *listHeadPtr)
{
    tfsAVLStruct *avlPtr = NULL;
    uint64_t numEntries, entryIndex = 0;
    tfsObjectAttributeValueDirectoryEntryStruct *directoryEntryList = NULL;

    assert(listHeadPtr);

    if(listHeadPtr == NULL)
    {
        tfsDbgPrint("ERROR: TFSGetObjectAttribute - listHeadPtr is null\n");
        return TFS_ERROR;
    }

    INIT_LIST_HEAD(listHeadPtr);

    numEntries = 2;

    avlPtr = calloc(1, sizeof(tfsAVLStruct) + (numEntries * sizeof(tfsObjectAttributeValueDirectoryEntryStruct)));
    assert(avlPtr);

    if(avlPtr == NULL)
    {
        tfsDbgPrint("ERROR: TFSGetObjectAttribute - calloc\n");
        return TFS_ERROR;
    }

    avlPtr->attributeID = TFS_OBJECT_ATTRIBUTE_ID_DIRECTORY_ENTRIES;
    INIT_LIST_HEAD(&avlPtr->list);
    avlPtr->length = numEntries * sizeof(tfsObjectAttributeValueDirectoryEntryStruct);
    directoryEntryList = (tfsObjectAttributeValueDirectoryEntryStruct *) avlPtr->value;

    for(entryIndex = 0; entryIndex < numEntries; entryIndex++)
    {
        snprintf(directoryEntryList[entryIndex].name, TFS_OBJECT_NAME_MAX_LENGTH, "file_%lld", entryIndex);
    }
    
    list_add_tail(&avlPtr->list, listHeadPtr);
    return TFS_OK;
}

//BlockOperationStatus opStatus(1);



    //check in read cache
    block = readCache(bid);

    if(block.ptr())
    {
        //found block
        return block;
    }

    //is write cache enabled?
#if 0
    //check in write cache
    block = writeCache(bid);

    if(block.ptr())
    {
        //found block
        return block;
    }
#endif

    //put data into read cache
    readCacheNew(bid, block);

    
    
    
    //check in read cache
    block = readCache(bid);

    if(block.ptr())
    {
        //found block
        return block;
    }

    //is write cache enabled?
#if 0
    {
        //check in write cache
        block = writeCache(bid);

        if(block.ptr())
        {
            //found block
            return block;
        }

        //write to cache...
    }
#endif


    //put data into read cache
    readCacheNew(bid, block);



#if 0
class BlockID
{
public:
    //accessors
    string prefix() const { return prefix_; }
    string body() const { return body_; }

    //mutators

    //constructors
    BlockID(string prefix, string body) : prefix_(prefix), body_(body) {}

protected:
    string prefix_;
    string body_;
};
#endif