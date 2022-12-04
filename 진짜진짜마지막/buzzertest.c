#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"

#define MAX_SCALE_STEP 8
static const int musicScale[MAX_SCALE_STEP] =
{
    262, /*do*/ 294,330,349,392,440,494, /* si */ 523
};

int main(void)
{
    buzzerInit();
    printf("buzzer turn on\n");
    printf("do[1] = 262\nre[2] = 294\n,mi[3] = 330\n,pa[4] = 349\n,sol[5] = 392\n,ra[6] = 440\n,si[7] = 494\n");
    buzzerPlaySong(musicScale[1]);
    printf("scale : %d\n", musicScale[1]);
    sleep(1);

    buzzerPlaySong(musicScale[3]);
    printf("scale : %d\n", musicScale[3]);
    sleep(1);

    buzzerPlaySong(musicScale[5]);
    printf("scale : %d\n", musicScale[5]);
    sleep(1);

    buzzerStopSong();
    printf("turn off\n");
    buzzerExit();
    return 0;
}
