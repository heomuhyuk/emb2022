#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "colorled.h"

int main(void)
{//duty cycle을 통한 RGB 값 조절
    pwmLedInit();
    printf("colorled init\n");
    pwmSetPercent(30, 0); //r    ( duty = (100- percent) )
    pwmSetPercent(60, 1); //g
    pwmSetPercent(90, 2); //b
    sleep(1);
    pwmInactiveAll();
    printf("colorled exit\n");
    return 0;
}
