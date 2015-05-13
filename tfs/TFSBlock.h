#ifndef TFS_BLOCK_H
#define TFS_BLOCK_H

#include <string>
#include <vector>

#include "../common/Ptr.h"
#include "../common/PtrInterface.h"

#include "TFSValueTypes.h"
#include "TFSObject.h"
#include "TFSBlockStore.h"

namespace TFS {

using namespace std;

class TFSBlock : public Fwk::PtrInterface <TFSBlock>
{
public:
    typedef Fwk::Ptr <TFSBlock const> PtrConst;
    typedef Fwk::Ptr <TFSBlock> Ptr;

    //accessors
    BlockID id() const  { return id_; }
    U8 *buffer() const  { return buffer_; }

    //mutators
    

    //creators


    static TFSBlock::Ptr TFSBlockNew(BlockID id, U8 *buffer, TFSBlockStore::Ptr blockStore);

protected:
    BlockID id_;
    U8 *buffer_;
    TFSBlockStore::Ptr blockStore_;

    TFSBlock(BlockID id, U8 *buffer, TFSBlockStore::Ptr blockStore) : id_(id), buffer_(buffer), blockStore_(blockStore) {}
}; //TFSBlock

} //namespace
#endif