#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "Temperature.h"
#define filename "/dev/spidev1.0"

static char gbuf[10];
static int file;
static int value = 0;
static int len;
static double temp;
int temp_init(void)
{
	__u8 mode, lsb, bits;
	__u32 speed=20000;
	
	if((file = open(filename, O_RDWR)) < 0)
	{
		printf("Failed to open the bus!\n");
		printf("ErrorType:%d\r\n",errno);
		exit(1);
	}
	
	if(ioctl(file, SPI_IOC_RD_MODE, &mode) < 0)
	{
		perror("SPI rd_mode");
		return 0;
	}
	if(ioctl(file, SPI_IOC_RD_LSB_FIRST, &lsb) < 0)
	{ 
		perror("SPI rd_lsb_first");
		return 0;
	}
	if(ioctl(file, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0)
	{
		perror("SPI bits_per_word");
		return 0;
	}
	
	return 1;
}

double temp_read(void)
{	
	memset(gbuf, 0, sizeof(gbuf));
	
	len = read(file, gbuf, 2);
	
	if(len != 2)
	{
		perror("read error");
		return 0;
	}
	
	value = (gbuf[1] >> 3);
	value = (gbuf[0]) << 5;
	if(gbuf[0]&0x80)
	{
		int i = 0;
		for(i=31; i > 12; i--)
		value |= (1<<i);
	}
	
	temp = (double)value*0.0625;
	
	return temp;
}

int temp_exit(void)
{
	if(close(file) != 0)return 1;
	
	return 0;
}
