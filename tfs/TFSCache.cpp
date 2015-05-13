#include <string>
#include <errno.h>

//#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "TFSValueTypes.h"
#include "TFSCache.h"

#include "TFSCore.h"


namespace TFS
{

using namespace std;

/*
  ==========================================================
  Implementation for TFSCache
  ==========================================================
*/




#if 0
#define TFS_BLOCK_HEADER_SIZE   (4 * 1024)

int TFSCache::block(BlockID id, U8 *buffer)
{
    int returnStatus = 0;
    string dirString = core_->configInterface()->cacheLocation().value() + id.prefix().c_str() + "/";
    string fullPathString = dirString + id.body();

    core_->log()->entryNew(Fwk::Log::info(), "TFSCache::block - %s", fullPathString.c_str());

    FILE *blockFile = fopen(fullPathString.c_str(), "rb");

    if(blockFile)
    {
        if(fseek(blockFile, TFS_BLOCK_HEADER_SIZE, SEEK_SET) != 0)
        {
            returnStatus = -1;
            goto block_end;
        }

        size_t amountRead = fread(buffer, 1, core_->configInterface()->blockSize(), blockFile);

        if(amountRead != core_->configInterface()->blockSize())
        {
            returnStatus = -1;
        }
    }
    else
    {
        returnStatus = -1;
    }

block_end:

    if(blockFile)
        fclose(blockFile);

    return returnStatus;
}

int TFSCache::blockIs(BlockID id, U8 *buffer)
{
    int returnStatus = 0;
    string dirString = core_->configInterface()->cacheLocation().value() + id.prefix().c_str() + "/";
    string fullPathString = dirString + id.body();


    core_->log()->entryNew(Fwk::Log::info(), "TFSCache::blockIs - %s", fullPathString.c_str());

    FILE *blockFile = fopen(fullPathString.c_str(), "wb");

    if(blockFile)
    {
        if(fseek(blockFile, TFS_BLOCK_HEADER_SIZE, SEEK_SET) != 0)
        {
            returnStatus = -1;
            goto block_is_end;
        }

        size_t amountWrote = fwrite(buffer, 1, core_->configInterface()->blockSize(), blockFile);
        
        if(amountWrote != core_->configInterface()->blockSize())
        {
            returnStatus = -1;
        }
    }
    else
    {
        returnStatus = -1;
    }

block_is_end:

    if(blockFile)
        fclose(blockFile);

    return returnStatus;
}

void TFSCache::objectCacheNew(BlockID id)
{
    int status = 0;
    struct stat st;

    string dirString = core_->configInterface()->cacheLocation().value() + id.prefix().c_str() + "/";

    if(stat(dirString.c_str(), &st) == 0)
    {
        if(S_ISDIR(st.st_mode))
            return;
        
        throw Fwk::InternalException("TFSCore::objectCacheNew");
    }
    else
    {
        status = mkdir(dirString.c_str(), S_IRWXU);

        if(status != 0)
            throw Fwk::InternalException("TFSCore::objectCacheNew");
    }
}
#endif

} //namespace
