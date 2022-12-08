#ifndef _BUTTON_H_
#define _BUTTON_H_
#define BUTTON_DRIVER_NAME "/dev/input/event5"
#define MESSAGE_ID 1122

typedef struct
{
	long int messageNum;
	int keyInput;
} BUTTON_MSG_T;

int buttonLibInit(void);
int buttonLibExit(void);
#endif
