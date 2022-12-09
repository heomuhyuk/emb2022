#include "led.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
static unsigned int ledValue = 0;
static int fd = 0;
int ledOnOff (int ledNum, int onOff)
{
    int i=1;
    i = i<<ledNum;
    ledValue = ledValue& (~i);
    if (onOff !=0) ledValue |= i;
    write(fd, &ledValue, 4);
    printf("state : num %d onoff %d\r\n", ledNum, onOff);
    sleep(1);
}
int ledStatus(void)
{
    return ledValue;
}
int ledLibInit(void)
{
    fd=open("/dev/periled", O_WRONLY);
    if ( fd < 0 )
    {
        perror("driver (//dev//cnled) open error.\n");
        return 1;
    }
    ledValue = 0;
}
int ledLibExit(void)
{
    ledValue = 0;
    ledOnOff(0, 0);
    close(fd);
}
