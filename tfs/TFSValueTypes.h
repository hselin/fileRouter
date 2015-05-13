#ifndef TFS_VALUETYPES_H
#define TFS_VALUETYPES_H

#include <string>
#include <stdio.h>

#include "../common/Types.h"
#include "../common/Exception.h"
#include "../common/Util.h"
#include "../common/Log.h"


namespace TFS
{
  
using namespace std;


/*
  ==========================================================
  Common objs
  ==========================================================
*/


class WorldWideName
{
public:
    //accessors
    string value() const;

    //mutators

    //constructors
    WorldWideName() : id_(counter_++) {}

    WorldWideName(const WorldWideName& wwn) { id_ = wwn.id_; }

protected:
    string value_;
    
    U64 id_;

    static U64 counter_;
};


class ResourceLocation
{
public:
    //accessors
    string value() const { return value_; }

    bool equal(ResourceLocation *rl) const;

    //mutators

    //constructors
    ResourceLocation() : value_("") {}
    ResourceLocation(string value) : value_(value) {}

protected:
    string value_;
};


class LocalFileSystemPath
{
public:
    //accessors
    static U64 pathMaxLength()        { return pathMaxLength_; }
    static char pathDelimiter()       { return pathDelimiter_; }

    string pathString() const         { return pathString_; }

    bool absolutePath() const;
    bool root() const;

    //mutators

    //constructors
    LocalFileSystemPath(const char *rawPath)
    {
        if(rawPath == NULL)
        {
            throw Fwk::InternalException("LocalFileSystemPath - rawPath is NULL");
        }

        //strlen does not include ending NULL
        pathString_.assign(rawPath, MIN(pathMaxLength_, strlen(rawPath)));
    }

    LocalFileSystemPath()
    {
        pathString_.assign(1, pathDelimiter_);
    }

protected:
    static const U64 pathMaxLength_ = 1024;
    static const char pathDelimiter_ = '/';

    string pathString_;
};

/*
  ==========================================================
  TFSObj objs
  ==========================================================
*/

class ObjectPathComponent
{
public:
    //accessors
    U64 componentMaxLength() const { return componentMaxLength_; }
    string componentString() const { return componentString_; }
    bool equal(ObjectPathComponent *component) const;

    //mutators

    //constructors
    ObjectPathComponent(const char *rawComponent)
    {
        if(rawComponent == NULL)
        {
            throw Fwk::InternalException("ObjectPathComponent - rawComponent is NULL");
        }

        componentString_.assign(rawComponent, componentMaxLength_);
    }

protected:
    static const U64 componentMaxLength_ = 256;

    string componentString_;
};

class ObjectPath
{
public:
    //accessors
    static U64 objectPathMaxLength()        { return objectPathMaxLength_; }
    string pathString() const               { return pathString_; }

    bool absolutePath() const;
    bool root() const;

    bool equal(ObjectPath *path) const;
    bool lessThan(ObjectPath *path) const;


    //mutators
    ObjectPath prefix();
    ObjectPathComponent lastComponent();

    //constructors
    ObjectPath(const char *rawPath)
    {
        if(rawPath == NULL)
        {
            throw Fwk::InternalException("ObjectPath - rawPath is NULL");
        }

        //strlen does not include ending NULL
        pathString_.assign(rawPath, MIN(objectPathMaxLength_, strlen(rawPath)));
    }

    ObjectPath()
    {
        pathString_.assign(1, pathDelimiter_);
    }

protected:
    static const U64 objectPathMaxLength_ = 1024;
    static const char pathDelimiter_ = '/';

    string pathString_;
};


class ObjectType
{
public:
    //accessors
    static U64 typeRegularFile()  { return typeRegularFile_; }
    static U64 typeDirectory()    { return typeDirectory_; }

    U64 value() const          { return value_; }

    bool directory() const;
    bool regularFile() const;

    //constructors
    ObjectType(U64 value) : value_(value) {}
    ObjectType() : value_(typeInvalid_) {}

protected:
    static const U64 typeInvalid_     = 0x0;
    static const U64 typeRegularFile_ = 0x1;
    static const U64 typeDirectory_   = 0x2;

    U64 value_;
};


class ObjectPermission
{
public:
    //accessors
    U64 uid() const             { return uid_; }
    U64 gid() const             { return gid_; }
    U64 access() const          { return access_; }

    U16 unixPermission() const;

    bool equal(ObjectPermission *permission) const;


    //mutators
    void unixPermissionIs(U16 up);

    //constructors
    ObjectPermission(U64 uid, U64 gid, U64 access) : uid_(uid), gid_(gid), access_(access) {}
    ObjectPermission() : uid_(0), gid_(0), access_(0) {}

protected:
    U64 uid_;
    U64 gid_;

    /*
    [0 - 15]  unix permission bits
    [16 - 63] reserved
    */
    U64 access_;
};



class ObjectSize
{
public:
    //accessors
    U64 value() const          { return value_; }

    //constructors
    ObjectSize(U64 value) : value_(value) {}
    ObjectSize() : value_(0) {}

protected:
    U64 value_;
};


class ObjectVersion
{
public:
    //accessors
    U64 value() const          { return value_; }

