#include <vector>
#include <map>

#include "../common/Util.h"

#include "TFSCore.h"


namespace TFS
{


/*
  ==========================================================
  Implementation for TFSCore
  ==========================================================
*/

TFSDirectoryObject::Ptr TFSCore::directoryObject(ObjectPath path) const
{
    std::map<ObjectPath, TFSDirectoryObject::Ptr, ObjectPathComp>::const_iterator it;
  
    it = directoryObjectLookupCache_.find(path);
  
    if (it != directoryObjectLookupCache_.end()){
        return it->second;
    }

    return NULL;
}

TFSRegularFileObject::Ptr TFSCore::regularFileObject(ObjectPath path) const
{
    std::map<ObjectPath, TFSRegularFileObject::Ptr, ObjectPathComp>::const_iterator it;
  
    it = regularFileObjectLookupCache_.find(path);
  
    if (it != regularFileObjectLookupCache_.end()){
        return it->second;
    }
    
    return NULL;
}

void TFSCore::directoryObjectAdd(ObjectPath path, TFSDirectoryObject::Ptr object)
{
    if(directoryObject(path).ptr())
    {
        log_->entryNew(Fwk::Log::info(), "TFSCore::directoryObjectAdd - duplicate object path %s", path.pathString().c_str());
        throw Fwk::NameInUseException("TFSCore::directoryObjectAdd");
    }

    object->coreIs(this);

    directoryObjectLookupCache_.insert(std::pair<ObjectPath, TFSDirectoryObject::Ptr>(path, object)); 

    //notify block manager
    blockManager_->onObjectAdd(object);
}

void TFSCore::regularFileObjectAdd(ObjectPath path, TFSRegularFileObject::Ptr object)
{
    if(regularFileObject(path).ptr())
    {
        log_->entryNew(Fwk::Log::info(), "TFSCore::regularFileObjectAdd - duplicate object path %s", path.pathString().c_str());
        throw Fwk::NameInUseException("TFSCore::regularFileObjectAdd");
    }

    object->coreIs(this);

    regularFileObjectLookupCache_.insert(std::pair<ObjectPath, TFSRegularFileObject::Ptr>(path, object));

    //notify block manager
    blockManager_->onObjectAdd(object);
}


TFSCore::TFSCore()
{
    configInterface_ = TFSConfigInterface::TFSConfigInterfaceNew(this);
    statusInterface_ = TFSStatusInterface::TFSStatusInterfaceNew(this);
    ioInterface_     = TFSIOInterface::TFSIOInterfaceNew(this);

    blockManager_    = TFSBlockManager::TFSBlockManagerNew(this);

    log_ = Fwk::Log::LogNew("TFS.log");
}

} //namespace











#if 0

int main(int argc, char *argv[])
{
    TFS::init();

    return 0;
}

#endif