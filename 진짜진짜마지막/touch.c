#include <stdio.h>
#include <stdlib.h> // for exit
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/mman.h>
#include <linux/fb.h> // for fb_var_screeninfo, FBIOGET_VSCREENINFO
#include <signal.h>
#include <linux/input.h>
#include <string.h>

#define FBDEV_FILE "/dev/fb0"
#define INPUT_DEVICE_LIST "/proc/bus/input/devices"
#define EVENT_STR "/dev/input/event"
#define MAX_BUFF 200

#define MAX_TOUCH_X	0x740
#define MAX_TOUCH_Y	0x540

static int touch_fd = 0;

int readFirstCoordinate(int* x, int* y)  /// get x, y
{
	int	screen_width = 1280;
	int	screen_height = 800;
	struct input_event event;
	int readSize;
	while (1)
	{
		readSize = read(touch_fd, &event, sizeof(event));

		if (readSize == sizeof(event))
		{
			if (event.type == EV_ABS)
			{
				if (event.code == ABS_MT_POSITION_X)
				{
					*x = event.value*screen_width / MAX_TOUCH_X;
				}
				else if (event.code == ABS_MT_POSITION_Y)
				{
					*y = event.value*screen_height / MAX_TOUCH_Y;
				}
				return 1;
			}
			else if ((event.type == EV_SYN) && (event.code == SYN_REPORT))
			{
				return 0;
				break;
			}
		}
	}
}

int openTouch(){  //for touchapp.c

	char eventFullPathName[100];
	int eventnum = 2;
	sprintf(eventFullPathName, "%s%d", EVENT_STR, eventnum);

	if (touch_fd > 0)
	{
		printf("touchDev is already open\n");
	}
	touch_fd = open(eventFullPathName, O_RDONLY);
	if (touch_fd < 0)
	{
		printf("touchDev open error\n");
	}

	return touch_fd;
}
