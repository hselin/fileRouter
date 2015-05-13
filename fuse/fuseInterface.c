#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <assert.h>

#include "../tfs/TFSWrapper.h"

//gcc -Wall `pkg-config fuse --cflags --libs` fuseInterface.c -o fuseInterface
//./tfs  /testmnt/  -oallow_other -odefault_permissions -d
//fusermount -u /testmnt

struct fuse_operations fi_operations = {
    .getattr     = tfswrapper_getattr,
    .readdir     = tfswrapper_readdir,
    .truncate    = tfswrapper_truncate,
    .open        = tfswrapper_open,
    .opendir     = tfswrapper_opendir,
    .create      = tfswrapper_create,
    .ftruncate   = tfswrapper_ftruncate,
    .read        = tfswrapper_read,
    .write       = tfswrapper_write,
    .mkdir       = tfswrapper_mkdir,
    .flag_nullpath_ok = 1,
};

int fuseInit(int argc, char *argv[])
{
    int status = 0;

    status = fuse_main(argc, argv, &fi_operations, NULL);

    return status;
}