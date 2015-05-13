all:
	make -C ./common
	make -C ./crypto
	make -C ./tfs
	make -C ./fuse
	cp ./common/common.o ./release
	cp ./crypto/crypto.o ./release
	cp ./crypto/libcryptopp.a ./release
	cp ./fuse/fuse.o ./release
	cp ./tfs/tfs.o ./release
	make -C ./release

clean:
	make clean -C ./common
	make clean -C ./fuse
	make clean -C ./tfs
	make clean -C ./release
