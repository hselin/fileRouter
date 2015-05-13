#ifndef TFS_CORE_H
#define TFS_CORE_H

#include <string>
#include <map>

#include "../common/Ptr.h"
#include "../common/PtrInterface.h"
#include "../common/Log.h"

#include "TFSInterface.h"
#include "TFSObject.h"
#include "TFSValueTypes.h"
#include "TFSCache.h"
#include "TFSBlockManager.h"


namespace TFS
{

using namespace std;

class TFSCore : public Fwk::PtrInterface <TFSCore>
{
public:
    typedef Fwk::Ptr <TFSCore const> PtrConst;
    typedef Fwk::Ptr <TFSCore> Ptr;

    //accessors
    TFSConfigInterface::Ptr configInterface() const          { return configInterface_; }
    TFSStatusInterface::Ptr statusInterface() const          { return statusInterface_; }
    TFSIOInterface::Ptr ioInterface() const                  { return ioInterface_; }

    TFSBlockManager::Ptr blockManager() const                { return blockManager_; }
    Fwk::Log::Ptr log() const                                { return log_; }


    TFSDirectoryObject::Ptr directoryObject(ObjectPath path) const;
    TFSRegularFileObject::Ptr regularFileObject(ObjectPath path) const;

    //TFSHandle::Ptr handle(HandleID id) const;


    //mutators
    void directoryObjectAdd(ObjectPath path, TFSDirectoryObject::Ptr object);
    void regularFileObjectAdd(ObjectPath path, TFSRegularFileObject::Ptr object);


    //creators
    static TFSCore::Ptr TFSCoreNew() { return new TFSCore(); }

protected:
    TFSConfigInterface::Ptr configInterface_;
    TFSStatusInterface::Ptr statusInterface_;
    TFSIOInterface::Ptr     ioInterface_;

    TFSBlockManager::Ptr    blockManager_;

    Fwk::Log::Ptr           log_;

    map<ObjectPath, TFSDirectoryObject::Ptr, ObjectPathComp> directoryObjectLookupCache_;
    map<ObjectPath, TFSRegularFileObject::Ptr, ObjectPathComp> regularFileObjectLookupCache_;


    //constructors
    TFSCore();
    
}; //TFSCore

} //namespace
#endif