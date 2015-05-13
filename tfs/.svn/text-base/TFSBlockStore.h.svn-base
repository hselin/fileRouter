#ifndef TFS_BLOCKSTORE_H
#define TFS_BLOCKSTORE_H

#include <string>
#include <vector>

#include "../common/Ptr.h"
#include "../common/PtrInterface.h"

#include "TFSValueTypes.h"
#include "TFSBlock.h"

namespace TFS {

using namespace std;

class TFSCore;

class TFSBlockStore : public Fwk::PtrInterface <TFSBlockStore>
{
public:
    typedef Fwk::Ptr <TFSBlockStore const> PtrConst;
    typedef Fwk::Ptr <TFSBlockStore> Ptr;


    //accessors
    string name() const                         { return name_; }
    BlockStoreStatus status() const             { return status_; }

    //static inline OperationType error()                { return readOp__; }
    //static inline OperationType writeOp()               { return writeOp__; }    


    //mutators
    virtual BlockOperationStatus block(BlockID bid, U8 **buffer); //get a block
    virtual BlockOperationStatus blockNew(BlockID bid, U8 *buffer); //create a new block


    //creators
    static TFSBlockStore::Ptr TFSBlockStoreNew();

protected:
    string name_;
    BlockStoreType   type_;
    Fwk::Ptr <TFSCore> core_;
    BlockStoreStatus status_;
    WorldWideName wwn_;  
    U64 layer_;
    U64 cost_;

    //constructors
    TFSBlockStore(string name, BlockStoreType type, Fwk::Ptr <TFSCore> core) : name_(name), type_(type), core_(core) {}
}; //TFSBlockStore


class TFSLocalFileSystemBlockStore : public TFSBlockStore
{
public:
    typedef Fwk::Ptr <TFSLocalFileSystemBlockStore const> PtrConst;
    typedef Fwk::Ptr <TFSLocalFileSystemBlockStore> Ptr;

    //accessors

    //mutators
    BlockOperationStatus block(BlockID bid, U8 **buffer); //get a block
    BlockOperationStatus blockNew(BlockID bid, U8 *buffer); //create a new block  

    //creators
    static TFSLocalFileSystemBlockStore::Ptr TFSLocalFileSystemBlockStoreNew(string name, LocalFileSystemPath blockStoreRoot, Fwk::Ptr <TFSCore> core);

protected:
    LocalFileSystemPath blockStoreRoot_;

    //helper functions
    string blockIDToDirPath(BlockID bid);

    //constructors
    TFSLocalFileSystemBlockStore(string name, LocalFileSystemPath blockStoreRoot, Fwk::Ptr <TFSCore> core) : TFSBlockStore(name, BlockStoreType::typeLocalFileSystem(), core), blockStoreRoot_(blockStoreRoot) {}
   
}; //TFSRegularFileObject

} //namespace

#endif