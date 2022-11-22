#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
    buzzerInit();
    buzzerPlaySong(1);
    buzzerStopSong();
    buzzerPlaySong(2);
    buzzerStopSong();
    buzzerExit();
    return 0;
}
