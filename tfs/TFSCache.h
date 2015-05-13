#ifndef TFS_CACHE_H
#define TFS_CACHE_H

#if 0


#include <string>

#include "../common/Ptr.h"
#include "../common/PtrInterface.h"
#include "../common/Log.h"

#include "TFSValueTypes.h"


namespace TFS
{

using namespace std;

class TFSCore;

class TFSCache : public Fwk::PtrInterface <TFSCache>
{
public:
    typedef Fwk::Ptr <TFSCache const> PtrConst;
    typedef Fwk::Ptr <TFSCache> Ptr;

    //accessors

    //mutators
    //void objectCacheNew(BlockID id);
    //int block(BlockID id, U8 *buffer);
    //int blockIs(BlockID id, U8 *buffer);

    void block(BlockID bid, U8 *buffer);

    //creators
    static TFSCache::Ptr TFSCacheNew(Fwk::Ptr <TFSCore> core) { return new TFSCache(core); }

protected:
    //ResourceLocation resourceLocation_;
    Fwk::Ptr <TFSCore> core_;

    //constructors
    TFSCache(Fwk::Ptr <TFSCore> core) : core_(core) {}
    
}; //TFSCache

} //namespace

#endif

#endif

