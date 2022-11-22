all: led.h led.c
	arm-linux-gnueabi-gcc -c led.c -o led.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o

