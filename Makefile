
obj-m := cdata.o
#obj-m := cdata-ts.o

#KDIR := /lib/module/2.6.24-26-generic/build
KDIR := /lib/modules/2.6.32-33-generic/build
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	rm -rf *.o *.ko *.*cmd modules.* Module.* .tmp_versions *.mod.c
