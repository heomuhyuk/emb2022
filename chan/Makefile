all: libMyPeri.a
libMyPeri.a: bitmap.o accelMagGyro.o Temperature.o textlcd.o fnd.o colorled.o buzzer.o button.o led.o rx_ipc.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o button.o buzzer.o colorled.o fnd.o textlcd.o Temperature.o accelMagGyro.o bitmap.o rx_ipc.o
rx_ipc.o: myMessage.h rx_ipc.c
	arm-linux-gnueabi-gcc -c rx_ipc.c -o rx_ipc.o
bitmap.o: bitmap.h bitmap.c
	arm-linux-gnueabi-gcc -c bitmap.c -o bitmap.o
accelMagGyro.o: accelMagGyro.h accelMagGyro.c
	arm-linux-gnueabi-gcc -c accelMagGyro.c -o accelMagGyro.o
Temperature.o: Temperature.h Temperature.c
	arm-linux-gnueabi-gcc -c Temperature.c -o Temperature.o
textlcd.o: textlcd.h textlcd.c
	arm-linux-gnueabi-gcc -c textlcd.c -o textlcd.o
fnd.o: fnd.h fnd.c
	arm-linux-gnueabi-gcc -c fnd.c -o fnd.o
colorled.o: colorled.h colorled.c
	arm-linux-gnueabi-gcc -c colorled.c -o colorled.o
buzzer.o: buzzer.h buzzer.c
	arm-linux-gnueabi-gcc -c buzzer.c -o buzzer.o
button.o: button.h button.c
	arm-linux-gnueabi-gcc -c button.c -o button.o
led.o: led.h led.c
	arm-linux-gnueabi-gcc -c led.c -o led.o