    //constructors
    ObjectVersion(U64 value) : value_(value) {}
    ObjectVersion() : value_(0) {}

protected:
    U64 value_;
};



/*
  ==========================================================
  IO objs
  ==========================================================
*/

class HandleID
{
public:
    //accessors
    U64 value() const          { return value_; }

    bool lessThan(HandleID *id) const;

    //mutators

    //constructors
    HandleID() : value_(counter_++) {}
    HandleID(U64 value) : value_(value) {}

    HandleID(const HandleID& hi) { value_ = hi.value_; }

protected:
    U64 value_;

    static U64 counter_;
};

class ProcessInfo
{
public:
    //accessors
    U64 uid() const             { return uid_; }
    U64 gid() const             { return gid_; }
    U64 pid() const             { return pid_; }

    //constructors
    ProcessInfo(U64 uid, U64 gid, U64 pid) : uid_(uid), gid_(gid), pid_(pid) {}
    ProcessInfo() : uid_(0), gid_(0), pid_(0) {}

protected:
    U64 uid_;
    U64 gid_;
    U64 pid_;
};

class OpenFlag
{
public:
    //accessors
    static U64 flagNone()      { return flagNone_; }
    static U64 flagCreate()    { return flagCreate_; }
    static U64 flagTrunc()     { return flagTrunc_; }
    static U64 flagAppend()    { return flagAppend_; }

    U64 value() const          { return value_; }

    bool truncate() const;
    bool append() const;

    //mutators
    void valueIs(U64 value);
    void add(U64 flag);

    //constructors
    OpenFlag(U64 value) : value_(value) {}
    OpenFlag() : value_(flagNone_) {}

protected:
    static const U64 flagNone_        = 0x0;
    static const U64 flagCreate_      = 0x1;
    static const U64 flagTrunc_       = 0x2;
    static const U64 flagAppend_      = 0x4;

    U64 value_;
};



/*
  ==========================================================
  Block objs
  ==========================================================
*/

class BlockID
{
public:
    //accessors
    string hexString() const; //{ return hexString_; }
    bool defaultID() const   { return defaultID_; }
    //U8 *byteArray() const   { return byteArray_; }

    bool lessThan(BlockID *bid) const;
    
    //mutators

    //constructors
    BlockID() : defaultID_(true) {}
    BlockID(U8 *blockBuffer, U64 blockSize);

protected:
    U8 byteArray_[32];
    //string hexString_;
    bool defaultID_;
};



/*
  ==========================================================
  Block store objs
  ==========================================================
*/

class BlockStoreType
{
public:
    //accessors
    static U64 typeLocalFileSystem()  { return typeLocalFileSystem_; }

    U64 value() const          { return value_; }

    bool directory() const;
    bool regularFile() const;

    //constructors
    BlockStoreType(U64 value) : value_(value) {}
    BlockStoreType() : value_(typeInvalid_) {}

protected:
    static const U64 typeInvalid_         = 0x0;
    static const U64 typeLocalFileSystem_ = 0x1;

    U64 value_;
};

class BlockStoreStatus
{
public:
    //accessors
    U64 status() const      { return status_; }
    bool online() const     { return true; }

    //mutators

    //constructors
    BlockStoreStatus() : status_(0) {}

    BlockStoreStatus(const U64& status) : status_(status) {}

protected:
    U64 status_;
    //string statusString_;
};

class BlockOperationStatus
{
public:
    //accessors
    U64 value() const       { return value_; }
    bool success() const;

    //mutators
    void successIs(bool s);

    //constructors
    BlockOperationStatus() : value_(0) {}

    BlockOperationStatus(const U64& value) : value_(value) {}

protected:
    U64 value_;
    //string statusString_;
};




/*
  ==========================================================
  Other objs
  ==========================================================
*/




class MemoryMapOption
{
public:
    //accessors
    static U64 mapRead()      { return mapRead_; }
    static U64 mapWrite()     { return mapWrite_; }

    U64 option() const        { return option_; }

    bool read() const;
    bool write() const;

    //mutators

    //constructors
    MemoryMapOption() : option_(0), offset_(0), length_(0) {}
    MemoryMapOption(U64 option, U64 offset, U64 length) : option_(option), offset_(offset), length_(length) {}

protected:
    static const U64 mapRead_  = 1;
    static const U64 mapWrite_ = 2;

    U64 option_;
    U64 offset_;
    U64 length_;

    
};






/*
  ==========================================================
  Compare objs
  ==========================================================
*/



//comparison class for ObjectPath   
class ObjectPathComp : public binary_function<ObjectPath, ObjectPath, bool>
{
public:
    ObjectPathComp() {}

    bool operator()(ObjectPath a, ObjectPath b) const
    {
        return a.lessThan(&b);
    }
};


//comparison class for HandleID   
class HandleIDComp : public binary_function<HandleID, HandleID, bool>
{
public:
    HandleIDComp() {}

    bool operator()(HandleID a, HandleID b) const
    {
        return a.lessThan(&b);
    }
};

#if 1
//comparison class for BlockID   
class BlockIDComp : public binary_function<BlockID, BlockID, bool>
{
public:
    BlockIDComp() {}

    bool operator()(BlockID a, BlockID b) const
    {
        return a.lessThan(&b);
    }
};
#endif

} /* end namespace */

#endif
