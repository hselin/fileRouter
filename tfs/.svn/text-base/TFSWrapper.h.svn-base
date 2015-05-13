#ifndef TFS_WRAPPER_H
#define TFS_WRAPPER_H

#include <fuse.h>

#ifdef __cplusplus
extern "C" {
#endif


#define TFS_WRAPPER_OK                  (0)
#define TFS_WRAPPER_ERROR               (-1)


int tfsInit();




int tfswrapper_getattr(const char *rawPath, struct stat *stbuf);
int tfswrapper_readdir(const char *rawPath, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi);
int tfswrapper_truncate(const char *rawPath, off_t length);
int tfswrapper_open(const char *rawPath, struct fuse_file_info *fi);
int tfswrapper_opendir(const char *rawPath, struct fuse_file_info *fi);
int tfswrapper_create(const char *rawPath, mode_t mode, struct fuse_file_info *fi);
int tfswrapper_ftruncate(const char *rawPath, off_t length, struct fuse_file_info *fi);

int tfswrapper_read(const char *rawPath, char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
int tfswrapper_write(const char *rawPath, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
int tfswrapper_mkdir(const char *rawPath, mode_t rawMode);

#ifdef __cplusplus
}
#endif


#endif