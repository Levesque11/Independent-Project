# This tells the kernel build system to build an object module (.ko) from drone_sensor.c
obj-m += drone_sensor.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
