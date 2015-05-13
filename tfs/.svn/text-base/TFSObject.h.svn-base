#ifndef TFS_OBJECT_H
#define TFS_OBJECT_H

#include <string>
#include <vector>

#include "../common/Ptr.h"
#include "../common/PtrInterface.h"


#include "TFSValueTypes.h"
#include "TFSOperation.h"
//#include "../common/ConcurrentQueue.h"

namespace TFS {

using namespace std;

class TFSCore;

class TFSObject : public Fwk::PtrInterface <TFSObject>
{
public:
    typedef Fwk::Ptr <TFSObject const> PtrConst;
    typedef Fwk::Ptr <TFSObject> Ptr;

    //accessors
    ObjectVersion    version() const        { return version_; }
    WorldWideName    wwn() const            { return wwn_; }
    ObjectType       type() const           { return type_; }
    ObjectPermission permission() const     { return permission_; }
    ObjectSize       size() const           { return size_; }
 
    bool path(ObjectPath path) const;

    bool removeObjectOnClose() const        { return removeObjectOnClose_; }

    BlockID blockID(U64 blockNumber) const;

    //mutators
    void permissionIs(ObjectPermission permission);
    void pathNew(ObjectPath path);
    void removeObjectOnCloseIs(bool remove);
    void blockIDIs(U64 blockNumber, BlockID bid);


    void coreIs(Fwk::Ptr <TFSCore> core);

    //creators
    static TFSObject::Ptr TFSObjectNew(U64 type);

protected:
    //friend class TFSCache;

    /*
    static const U64 TFSBlockSizeShift_ = 20;
    static const U64 TFSBlockSize_ = 1 << TFSBlockSizeShift_;  //0x100000 (1MB)
    static const U64 TFSBlockOffsetMask_ = (TFSBlockSize_ - 1); //0xFFFFF;
    static const U64 TFSBlockSizeMask_ = ~(TFSBlockOffsetMask_);
    */

    ObjectVersion    version_;
    WorldWideName    wwn_;
    ObjectType       type_;
    ObjectPermission permission_;
    ObjectSize       size_;

    vector<ObjectPath> path_;

    bool removeObjectOnClose_;

    map<U64, BlockID> blockMap_;

    Fwk::Ptr <TFSCore>  core_;

    //constructors
    TFSObject(U64 type) : type_(type), permission_(1000, 1000, 0x1FF), removeObjectOnClose_(false) {}
   
}; //TFSObject

class TFSRegularFileObject : public TFSObject
{
public:
    typedef Fwk::Ptr <TFSRegularFileObject const> PtrConst;
    typedef Fwk::Ptr <TFSRegularFileObject> Ptr;

    //accessors

    //mutators
    U8 *mmap(MemoryMapOption option);

    void readNew(TFSReadOperation::Ptr readOp);
    void writeNew(TFSWriteOperation::Ptr writeOp);

    //void queueIO(TFSOperation::Ptr op);
    //TFSOperation::Ptr popIO();
    //void processIO();
    //void handleReadIO(TFSReadOperation::Ptr readOp);
    //void handleWriteIO(TFSWriteOperation::Ptr writeOp);
  

    //creators
    static TFSRegularFileObject::Ptr TFSRegularFileObjectNew();

protected:
    //vector<TFSOperation::Ptr> ioQueue_;
    //Fwk::ConcurrentQueue <TFSOperation::Ptr> ioQueue_;    

    //helper functions
    int readBlock(U64 blockNumber, U8 *buffer, U64 offset, U64 length);
    int writeBlock(U64 blockNumber, U8 *buffer, U64 offset, U64 length);

    //constructors
    TFSRegularFileObject() : TFSObject(ObjectType::typeRegularFile()) {}
   
}; //TFSRegularFileObject

class TFSDirectoryObject : public TFSObject
{
public:
    typedef Fwk::Ptr <TFSDirectoryObject const> PtrConst;
    typedef Fwk::Ptr <TFSDirectoryObject> Ptr;

    //accessors
    ObjectPathComponent entry(U64 index) const;
    U64 entries() const { return entry_.size(); }
    bool entry(ObjectPathComponent component) const;
    vector<ObjectPathComponent> entry() const;

    //mutators
    void entryNew(ObjectPathComponent component);
    void entryDel(ObjectPathComponent component);

    //creators
    static TFSDirectoryObject::Ptr TFSDirectoryObjectNew();

protected:
    vector<ObjectPathComponent> entry_;

    //constructors
    TFSDirectoryObject() : TFSObject(ObjectType::typeDirectory()) {}
    
}; //TFSDirectoryObject

} //namespace
#endif