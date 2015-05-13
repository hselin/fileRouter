#include <string>
#include <errno.h>

//#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "TFSValueTypes.h"
#include "TFSCore.h"

#include "TFSBlock.h"

namespace TFS
{

using namespace std;

/*
  ==========================================================
  Implementation for TFSBlock
  ==========================================================
*/

TFSBlock::Ptr TFSBlock::TFSBlockNew(BlockID id, U8 *buffer, TFSBlockStore::Ptr blockStore)
{
    return new TFSBlock(id, buffer, blockStore);
}

} //namespace
    