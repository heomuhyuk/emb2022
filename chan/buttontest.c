#include <stdio.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/mman.h>
#include "button.h"
// first read input device
#define INPUT_DEVICE_LIST "/dev/input/event4"

int main(int argc, char *argv[])
{
	struct input_event stEvent;
	BUTTON_MSG_T msgRx;
	int msgID = msgget ((key_t)MESSAGE_ID, IPC_CREAT|0666);
	buttonLibInit();
	while(1)
	{
		int returnValue = 0 ;
		returnValue = msgrcv(msgID, &msgRx, sizeof(int), 0 ,0);
			printf("EV_KEY(");
			switch(msgRx.keyInput)
			{
				case KEY_VOLUMEUP: printf("Volume up key):"); break;
				case KEY_HOME: printf("Home key):"); break;
				case KEY_SEARCH: printf("Search key):"); break;
				case KEY_BACK: printf("Back key):"); break;
				case KEY_MENU: printf("Menu key):"); break;
				case KEY_VOLUMEDOWN:printf("Volume down key):");break;
			}
			printf("pressed\n");
	}
	buttonLibExit();
}