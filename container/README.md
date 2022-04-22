Download BuildRoot source code from https://buildroot.uclibc.org/

Compile the source code and you can test full.c
```shell
make menuconfig
make -j $(nproc)
```
Make a link dir name fs to buildroot-path/output/target, and run the execution file after compiling full.c.
