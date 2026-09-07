obj-m += my_driver.o

KDIR := /home/levesque11/rt-kernel/linux
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
