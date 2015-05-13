#include <string>
#include <vector>
#include <stdarg.h>

#include "../common/Ptr.h"
#include "../common/PtrInterface.h"

#include "TFSCore.h"

#include "TFSOperation.h"

namespace TFS {

using namespace std;

/*
  ==========================================================
  Implementation for TFSOperationResult
  ==========================================================
*/

/*
void TFSOperationResult::bytesReadIs(U64 value)
{
    if(bytesRead_ != value)
        bytesRead_ = value;
}

void TFSOperationResult::bytesReadInc(U64 value)
{
    bytesRead_ += value;
}

void TFSOperationResult::bytesWrittenIs(U64 value)
{
    if(bytesWritten_ != value)
        bytesWritten_ = value;
}

void TFSOperationResult::bytesWrittenInc(U64 value)
{
    bytesWritten_ += value;
}
*/

void TFSOperationResult::bytesTransferredIs(U64 value)
{
    if(bytesTransferred_ != value)
        bytesTransferred_ = value;
}

void TFSOperationResult::bytesTransferredInc(U64 value)
{
    bytesTransferred_ += value;
}


TFSOperationResult::Ptr TFSOperationResult::TFSOperationResultNew()
{
    return new TFSOperationResult();
}

/*
  ==========================================================
  Implementation for TFSOperation
  ==========================================================
*/

#if 1
void TFSOperation::logEntryNew(Fwk::Log::Priority p, const char *format, ...) throw()
{
    if(core_.ptr())
    {
        va_list ap;
        va_start(ap, format);

        core_->log()->vEntryNew(p, format, ap);
        va_end(ap);
    }
}
#endif

/*
  ==========================================================
  Implementation for TFSReadOperation
  ==========================================================
*/

/*
void TFSReadOperation::writeBuffer(U8 *srcBuffer, U64 length)
{
    memcpy(dstBuffer_ + result_->bytesRead(), srcBuffer, length);

    result_->bytesReadInc(length);
}
*/

TFSReadOperation::Ptr TFSReadOperation::TFSReadOperationNew(U8 *dstBuffer, U64 offset, U64 length, TFSCore::Ptr core)
{
    return new TFSReadOperation(dstBuffer, offset, length, core);
}

/*
  ==========================================================
  Implementation for TFSWriteOperation
  ==========================================================
*/

/*
void TFSWriteOperation::readBuffer(U8 *dstBuffer, U64 length)
{
    memcpy(dstBuffer, srcBuffer_ + result_->bytesWritten(), length);

    result_->bytesWrittenInc(length);
}
*/

TFSWriteOperation::Ptr TFSWriteOperation::TFSWriteOperationNew(U8 *srcBuffer, U64 offset, U64 length, TFSCore::Ptr core)
{
    return new TFSWriteOperation(srcBuffer, offset, length, core);
}


} //namespace
