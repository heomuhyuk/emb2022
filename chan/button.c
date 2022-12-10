#include <fcntl.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <linux/input.h>
#include <unistd.h>
#include "button.h"

static pthread_t buttonTh_id;
static int fd = 0;
static void* buttonThFunc(void* arg);
static int msgID = 0;

int buttonLibInit(void)
{
	fd=open (BUTTON_DRIVER_NAME, O_RDONLY);
	msgID = msgget((key_t)MESSAGE_ID, IPC_CREAT|0666);
	pthread_create(&buttonTh_id, NULL, &buttonThFunc, NULL);
}

int buttonLibExit(void)
{
	pthread_cancel(buttonTh_id);
}

static void* buttonThFunc(void* arg)
{
	BUTTON_MSG_T msgTx;
	msgTx.messageNum = 1;
	struct input_event stEvent;

	while (1)
	{
		read(fd, &stEvent, sizeof(stEvent));
		if ( ( stEvent.type == EV_KEY) &&( stEvent.value == 0) )
		{
			msgTx.keyInput = stEvent.code;
			msgsnd(msgID, &msgTx, sizeof(int), 0);
		}
	}
}