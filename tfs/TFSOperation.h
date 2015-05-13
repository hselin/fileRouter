#ifndef TFS_OPERATION_H
#define TFS_OPERATION_H

#include <string>
#include <map>

#include "../common/Ptr.h"
#include "../common/PtrInterface.h"
#include "../common/Log.h"

#include "TFSValueTypes.h"


namespace TFS
{

using namespace std;

class TFSCore;

class TFSOperationResult : public Fwk::PtrInterface <TFSOperationResult>
{
public:
    typedef Fwk::Ptr <TFSOperationResult const> PtrConst;
    typedef Fwk::Ptr <TFSOperationResult> Ptr;

    //accessors
    //U64 bytesRead() const         { return bytesRead_; }
    //U64 bytesWritten() const      { return bytesWritten_; }
    U64 bytesTransferred() const    { return bytesTransferred_; }

    //mutators
    /*
    void bytesReadIs(U64 value);
    void bytesReadInc(U64 value);
    void bytesWrittenIs(U64 value);
    void bytesWrittenInc(U64 value);
    */

    void bytesTransferredIs(U64 value);
    void bytesTransferredInc(U64 value);


    //creators
    static TFSOperationResult::Ptr TFSOperationResultNew();

protected:
    //U64 bytesRead_;
    //U64 bytesWritten_;
    U64 bytesTransferred_;

    //constructors
    //TFSOperationResult(U64 bytesRead, U64 bytesWritten) : bytesRead_(bytesRead), bytesWritten_(bytesWritten) {}
    TFSOperationResult() : bytesTransferred_(0) {} //bytesRead_(0), bytesWritten_(0) {}
};

class TFSOperation : public Fwk::PtrInterface <TFSOperation>
{
public:
    typedef Fwk::Ptr <TFSOperation const> PtrConst;
    typedef Fwk::Ptr <TFSOperation> Ptr;

    enum OperationType {
        invalidOp__ = 0,
        readOp__ = 1,
        writeOp__ = 2
    };

    
    static inline OperationType readOp()                { return readOp__; }
    static inline OperationType writeOp()               { return writeOp__; }

    //accessors
    TFSOperation::OperationType opType() const          { return opType_; }
    //Fwk::Log::Ptr log() const                           { return log_; }
    Fwk::Ptr <TFSCore> core() const                     { return core_; }

    TFSOperationResult::Ptr result() const              { return result_;}

    bool opTypeRead() const                             { return (opType_ == readOp__); }
    bool opTypeWrite() const                            { return (opType_ == writeOp__); }

    //mutators
    void resultWait();
    void logEntryNew(Fwk::Log::Priority p, const char *format, ...) throw();

    //creators
protected:
    TFSOperation::OperationType opType_;
    //Fwk::Log::Ptr log_;
    Fwk::Ptr <TFSCore> core_;
    TFSOperationResult::Ptr result_;


    //constructors
    //TFSOperation(TFSOperation::OperationType opType, Fwk::Log::Ptr log) : opType_(opType), log_(log) { result_ = TFSOperationResult::TFSOperationResultNew(); }

    TFSOperation(TFSOperation::OperationType opType, Fwk::Ptr <TFSCore> core) : opType_(opType), core_(core) { result_ = TFSOperationResult::TFSOperationResultNew(); }
};



class TFSReadOperation : public TFSOperation
{
public:
    typedef Fwk::Ptr <TFSReadOperation const> PtrConst;
    typedef Fwk::Ptr <TFSReadOperation> Ptr;

    //accessors
    U8* dstBuffer() const                { return dstBuffer_; }    
    U64 offset() const                   { return offset_; }
    U64 length() const                   { return length_; }

    //mutators
    void writeBuffer(U8 *srcBuffer, U64 length);

    //creators
    static TFSReadOperation::Ptr TFSReadOperationNew(U8 *dstBuffer, U64 offset, U64 length, Fwk::Ptr <TFSCore> core);

protected:
    U8 *dstBuffer_;
    U64 offset_;
    U64 length_;

    //constructors
    TFSReadOperation(U8 *dstBuffer, U64 offset, U64 length, Fwk::Ptr <TFSCore> core) : TFSOperation(TFSOperation::readOp(), core), dstBuffer_(dstBuffer), offset_(offset), length_(length) {}
    TFSReadOperation() : TFSOperation(TFSOperation::readOp(), NULL), dstBuffer_(NULL), offset_(0), length_(0) {}
};

class TFSWriteOperation : public TFSOperation
{
public:
    typedef Fwk::Ptr <TFSWriteOperation const> PtrConst;
    typedef Fwk::Ptr <TFSWriteOperation> Ptr;

    //accessors
    U8* srcBuffer() const                { return srcBuffer_; }
    U64 offset() const                   { return offset_; }
    U64 length() const                   { return length_; }

    //mutators
    void readBuffer(U8 *dstBuffer, U64 length);

    //creators
    static TFSWriteOperation::Ptr TFSWriteOperationNew(U8 *srcBuffer, U64 offset, U64 length, Fwk::Ptr <TFSCore> core);

protected:
    U8 *srcBuffer_;
    U64 offset_;
    U64 length_;

    Fwk::Log::Ptr log_;

    //constructors
    TFSWriteOperation(U8 *srcBuffer, U64 offset, U64 length, Fwk::Ptr <TFSCore> core) : TFSOperation(TFSOperation::writeOp(), core), srcBuffer_(srcBuffer), offset_(offset), length_(length) {}
    TFSWriteOperation() : TFSOperation(TFSOperation::writeOp(), NULL), srcBuffer_(NULL), offset_(0), length_(0) {}
};


} //namespace
#endif