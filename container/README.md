Download BuildRoot source code from https://buildroot.uclibc.org/

Compile the source code and you can test CLONE_NEWNS
```shell
make menuconfig
make -j $(nproc)
```
