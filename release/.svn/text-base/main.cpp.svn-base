#include "../common/Util.h"
#include "../tfs/TFSWrapper.h"

extern "C" {
    int fuseInit(int argc, char *argv[]);
}


int main(int argc, char *argv[])
{
    tfsInit();
    fuseInit(argc, argv);
}