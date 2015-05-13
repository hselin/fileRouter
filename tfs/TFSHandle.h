#ifndef TFS_HANDLE_H
#define TFS_HANDLE_H

#include <string>
#include <vector>

#include "../common/Ptr.h"
#include "../common/PtrInterface.h"

#include "TFSValueTypes.h"
#include "TFSOperation.h"

namespace TFS {

using namespace std;

class TFSObject;

class TFSHandle : public Fwk::PtrInterface <TFSHandle>
{
public:
    typedef Fwk::Ptr <TFSHandle const> PtrConst;
    typedef Fwk::Ptr <TFSHandle> Ptr;

    //accessors
    HandleID id() const                      { return id_; }
    Fwk::Ptr <TFSObject> object() const      { return object_; }
    ProcessInfo process() const              { return process_; }
    OpenFlag openFlag() const                { return openFlag_; }

    U64 currentOffset() const                { return currentOffset_; }

 
    //mutators
    void readNew(TFSReadOperation::Ptr readOp);
    void writeNew(TFSWriteOperation::Ptr writeOp);

    void close();

    //creators
    static TFSHandle::Ptr TFSHandleNew(Fwk::Ptr <TFSObject> object, ProcessInfo process, OpenFlag openFlag);

protected:
    HandleID id_;
    Fwk::Ptr <TFSObject> object_;
    ProcessInfo process_;
    OpenFlag openFlag_;

    U64 currentOffset_;

    //constructors
    TFSHandle(Fwk::Ptr <TFSObject> object, ProcessInfo process, OpenFlag openFlag) : object_(object), process_(process), openFlag_(openFlag), currentOffset_(0)
    {
        if(openFlag_.append())
        {
            //set offset @ EOF
            currentOffset_ = object->size().value();
        }
    }
   
}; //TFSHandle

} //namespace
#endif