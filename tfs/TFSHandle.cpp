#include "TFSValueTypes.h"
#include "TFSObject.h"
#include "TFSOperation.h"
#include "TFSHandle.h"
#include "TFSCore.h"

namespace TFS {

using namespace std;

/*
  ==========================================================
  Implementation for TFSHandle
  ==========================================================
*/

TFSHandle::Ptr TFSHandle::TFSHandleNew(TFSObject::Ptr object, ProcessInfo process, OpenFlag openFlag)
{
    return new TFSHandle(object, process, openFlag);
}

void TFSHandle::readNew(TFSReadOperation::Ptr readOp)
{
    TFSRegularFileObject::Ptr fileObj = NULL;

    fileObj = Fwk::ptr_cast<TFSRegularFileObject, TFSObject>(object_);

    if(fileObj.ptr() == NULL)
    {
        //if(readOp->core()->log().ptr())
            //readOp->core()->log()->entryNew(Fwk::Log::warning(), "TFSHandle::read - cannot find object associated with handle");

        readOp->logEntryNew(Fwk::Log::warning(), "TFSHandle::read - cannot find object associated with handle");
        throw Fwk::UnexpectedTypeException("TFSHandle::read");
    }

    try
    {
        fileObj->readNew(readOp);
    }
    catch (Fwk::Exception &e)
    {
        //if(readOp->core()->log().ptr())
            //readOp->core()->log()->entryNew(Fwk::Log::warning(), "TFSHandle::read - exception %s", e.what());


        readOp->logEntryNew(Fwk::Log::warning(), "TFSHandle::read - exception %s", e.what());
        throw;
    }
    catch (...)
    {
        //if(readOp->core()->log().ptr())
            //readOp->core()->log()->entryNew(Fwk::Log::warning(), "TFSHandle::read - general exception");

        readOp->logEntryNew(Fwk::Log::warning(), "TFSHandle::read - general exception");
        throw;
    }
}

void TFSHandle::writeNew(TFSWriteOperation::Ptr writeOp)
{
    TFSRegularFileObject::Ptr fileObj = NULL;

    fileObj = Fwk::ptr_cast<TFSRegularFileObject, TFSObject>(object_);

    if(fileObj.ptr() == NULL)
    {
        //if(writeOp->core()->log().ptr())
            //writeOp->core()->log()->entryNew(Fwk::Log::warning(), "TFSHandle::write - cannot find object associated with handle");

        writeOp->logEntryNew(Fwk::Log::warning(), "TFSHandle::write - cannot find object associated with handle");
        throw Fwk::UnexpectedTypeException("TFSHandle::write");
    }

    try
    {
        fileObj->writeNew(writeOp);
    }
    catch (Fwk::Exception &e)
    {
        //if(writeOp->core()->log().ptr())
            //writeOp->core()->log()->entryNew(Fwk::Log::warning(), "TFSHandle::write - exception %s", e.what());

        writeOp->logEntryNew(Fwk::Log::warning(), "TFSHandle::write - exception %s", e.what());
        throw;
    }
    catch (...)
    {
        //if(writeOp->core()->log().ptr())
            //writeOp->core()->log()->entryNew(Fwk::Log::warning(), "TFSHandle::write - general exception");

        writeOp->logEntryNew(Fwk::Log::warning(), "TFSHandle::write - general exception");
        throw;
    }
}



void TFSHandle::close()
{
}

} //namespace
