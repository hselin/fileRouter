#include <string>
#include <errno.h>

//#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "TFSValueTypes.h"
#include "TFSCore.h"

#include "TFSBlockStore.h"

namespace TFS
{

using namespace std;

/*
  ==========================================================
  Implementation for TFSBlockStore
  ==========================================================
*/

BlockOperationStatus TFSBlockStore::block(BlockID bid, U8 **buffer)
{
    BlockOperationStatus status;

    core_->log()->entryNew(Fwk::Log::info(), "TFSBlockStore::block %s", bid.hexString().c_str());

    return status;
}

BlockOperationStatus TFSBlockStore::blockNew(BlockID bid, U8 *buffer)
{
    BlockOperationStatus status;

    core_->log()->entryNew(Fwk::Log::info(), "TFSBlockStore::blockNew %s", bid.hexString().c_str());

    return status;
}

/*
  ==========================================================
  Implementation for TFSLocalFileSystemBlockStore
  ==========================================================
*/

BlockOperationStatus TFSLocalFileSystemBlockStore::block(BlockID bid, U8 **buffer)
{
    BlockOperationStatus status;

    core_->log()->entryNew(Fwk::Log::info(), "TFSLocalFileSystemBlockStore::block %s", bid.hexString().c_str());

    string blockDirPath = blockIDToDirPath(bid);
    string userDataFilePath = blockDirPath + blockStoreRoot_.pathDelimiter() + "user.dat";     

#if 0
    //check if block exist
    if(!Fwk::fileExist(userDataFilePath))
    {
        //if block does not existed then return error
        status.successIs(false);
        return status;
    }
#endif

    *buffer = Fwk::fileMap(userDataFilePath, core_->configInterface()->blockSize());

    if(*buffer)
    {
        //mapping a success
        return status;
    }


    status.successIs(false);
    return status;
}

string TFSLocalFileSystemBlockStore::blockIDToDirPath(BlockID bid)
{
    string subDirPath = "";
    string bidHexString = bid.hexString();
    unsigned int i = 0;

    DBG_ASSERT((bidHexString.size() % 2) == 0);

    while(1)
    {
        subDirPath.append(bidHexString.substr(i, 2));
        i+=2;
        
        if(i >= bidHexString.size())
            break;
        
        subDirPath.append(1, blockStoreRoot_.pathDelimiter());
    }

    return blockStoreRoot_.pathString() + subDirPath;
}

BlockOperationStatus TFSLocalFileSystemBlockStore::blockNew(BlockID bid, U8 *buffer)
{
    BlockOperationStatus status;

    core_->log()->entryNew(Fwk::Log::info(), "TFSLocalFileSystemBlockStore::blockNew %s", bid.hexString().c_str());
    
    string blockDirPath = blockIDToDirPath(bid);
    string userDataFilePath = blockDirPath + blockStoreRoot_.pathDelimiter() + "user.dat";    
    string metaDataFilePath = blockDirPath + blockStoreRoot_.pathDelimiter() + "meta.dat";

    core_->log()->entryNew(Fwk::Log::info(), "TFSLocalFileSystemBlockStore::blockNew blockDirPath %s", blockDirPath.c_str());
    core_->log()->entryNew(Fwk::Log::info(), "TFSLocalFileSystemBlockStore::blockNew userDataFilePath %s", userDataFilePath.c_str());


    //try creating block dir path
    if(!Fwk::createDirPath(blockDirPath, blockStoreRoot_.pathDelimiter()))
    {
        core_->log()->entryNew(Fwk::Log::warning(), "TFSLocalFileSystemBlockStore::blockNew createDirPath %s failed", blockDirPath.c_str());
        status.successIs(false);
        return status;
    }
    
    //check if block already existed

    if(Fwk::fileExist(userDataFilePath))
    {
        //if block already existed then update metadata
        
        
        core_->log()->entryNew(Fwk::Log::info(), "TFSLocalFileSystemBlockStore::blockNew %s already existed", userDataFilePath.c_str());

        return status;
    }

    //new block

    if(Fwk::fileWrite(metaDataFilePath, , ))
    {

    }


    if(Fwk::fileWrite(userDataFilePath, buffer, core_->configInterface()->blockSize()))
    {
        //write new block success
        core_->log()->entryNew(Fwk::Log::info(), "TFSLocalFileSystemBlockStore::blockNew fileWrite %s good", userDataFilePath.c_str());
        return status;
    }

    core_->log()->entryNew(Fwk::Log::warning(), "TFSLocalFileSystemBlockStore::blockNew fileWrite %s failed", userDataFilePath.c_str());

    status.successIs(false);

    return status;
}





TFSLocalFileSystemBlockStore::Ptr TFSLocalFileSystemBlockStore::TFSLocalFileSystemBlockStoreNew(string name, LocalFileSystemPath blockStoreRoot, TFSCore::Ptr core)
{
    return new TFSLocalFileSystemBlockStore(name, blockStoreRoot, core);
}

} //namespace
    