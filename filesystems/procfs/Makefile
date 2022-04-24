ifneq  ($(KERNELRELEASE),)
obj-m:=procfs_example.o
else
KDIR := /lib/modules/$(shell uname -r)/build
PWD:=$(shell pwd)

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf *.ko *.o *.symvers *.cmd *.cmd.o *.mod *.mod.c *.order *.cmd
endif
