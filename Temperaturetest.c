#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Temperature.h"

int main(void)
{
	double thermal; int cnt;
	temp_init();

	printf("Temperature is: %f\n", temp_read());
    temp_exit();
	printf("goodbye!\n");
	
	return 0;
}
