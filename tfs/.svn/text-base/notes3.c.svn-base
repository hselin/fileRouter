void TFSRegularFileObject::readNew(TFSReadOperation::Ptr readOp)
{
    queueIO(readOp);
}

void TFSRegularFileObject::writeNew(TFSWriteOperation::Ptr writeOp)
{
    queueIO(writeOp);
}

void TFSRegularFileObject::queueIO(TFSOperation::Ptr op)
{
    ioQueue_.push(op);
}

TFSOperation::Ptr TFSRegularFileObject::popIO()
{
    return ioQueue_.pop();
}

#if 0
    if(ioQueue_.empty())
        return NULL;
  
    TFSOperation::Ptr op = ioQueue_.front();
    ioQueue_.erase(ioQueue_.begin());

    return op;
#endif

//separate thread
void TFSRegularFileObject::processIO()
{
    while(1)
    {
        TFSOperation::Ptr op = popIO();

        if(op.ptr() == NULL)
            return;

        if(op->opTypeRead())
        {
            //handle read
            TFSReadOperation::Ptr readOp = Fwk::ptr_cast<TFSReadOperation, TFSOperation>(op);

            if(readOp.ptr() == NULL)
            {
                throw Fwk::UnexpectedTypeException("TFSRegularFileObject::processIO - read");
            }

            handleReadIO(readOp);
        }

        if(op->opTypeWrite())
        {
            //handle write
            TFSWriteOperation::Ptr writeOp = Fwk::ptr_cast<TFSWriteOperation, TFSOperation>(op);

            if(writeOp.ptr() == NULL)
            {
                throw Fwk::UnexpectedTypeException("TFSRegularFileObject::processIO - write");
            }

            handleWriteIO(writeOp);
        }
    }
}

#if 0
        if(intCount < core_->configInterface()->blockSize())
        {
            //RMW
            try
            {
                //block(blockNumber, buffer);
                readBlock(blockNumber, readOp->dstBuffer() + readOp->result()->bytesTransferred(), (intStart - blockStartByte), intCount);
            }
            catch (...)
            {
                //block does not exist
            }
        }
        else
        {
            //nothing
        }

        writeOp->readBuffer(buffer + (intStart - blockStartByte), intCount);

        blockIs(blockNumber, buffer);


        processByte = blockEndByte + 1;
#endif

void TFSRegularFileObject::handleReadIO(TFSReadOperation::Ptr readOp)
{
#if 0

#endif
}

void TFSRegularFileObject::handleWriteIO(TFSWriteOperation::Ptr writeOp)
{
#if 0

#endif
}



if(length == core_->configInterface()->blockSize())
{
    //full block read
    DBG_ASSERT(offset == 0);
    core_->cache()->block(bid, buffer);
}
//core_->cache()->block(bid, buffer);

//core_->log()->entryNew(Fwk::Log::info(), "TFSCache::block - dirString %s", dirString.c_str());
//core_->log()->entryNew(Fwk::Log::info(), "TFSCache::blockIs - dirString %s", dirString.c_str());


FILE *blockFile = fopen(fullPathString.c_str(), "rb");

if(blockFile)
{
    prea(d
    fread(buffer, 1, (1024*1024), blockFile);


    fclose(blockFile);
}
else
{
    throw Fwk::InternalException("TFSCache::block");
}