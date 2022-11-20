ccflags-y := -I$(src)/inc -Wall
obj-m += hello1.o hello2.o

all:
	$(MAKE) -C /lib/modules/`uname -r`/build M=$(PWD) modules
clean:
	$(MAKE) -C /lib/modules/`uname -r`/build M=$(PWD) clean
