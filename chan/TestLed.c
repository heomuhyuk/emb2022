#include "led.h"
//#include "button.h"
//#include "led.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    ledLibInit();
    //led on
    ledOnOff(1,1);
    ledOnOff(0,0);
    ledOnOff(4,1);
    
    ledLibExit();
}
