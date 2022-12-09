#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "accelMagGyro.h"

int main(void)
{
	int *data;
	
	if(accelInit() != 0)
	{
		printf("Accelerometer Init failed!\n");
		exit(-1);
	}
	
	if(magInit() != 0)
	{
		printf("Accelerometer Init failed!\n");
		exit(-1);
	}
	
	if(gyroInit() != 0)
	{
		printf("Accelerometer Init failed!\n");
		exit(-1);
	}
	
	data = accelRead();
	printf("Accel data is: %d, %d, %d\n",data[0],data[1],data[2]);
	
	data = magRead();
	printf("Mag data is: %d, %d, %d\n",data[0],data[1],data[2]);
	
	data = gyroRead();
	printf("Gyro data is: %d, %d, %d\n",data[0],data[1],data[2]);
	
	return 0;
}
	
