//#include <sys/mman.h>

#include "../common/Util.h"

#include "TFSCore.h"
#include "TFSObject.h"


namespace TFS
{

/*
  ==========================================================
  Implementation for TFSObject
  ==========================================================
*/

bool TFSObject::path(ObjectPath path) const
{
    vector<ObjectPath>::const_iterator it;

    for(it = path_.begin(); it < path_.end(); it++)
    {
        if(it->equal(&path))
        {
            return true;
        }
    }

    return false;
}

BlockID TFSObject::blockID(U64 blockNumber) const
{
    std::map<U64, BlockID>::const_iterator it;
  
    it = blockMap_.find(blockNumber);
  
    if (it != blockMap_.end()){
        return it->second;
    }

    return BlockID();
}





void TFSObject::permissionIs(ObjectPermission permission)
{
    if(permission_.equal(&permission))
        return;

    permission_ = permission;
}

void TFSObject::pathNew(ObjectPath path)
{
    if(this->path(path) == true)
    {
        throw Fwk::NameInUseException("TFSObject::pathNew");
    }

    path_.push_back(path);
}

void TFSObject::removeObjectOnCloseIs(bool remove)
{
    if(removeObjectOnClose_ != remove)
        removeObjectOnClose_ = remove;
}

void TFSObject::blockIDIs(U64 blockNumber, BlockID bid)
{
    blockMap_.erase(blockNumber);

    DBG_ASSERT(blockID(blockNumber).defaultID() == true);

    blockMap_.insert(std::pair<U64, BlockID>(blockNumber, bid));
}


void TFSObject::coreIs(TFSCore::Ptr core)
{
    if(core_.ptr() != core.ptr())
    {
        DBG_ASSERT(core_.ptr() == NULL);

        core_ = core;

        //BlockID bid(wwn_.value(), Fwk::U64HexString(0));
        //core_->cache()->objectCacheNew(bid);
    }
}

/*
  ==========================================================
  Implementation for TFSRegularFileObject
  ==========================================================
*/

