#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "accelMagGyro.h"

static int fd = 0;
static FILE *fp = NULL;
static int output[3] = {0,};

int accelInit(void)
{
	if((fd = open(ACCELPATH "enable", O_WRONLY))<0)
	{
		printf("Accelerometer enable open failed!\n");
		return 1;
	}
	dprintf (fd, "1");
	close(fd);
	
	return 0;
}

int magInit(void)
{
	if((fd = open(ACCELPATH "enable", O_WRONLY))<0)
	{
		printf("Accelerometer enable open failed!\n");
		return 1;
	}
	dprintf (fd, "1");
	close(fd);
	
	return 0;
}

int gyroInit(void)
{
	if((fd = open(GYROPATH "enable", O_WRONLY))<0)
	{
		printf("Accelerometer enable open failed!\n");
		return 1;
	}
	dprintf (fd, "1");
	close(fd);
	
	return 0;
}

int* accelRead(void)
{
	fp = fopen(ACCELPATH "data", "rt");
	if(fp == NULL)
	{
		printf("data open failed!\n");
		exit(-1);
	}
	fscanf(fp, "%d, %d, %d", &output[0], &output[1], &output[2]);
	fclose(fp);
	
	return output;
}

int* magRead(void)
{
	fp = fopen(MAGPATH "data", "rt");
	if(fp == NULL)
	{
		printf("data open failed!\n");
		exit(-1);
	}
	fscanf(fp, "%d, %d, %d", &output[0], &output[1], &output[2]);
	fclose(fp);
	
	return output;
}

int* gyroRead(void)
{
	fp = fopen(GYROPATH "data", "rt");
	
	if(fp == NULL)
	{
		printf("data open failed!\n");
		exit(-1);
	}
	fscanf(fp, "%d, %d, %d", &output[0], &output[1], &output[2]);
	fclose(fp);
	
	return output;
}
