all: libMyPeri.a
libMyPeri.a: button.o led.o buzzer.o fnd.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o button.o buzzer.o fnd.o
button.o: button.h button.c
	arm-linux-gnueabi-gcc -c button.c -o button.o
led.o: led.h led.c
	arm-linux-gnueabi-gcc -c led.c -o led.o
buzzer.o: buzzer.h buzzer.c
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o
fnd.o: fnd.h fnd.c
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o
