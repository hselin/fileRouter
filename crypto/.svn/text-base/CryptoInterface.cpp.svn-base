#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <queue>

#include "../common/Util.h"



#include "./cryptopp561/sha.h"


#include "CryptoInterface.h"


namespace Crypto {

using namespace std;

bool sha256(uint8_t *buffer, uint64_t bufferSize, uint8_t *data, uint64_t dataSize)
{
    DBG_ASSERT(bufferSize == (uint64_t) CryptoPP::SHA256::DIGESTSIZE);

    CryptoPP::SHA256().CalculateDigest(buffer, data, dataSize);
     // pbOutputBuffer must be SHA256::DIGESTSIZE bytes in length

    return true;
}


} //namespace


#if 0
void hash(uint8_t *hashBuffer, uint32_t hashBufferSize, uint_8_t *dataBuffer, uint32_t dataBufferSize)
{

}
#endif