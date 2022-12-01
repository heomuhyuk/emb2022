#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/msg.h>
#include <sys/mman.h>
#include <linux/input.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include "Temperature.h"
#include "accelMagGyro.h"
#include "bitmap.h"
#include "button.h"
#include "buzzer.h"
#include "colorled.h"
#include "fnd.h"
#include "led.h"
#include "textlcd.h"

    /*LED*/
//ledLibInit();
//ledOnOff(1,1);
//ledOnOff(0,0);
//ledLibExit();
    /*온도*/
//temp_init();
//temp_exit();
//temp_read()
    /*가속도*/
//accelInit()
//magInit()
//gyroInit()
//accelRead();
//magRead();
//gyroRead();

    /*비트맵*/
//bitmainfunc("test.bmp");

    /*버튼*/
//buttonLibInit();
/*	메인문 안에서
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
*/
//buttonLibExit();

    /*부저*/
//buzzerInit();
//buzzerPlaySong(musicScale[1]);
//buzzerStopSong();
//buzzerExit();


    /*컬러엘이디*/
//pwmLedInit();
//pwmSetPercent(30, 0); //r    ( duty = (100- percent) )
//sleep(1);
//pwmInactiveAll(); 종료
    
    //fnd//
//fndDisp(number , 0);
//fndOff(void);

    /*text lcd*/
//textLCD_Init();
//writeLCD(line_number, str);
//textLCD_off();

void AllDeviceInit()
{
    //여기에 드라이브 모두 이닛
}

void AllDeviceClose()
{
    //여기에 드라이브 모두 클로즈
}


int main(void){
	struct input_event stEvent;
	BUTTON_MSG_T msgRx;
	int msgID = msgget ((key_t)MESSAGE_ID, IPC_CREAT|0666);
    while(1)
	{
		int returnValue = 0 ;
		returnValue = msgrcv(msgID, &msgRx, sizeof(int), 0 ,0);
			printf("EV_KEY(");
			switch(msgRx.keyInput)
			{
                /*각 키가 눌렸을 때 행동 지정.*/
				case KEY_VOLUMEUP: printf("Volume up key):"); break; 
				case KEY_HOME: printf("Home key):"); break;
				case KEY_SEARCH: printf("Search key):"); break;
				case KEY_BACK: printf("Back key):"); break;
				case KEY_MENU: printf("Menu key):"); break;
				case KEY_VOLUMEDOWN:printf("Volume down key):");break;
			}
			printf("pressed\n");
	}

}