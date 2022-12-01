#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "Temperature.h"

int main(void){
int a;

int spi_init(const char filename[40])
char * spi_read_lm74(int file)

a = int getTem(void);
printf("current temp: %d", a);

}
