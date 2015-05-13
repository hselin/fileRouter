#include <string>
#include <errno.h>

//#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "TFSValueTypes.h"
#include "TFSCore.h"

#include "TFSBlockStore.h"
#include "TFSBlockManager.h"


namespace TFS
{

using namespace std;

/*
  ==========================================================
  Implementation for TFSBlockManager
  ==========================================================
*/

void TFSBlockManager::onObjectAdd(TFSObject::Ptr obj)
{
    return;
}


//get a block
TFSBlock::Ptr TFSBlockManager::block(BlockID bid)
{
    TFSBlockStore::Ptr blockStore = NULL;
    U8 *blockBuffer = NULL;
    TFSBlock::Ptr block = NULL;

    block = cache(bid);

    if(block.ptr())
    {
        return block;
    }


    //get block from block storage layer
    if(!blockStorageLayerRead(bid, &blockBuffer, &blockStore))
    {
        //can't find block anywhere
        core_->log()->entryNew(Fwk::Log::warning(), "TFSBlockManager::block - block not found %s", bid.hexString().c_str());
        return NULL;
    }
    else
    {
        //alloc a new TFSBlock obj
        block = TFSBlockAlloc(bid, blockBuffer, false, blockStore);

        if(block)
        {
            //add to cache
            cacheNew(bid, block);
        }

        return block;
    }    
}


//create a new block
TFSBlock::Ptr TFSBlockManager::blockNew(BlockID bid, U8 *blockBuffer)
{
    TFSBlockStore::Ptr blockStore = NULL;
    TFSBlock::Ptr block = NULL;

    block = cache(bid);

    if(block.ptr())
    {
        return block;
    }

    //write block to block storage layer
    if(!blockStorageLayerWrite(bid, blockBuffer, &blockStore))
    {
        //can't store block anywhere
        core_->log()->entryNew(Fwk::Log::warning(), "TFSBlockManager::blockNew - cannot store block %s", bid.hexString().c_str());
        return NULL;
    }
    else
    {
        block = TFSBlockAlloc(bid, blockBuffer, true, blockStore);

        if(block)
        {
            /* To do: cache filling */
            cacheNew(bid, block);
        }

        return block;
    }
}



void TFSBlockManager::blockStoreAdd(TFSBlockStore::Ptr blockStore)
{
    if(blockStore.ptr() == NULL)
        return;


    blockStorageLayer_.push_back(blockStore);

    core_->log()->entryNew(Fwk::Log::info(), "TFSBlockManager::blockStoreAdd blockStorageLayer_.size() %d", blockStorageLayer_.size());
}

TFSBlock::Ptr TFSBlockManager::cache(BlockID bid)
{
    std::map<BlockID, TFSBlock::Ptr, BlockIDComp>::const_iterator it;
  
    it = cleanCacheMap_.find(bid);
  
    if (it != cleanCacheMap_.end()){
        return it->second;
    }

    return NULL;
}

bool TFSBlockManager::cacheNew(BlockID bid, TFSBlock::Ptr block)
{
    if(core_->configInterface()->maxCleanCacheBlocks() == 0)
        return true;

    if(cleanCacheQueue_.size() >= core_->configInterface()->maxCleanCacheBlocks())
    {
        //remove a old entry
        TFSBlock::Ptr oldBlock = cleanCacheQueue_.front();
            
        DBG_ASSERT(oldBlock.ptr());

        cleanCacheQueue_.pop();

        cleanCacheMap_.erase(oldBlock->id());
        DBG_ASSERT(cache(oldBlock->id()) == NULL);
    }

    cleanCacheMap_.insert(std::pair<BlockID, TFSBlock::Ptr>(bid, block));        
    cleanCacheQueue_.push(block);

    return true;
}










bool TFSBlockManager::blockStorageLayerRead(BlockID bid, U8 **blockBuffer, TFSBlockStore::Ptr *blockStore)
{
    core_->log()->entryNew(Fwk::Log::info(), "TFSBlockManager::blockStorageLayerRead blockStorageLayer_.size() %d", blockStorageLayer_.size());

    //get block from block store... starting from lowest cost layer    
    for(unsigned int index = 0; index < blockStorageLayer_.size(); index++)
    {
        *blockStore = blockStorageLayer_.at(index);

        if((*blockStore).ptr() == NULL)
        {
            DBG_ASSERT(blockStorageLayer_.at(index) == NULL);
            //core_->log()->entryNew(Fwk::Log::info(), "TFSBlockManager::blockStorageLayerRead block store at %d is null", index);
            continue;
        }

        if(!(*blockStore)->status().online())
        {
            //core_->log()->entryNew(Fwk::Log::info(), "TFSBlockManager::blockStorageLayerRead %s not online", (*blockStore)->name().c_str());
            continue;
        }
        
        //core_->log()->entryNew(Fwk::Log::info(), "TFSBlockManager::blockStorageLayerRead %s online", (*blockStore)->name().c_str());

        if((*blockStore)->block(bid, blockBuffer).success())
        {
            //got it
            DBG_ASSERT(*blockBuffer != NULL);

            //core_->log()->entryNew(Fwk::Log::info(), "TFSBlockManager::blockStorageLayerRead read from block store %s", (*blockStore)->name().c_str());
            return true;
        }
    }

    return false;
}


bool TFSBlockManager::blockStorageLayerWrite(BlockID bid, U8 *blockBuffer, TFSBlockStore::Ptr *blockStore)
{
    core_->log()->entryNew(Fwk::Log::info(), "TFSBlockManager::blockStorageLayerWrite blockStorageLayer_.size() %d", blockStorageLayer_.size());

    //write block to block store... starting from lowest cost layer
    for(unsigned int index = 0; index < blockStorageLayer_.size(); index++)
    {
        *blockStore = blockStorageLayer_.at(index);

        if((*blockStore).ptr() == NULL)
        {
            DBG_ASSERT(blockStorageLayer_.at(index) == NULL);
            //core_->log()->entryNew(Fwk::Log::info(), "TFSBlockManager::blockStorageLayerWrite block store at %d is null", index);
            continue;
        }

        if(!(*blockStore)->status().online())
        {
            //core_->log()->entryNew(Fwk::Log::info(), "TFSBlockManager::blockStorageLayerWrite %s not online", (*blockStore)->name().c_str());
            continue;
        }
        
        //core_->log()->entryNew(Fwk::Log::info(), "TFSBlockManager::blockStorageLayerWrite %s online", (*blockStore)->name().c_str());

        if((*blockStore)->blockNew(bid, blockBuffer).success())
        {
            //wrote block
            //core_->log()->entryNew(Fwk::Log::info(), "TFSBlockManager::blockStorageLayerWrite wrote to block store %s", (*blockStore)->name().c_str());
            return true;
        }
    }

    return false;
}

TFSBlock::Ptr TFSBlockManager::TFSBlockAlloc(BlockID bid, U8 *blockBuffer, bool newBlockBuffer, TFSBlockStore::Ptr blockStore)
{
    TFSBlock::Ptr block = NULL;
    U8 *buffer = NULL;
    U64 blockSize = core_->configInterface()->blockSize();

    if(newBlockBuffer)
    {
        buffer = (U8 *) malloc(blockSize);
        
        if(buffer == NULL)
            return NULL;

        memcpy(buffer, blockBuffer, blockSize);
    }
    else
    {
        buffer = blockBuffer;
    }

    //alloc a new TFSBlock obj
    block = TFSBlock::TFSBlockNew(bid, buffer, blockStore);

    if(block == NULL)
    {
        //can't alloc block
        core_->log()->entryNew(Fwk::Log::warning(), "TFSBlockManager::TFSBlockAlloc - TFSBlockNew() %s", bid.hexString().c_str());
        return NULL;
    }

    return block;
}




TFSBlockManager::Ptr TFSBlockManager::TFSBlockManagerNew(TFSCore::Ptr core)
{
    return new TFSBlockManager(core);
}


TFSBlockManager::TFSBlockManager(TFSCore::Ptr core)
{
    core_ = core;
    //cache_ = TFSCache::TFSCacheNew(core);
}

} //namespace
    