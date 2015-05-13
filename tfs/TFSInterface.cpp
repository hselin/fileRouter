#include "TFSCore.h"
#include "TFSOperation.h"
#include "TFSInterface.h"

#include "../common/Util.h"

namespace TFS
{

/*
  ==========================================================
  Implementation for TFSConfigInterface
  ==========================================================
*/

void TFSConfigInterface::blockSizeShiftIs(U64 shift)
{
    if(blockSizeShift_ != shift)
    {
        blockSizeShift_ = shift;
        blockSize_ = (U64)(1 << blockSizeShift_);
        blockOffsetMask_ = (blockSize_ - 1);
        blockSizeMask_ = ~(blockOffsetMask_);
    }
}

void TFSConfigInterface::localFileSystemBlockStoreNew(string name, string blockStoreRoot)
{
    core_->log()->entryNew(Fwk::Log::info(), "TFSConfigInterface::localFileSystemBlockStoreNew name %d", name.c_str());

    LocalFileSystemPath root(blockStoreRoot.c_str());
    TFSLocalFileSystemBlockStore::Ptr blockStore = TFSLocalFileSystemBlockStore::TFSLocalFileSystemBlockStoreNew(name, root, core_);

    core_->blockManager()->blockStoreAdd(blockStore);
}


/*
void TFSConfigInterface::cacheLocationIs(ResourceLocation location)
{
    if(!cacheLocation_.equal(&location))
        cacheLocation_ = location;
}
*/

/*
  ==========================================================
  Implementation for TFSIOInterface
  ==========================================================
*/

TFSDirectoryObject::Ptr TFSIOInterface::directoryObject(ObjectPath path) const
{
    return core_->directoryObject(path);
}

TFSRegularFileObject::Ptr TFSIOInterface::regularFileObject(ObjectPath path) const
{
    return core_->regularFileObject(path);
}


TFSHandle::Ptr TFSIOInterface::handle(HandleID hid) const
{
    std::map<HandleID, TFSHandle::Ptr, HandleIDComp>::const_iterator it;
  
    it = handleLookupCache_.find(hid);
  
    if (it != handleLookupCache_.end()){
        return it->second;
    }

    return NULL;
}

TFSHandle::Ptr TFSIOInterface::handleNew(ObjectPath path, TFSObject::Ptr object, ProcessInfo process, OpenFlag openFlag)
{
    if(object.ptr() == NULL)
        return NULL;

    //some count limitation here...


    //handle file vs dir differently


    TFSHandle::Ptr handle = TFSHandle::TFSHandleNew(object, process, openFlag);

    handleLookupCache_.insert(std::pair<HandleID, TFSHandle::Ptr>(handle->id(), handle));

    return handle;
}



void TFSIOInterface::handleDel(HandleID hid)
{
    core_->log()->entryNew(Fwk::Log::info(), "TFSIOInterface::handleDel - 0x%llx", hid.value());

#if 1
    TFSHandle::Ptr handle = this->handle(hid);

    if(handle.ptr() == NULL)
    {
        core_->log()->entryNew(Fwk::Log::warning(), "TFSIOInterface::handleDel - cannot find handle 0x%llx", hid.value());
        throw Fwk::NameNotFoundException("TFSIOInterface::handleDel");
    }

    handle->close();
#endif

    handleLookupCache_.erase(hid);
}














TFSRegularFileObject::Ptr TFSIOInterface::regularFileObjectNew(ObjectPath path, ObjectPermission permission)
{
    TFSRegularFileObject::Ptr fileObj = TFSRegularFileObject::TFSRegularFileObjectNew();
    fileObj->permissionIs(permission);

    return fileObj;
}

TFSDirectoryObject::Ptr TFSIOInterface::directoryObjectNew(ObjectPath path, ObjectPermission permission)
{
    TFSDirectoryObject::Ptr dirObj = TFSDirectoryObject::TFSDirectoryObjectNew();
    dirObj->permissionIs(permission);

    return dirObj;
}


void TFSIOInterface::rootDirectoryObjectAdd(ObjectPath path, TFSDirectoryObject::Ptr object)
{
    core_->log()->entryNew(Fwk::Log::info(), "TFSIOInterface::rootDirectoryObjectAdd - %s", path.pathString().c_str());

    if(path.root() == false)
    {
        core_->log()->entryNew(Fwk::Log::info(), "TFSIOInterface::rootDirectoryObjectAdd - not root path %s", path.pathString().c_str());
        throw Fwk::IllegalParameterException("TFSIOInterface::rootDirectoryObjectAdd");
    }

    try
    {
        object->pathNew(path);
        core_->directoryObjectAdd(path, object);
    }
    catch (...)
    {
        throw;
    }    
}

void TFSIOInterface::directoryObjectAdd(ObjectPath path, TFSDirectoryObject::Ptr object)
{
    core_->log()->entryNew(Fwk::Log::info(), "TFSIOInterface::directoryObjectAdd - %s", path.pathString().c_str());

    if(path.absolutePath() == false)
    {
        core_->log()->entryNew(Fwk::Log::info(), "TFSIOInterface::directoryObjectAdd - not absolute path %s", path.pathString().c_str());
        throw Fwk::IllegalParameterException("TFSIOInterface::directoryObjectAdd");
    }

    ObjectPath prefix = path.prefix();
    ObjectPathComponent lastComponent = path.lastComponent();

    core_->log()->entryNew(Fwk::Log::info(), "TFSIOInterface::directoryObjectAdd - [%s] [%s]", prefix.pathString().c_str(), lastComponent.componentString().c_str());

    TFSDirectoryObject::Ptr parentDir = core_->directoryObject(prefix);

    if(parentDir == NULL)
    {
        //can not get parent directory
        core_->log()->entryNew(Fwk::Log::info(), "TFSIOInterface::directoryObjectAdd - can not find prefix %s", prefix.pathString().c_str());
        throw Fwk::NameNotFoundException("TFSIOInterface::directoryObjectAdd");
    }

    try
    {
        object->pathNew(path);
        core_->directoryObjectAdd(path, object);
        parentDir->entryNew(lastComponent);
    }
    catch (...)
    {
        throw;
    }    
}

void TFSIOInterface::regularFileObjectAdd(ObjectPath path, TFSRegularFileObject::Ptr object)
{
    core_->log()->entryNew(Fwk::Log::info(), "TFSIOInterface::regularFileObjectAdd - %s", path.pathString().c_str());

    if(path.absolutePath() == false)
    {
        core_->log()->entryNew(Fwk::Log::info(), "TFSIOInterface::regularFileObjectAdd - not absolute path %s", path.pathString().c_str());
        throw Fwk::IllegalParameterException("TFSIOInterface::regularFileObjectAdd");
    }

    ObjectPath prefix = path.prefix();
    ObjectPathComponent lastComponent = path.lastComponent();

    core_->log()->entryNew(Fwk::Log::info(), "TFSIOInterface::regularFileObjectAdd - [%s] [%s]", prefix.pathString().c_str(), lastComponent.componentString().c_str());

    TFSDirectoryObject::Ptr parentDir = core_->directoryObject(prefix);

    if(parentDir == NULL)
    {
        //can not get parent directory
        core_->log()->entryNew(Fwk::Log::info(), "TFSIOInterface::regularFileObjectAdd - can not find prefix %s", prefix.pathString().c_str());
        throw Fwk::NameNotFoundException("TFSIOInterface::regularFileObjectAdd");
    }

    try
    {
        object->pathNew(path);
        core_->regularFileObjectAdd(path, object);
        parentDir->entryNew(lastComponent);
    }
    catch (...)
    {
        throw;
    }    
}


void TFSIOInterface::directoryObjectDel(ObjectPath path)
{
}

void TFSIOInterface::regularFileObjectDel(ObjectPath path)
{
}


U64 TFSIOInterface::readNew(HandleID hid, U8 *dstBuffer, U64 offset, U64 length)
{   
    core_->log()->entryNew(Fwk::Log::info(), "TFSIOInterface::read - offset 0x%llx length 0x%llx", offset, length);

    try
    {
        TFSHandle::Ptr handle = this->handle(hid);

        if(handle.ptr() == NULL)
        {
            core_->log()->entryNew(Fwk::Log::warning(), "TFSIOInterface::read - cannot find handle 0x%llx", hid.value());
            throw Fwk::InternalException("TFSIOInterface::read");
        }

        TFSReadOperation::Ptr readOp = TFSReadOperation::TFSReadOperationNew(dstBuffer, offset, length, core_);

        //zeroize the memory
        memset(dstBuffer, 0, (size_t) length);

        handle->readNew(readOp);

        //wait for op to finish
        //readOp->resultWait();

        return readOp->result()->bytesTransferred();
    }
    catch (Fwk::Exception &e)
    {
        core_->log()->entryNew(Fwk::Log::warning(), "tfswrapper_read - exception %s", e.what());
        throw;
    }
    catch (...)
    {
        core_->log()->entryNew(Fwk::Log::warning(), "tfswrapper_read - general exception");
        throw;
    }

    return 0;
}

U64 TFSIOInterface::writeNew(HandleID hid, U8 *srcBuffer, U64 offset, U64 length)
{
    
    core_->log()->entryNew(Fwk::Log::info(), "TFSIOInterface::write - offset 0x%llx length 0x%llx", offset, length);

    try
    {
        TFSHandle::Ptr handle = this->handle(hid);

        if(handle.ptr() == NULL)
        {
            core_->log()->entryNew(Fwk::Log::warning(), "TFSIOInterface::write - cannot find handle 0x%llx", hid.value());
            throw Fwk::InternalException("TFSIOInterface::write");
        }

        TFSWriteOperation::Ptr writeOp = TFSWriteOperation::TFSWriteOperationNew(srcBuffer, offset, length, core_);

        handle->writeNew(writeOp);

        //wait for op to finish
        //writeOp->resultWait();

        return writeOp->result()->bytesTransferred();
    }
    catch (Fwk::Exception &e)
    {
        core_->log()->entryNew(Fwk::Log::warning(), "tfswrapper_write - exception %s", e.what());
        throw;
    }
    catch (...)
    {
        core_->log()->entryNew(Fwk::Log::warning(), "tfswrapper_write - general exception");
        throw;
    }

    return 0;
}




TFSIOInterface::Ptr TFSIOInterface::TFSIOInterfaceNew(Fwk::Ptr <TFSCore> core)
{
    return new TFSIOInterface(core);
}

} //namespace