 U8 *TFSRegularFileObject::mmap(MemoryMapOption option)
 {
     /*
     if(option.read())
     {       

       void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);

     }

     if(option.write())
     {
     }

     */

     return NULL;
 }


//read operation
void TFSRegularFileObject::readNew(TFSReadOperation::Ptr readOp)
{
    //take file lock?

    if(readOp->length() == 0)
        return;

    if(this->size_.value() == 0)
        return;

    U64 opStartByte = readOp->offset();
    U64 opEndByte = opStartByte + readOp->length() - 1;

    //check math
    DBG_ASSERT(opStartByte <= opEndByte);


    if(opEndByte >= this->size_.value())
    {
        //out of bound access
        opEndByte = this->size_.value() - 1;
    }

    U64 processByte = opStartByte;


    U64 blockStartByte = 0;
    U64 blockEndByte = 0;
    U64 blockNumber = 0;


    U64 intStart = 0;
    U64 intEnd = 0;
    U64 intCount = 0;

    //U64 amountRead = 0;

    while(processByte <= opEndByte)
    {
        blockStartByte = processByte & core_->configInterface()->blockSizeMask();
        blockEndByte = blockStartByte + core_->configInterface()->blockSize() - 1;

        //check math
        DBG_ASSERT(blockStartByte <= blockEndByte);

        blockNumber = blockStartByte >> core_->configInterface()->blockSizeShift();

        //check math
        DBG_ASSERT(opStartByte <= blockEndByte);
        DBG_ASSERT(opEndByte >= blockStartByte);

        intStart = MAX(blockStartByte, opStartByte);
        intEnd = MIN(blockEndByte, opEndByte);
        intCount = intEnd - intStart + 1;
        
        //check math
        DBG_ASSERT(intStart <= intEnd);
        DBG_ASSERT(intCount > 0);
       
        //read from block
        if(readBlock(blockNumber, readOp->dstBuffer() + readOp->result()->bytesTransferred(), (intStart - blockStartByte), intCount) == 0)
        {
            //update result
            readOp->result()->bytesTransferredInc(intCount);
            processByte = blockEndByte + 1;
        }
        else
        {
            //error in processing read block
            core_->log()->entryNew(Fwk::Log::warning(), "TFSRegularFileObject::readNew - readBlock(0x%llx)", blockNumber);
            break;
        }        
    }

    return;
}

//write operation
void TFSRegularFileObject::writeNew(TFSWriteOperation::Ptr writeOp)
{
    //take file lock?

    if(writeOp->length() == 0)
        return;

    U64 opStartByte = writeOp->offset();
    U64 opEndByte = opStartByte + writeOp->length() - 1;

    //check math
    DBG_ASSERT(opStartByte <= opEndByte);

    U64 processByte = opStartByte;


    U64 blockStartByte = 0;
    U64 blockEndByte = 0;
    U64 blockNumber = 0;


    U64 intStart = 0;
    U64 intEnd = 0;
    U64 intCount = 0;
    //U8  buffer[TFSObject::TFSBlockSize_];

    //U64 amountProcessed = 0;

    while(processByte <= opEndByte)
    {
        blockStartByte = processByte & core_->configInterface()->blockSizeMask();
        blockEndByte = blockStartByte + core_->configInterface()->blockSize() - 1;

        //check math
        DBG_ASSERT(blockStartByte <= blockEndByte);

        blockNumber = blockStartByte >> core_->configInterface()->blockSizeShift();

        //check math
        DBG_ASSERT(opStartByte <= blockEndByte);
        DBG_ASSERT(opEndByte >= blockStartByte);

        intStart = MAX(blockStartByte, opStartByte);
        intEnd = MIN(blockEndByte, opEndByte);
        intCount = intEnd - intStart + 1;
        
        //check math
        DBG_ASSERT(intStart <= intEnd);
        DBG_ASSERT(intCount > 0); 

        //write to block
        if(writeBlock(blockNumber, writeOp->srcBuffer() + writeOp->result()->bytesTransferred(), (intStart - blockStartByte), intCount) == 0)
        {
            //update result
            writeOp->result()->bytesTransferredInc(intCount);
            processByte = blockEndByte + 1;
        }
        else
        {
            //error in processing write block
            core_->log()->entryNew(Fwk::Log::warning(), "TFSRegularFileObject::writeNew - writeBlock(0x%llx)", blockNumber);
            break;
        }
    }

    //update file size if needed
    this->size_ = MAX(this->size_.value(), (opEndByte + 1));


    core_->log()->entryNew(Fwk::Log::info(), "TFSRegularFileObject::handleWriteIO - file size: %lld", size_.value());

    return;
}

#if 0
void TFSRegularFileObject::readBlock(U64 blockNumber, U8 *buffer, U64 offset, U64 length)
{
    DBG_ASSERT(core_.ptr());

    BlockID bid(wwn_.value(), Fwk::U64HexString(id));


    if(length == core_->configInterface()->blockSize())
    {
        DBG_ASSERT(offset == 0);
        core_->cache()->block(bid, buffer);
    }
    else
    {
        U8 blockBuffer[TFSConfigInterface::TFSBlockSize_];
        
        if(core_->cache()->block(bid, blockBuffer) < 0)
        {
            throw Fwk::IOException("TFSRegularFileObject::readBlock");
        }

        memcpy(buffer, blockBuffer + offset, length);
    }
}
#endif


//read from block
int TFSRegularFileObject::readBlock(U64 blockNumber, U8 *buffer, U64 offset, U64 length)
{
    DBG_ASSERT(core_.ptr());

    //get block ID @ block number
    BlockID bid = blockID(blockNumber);

    //handle default ID
    if(bid.defaultID())
    {
        //empty "place holder" block
        return 0;
    }

    //get block
    TFSBlock::Ptr block = core_->blockManager()->block(bid);

    if(block.ptr() == NULL)
    {
        //cannot find block
        core_->log()->entryNew(Fwk::Log::warning(), "TFSRegularFileObject::readBlock - block not found %s", bid.hexString().c_str());
        return -1;
    }

    memcpy(buffer, block->buffer() + offset, (size_t) length);

    return 0;
}

int TFSRegularFileObject::writeBlock(U64 blockNumber, U8 *buffer, U64 offset, U64 length)
{
    DBG_ASSERT(core_.ptr());

    TFSBlock::Ptr block = NULL;

    //check if we are doing a full block write
    if(length == core_->configInterface()->blockSize())
    {
        //full block write
        DBG_ASSERT(offset == 0);
        
        //generate block ID from buffer
        BlockID bid = BlockID(buffer, core_->configInterface()->blockSize());

        //write block
        block = core_->blockManager()->blockNew(bid, buffer);
    }
    else
    {
        //partial block write

        DBG_ASSERT(length < core_->configInterface()->blockSize());
        
        U8 blockBuffer[TFSConfigInterface::TFSBlockSize_];
        memset(blockBuffer, 0, sizeof(blockBuffer));

        //get block ID @ block number
        BlockID bid = blockID(blockNumber);
        
        //handle default ID
        if(bid.defaultID())
        {
            //empty "place holder" block
            memcpy(blockBuffer + offset, buffer, (size_t) length);
        }
        else
        {
            //get block
            block = core_->blockManager()->block(bid);

            if(block.ptr() == NULL)
            {
                //cannot find block
                core_->log()->entryNew(Fwk::Log::warning(), "TFSRegularFileObject::writeBlock - block not found %s", bid.hexString().c_str());
                return -1;
            }

            memcpy(blockBuffer, block->buffer(), (size_t) core_->configInterface()->blockSize());
            
            //do overwrite
            memcpy(blockBuffer + offset, buffer, (size_t) length);
        }
        
        //generate block ID from buffer
        bid = BlockID(blockBuffer, core_->configInterface()->blockSize());

        //write block
        block = core_->blockManager()->blockNew(bid, blockBuffer);
    }

    if(block.ptr() == NULL)
    {
        core_->log()->entryNew(Fwk::Log::warning(), "TFSRegularFileObject::writeBlock - block write failed 0x%llx", blockNumber);
        return -1;
    }

    blockIDIs(blockNumber, block->id());

    return 0;
}

#if 0
void TFSRegularFileObject::writeBlock(U64 blockNumber, U8 *buffer, U64 offset, U64 length)
{
    DBG_ASSERT(core_.ptr());

    BlockID bid(wwn_.value(), Fwk::U64HexString(id));

    if(length == core_->configInterface()->blockSize())
    {
        DBG_ASSERT(offset == 0);
        core_->cache()->blockIs(bid, buffer);
    }
    else
    {
        U8 blockBuffer[TFSConfigInterface::TFSBlockSize_];
        memset(blockBuffer, 0, sizeof(blockBuffer));

        //block might not exist yet, so no need to check return code
        core_->cache()->block(bid, blockBuffer);
        
        memcpy(blockBuffer + offset, buffer, length);

        if(core_->cache()->blockIs(bid, blockBuffer) < 0)
        {
            throw Fwk::IOException("TFSRegularFileObject::writeBlock");
        }
    }
}
#endif



TFSRegularFileObject::Ptr TFSRegularFileObject::TFSRegularFileObjectNew()
{
    return new TFSRegularFileObject();
}


/*
  ==========================================================
  Implementation for TFSDirectoryObject
  ==========================================================
*/

ObjectPathComponent TFSDirectoryObject::entry(U64 index) const
{
    if((std::vector<ObjectPathComponent>::size_type)index >= entry_.size())
        return ObjectPathComponent("");

    return entry_.at((std::vector<ObjectPathComponent>::size_type)index);
}

bool TFSDirectoryObject::entry(ObjectPathComponent component) const
{
    vector<ObjectPathComponent>::const_iterator it;

    for(it = entry_.begin(); it < entry_.end(); it++)
    {
        //if(it->componentString().compare(component.componentString()) == 0)
        if(it->equal(&component))
        {
            return true;
        }
    }

    return false;
}

vector<ObjectPathComponent> TFSDirectoryObject::entry() const
{
    return entry_;
}


void TFSDirectoryObject::entryNew(ObjectPathComponent component)
{
    if(entry(component) == true)
    {
        throw Fwk::NameInUseException("TFSDirectoryObject::entryNew");
    }

    entry_.push_back(component);
}

void TFSDirectoryObject::entryDel(ObjectPathComponent component)
{
    vector<ObjectPathComponent>::const_iterator it;

    for(it = entry_.begin(); it < entry_.end(); it++)
    {
        if(it->componentString().compare(component.componentString()) == 0)
        {
            //entry_.erase(it);
            return;
        }
    }
}

TFSDirectoryObject::Ptr TFSDirectoryObject::TFSDirectoryObjectNew()
{
    return new TFSDirectoryObject();
}



} //namespace