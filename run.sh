rm -rf ./cache/*
rm -f TFS.log
./release/tfs /testmnt/ -oallow_other -odefault_permissions -obig_writes -omax_read=524288 -omax_write=524288 -d
