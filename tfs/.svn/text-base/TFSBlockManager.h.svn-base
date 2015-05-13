#ifndef TFS_BLOCKMANAGER_H
#define TFS_BLOCKMANAGER_H

#include <string>
#include <vector>

#include <queue>

#include "../common/Ptr.h"
#include "../common/PtrInterface.h"

#include "TFSValueTypes.h"
#include "TFSObject.h"
#include "TFSBlock.h"
#include "TFSBlockStore.h"

namespace TFS {

using namespace std;

class TFSCore;

class TFSBlockManager : public Fwk::PtrInterface <TFSBlockManager>
{
public:
    typedef Fwk::Ptr <TFSBlockManager const> PtrConst;
    typedef Fwk::Ptr <TFSBlockManager> Ptr;

    //accessors
    //TFSCache::Ptr       cache() const           { return cache_; }

    //mutators
    void onObjectAdd(TFSObject::Ptr obj);

    //void block(BlockID bid, U8 *buffer);
    //void blockIs(BlockID bid, U8 *buffer);

    TFSBlock::Ptr block(BlockID bid);
    TFSBlock::Ptr blockNew(BlockID bid, U8 *blockBuffer);

    void blockStoreAdd(TFSBlockStore::Ptr blockStore);
    
    
    //creators


    static TFSBlockManager::Ptr TFSBlockManagerNew(Fwk::Ptr <TFSCore> core);

protected:
    map<BlockID, TFSBlock::Ptr, BlockIDComp> cleanCacheMap_;
    queue<TFSBlock::Ptr> cleanCacheQueue_;

    //map<BlockID, TFSBlock::Ptr, BlockIDComp> dirtyCache_;

    vector<TFSBlockStore::Ptr> blockStorageLayer_;


    Fwk::Ptr <TFSCore> core_;
    //TFSCache::Ptr cache_;

    //helper functions
    TFSBlock::Ptr cache(BlockID bid);
    bool cacheNew(BlockID bid, TFSBlock::Ptr block);

    /*
    TFSBlock::Ptr readCache(BlockID bid);
    TFSBlock::Ptr writeCache(BlockID bid);

    bool readCacheNew(BlockID bid, TFSBlock::Ptr block);    
    bool writeCacheNew(BlockID bid, TFSBlock::Ptr block);
    */

    bool blockStorageLayerRead(BlockID bid, U8 **blockBuffer, TFSBlockStore::Ptr *blockStore);
    bool blockStorageLayerWrite(BlockID bid, U8 *blockBuffer, TFSBlockStore::Ptr *blockStore);

    TFSBlock::Ptr TFSBlockAlloc(BlockID bid, U8 *blockBuffer, bool newBlockBuffer, TFSBlockStore::Ptr blockStore);

    //constructors
    TFSBlockManager(Fwk::Ptr <TFSCore> core);
}; //TFSBlockManager

} //namespace
#endif