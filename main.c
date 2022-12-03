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

/*---------------스레드----------------*/
#define MUTEX_ENABLE 0
pthread_t tid[2];
int jobIndex = 0; //순차적으로 증가
pthread_mutex_t lock;
/*-------------------------------------*/

/*-------------스레드 1 버튼 home ---------------*/
void* Do_Thread_1(void *arg)
{
    #if MUTEX_ENABLE //  mutex을 사용했을 경우
        pthread_mutex_lock(&lock); // lock으로 다른 스레드의 동시 수행 차단
    #endif

    /*스레드 1 구현부*/

    #if MUTEX_ENABLE
        pthread_mutex_unlock(&lock); // 다른 스레드가 수행할수 있도록 lock 해제
    #endif
    return NULL;
}
/*---------------------------------------*/

/*-------------스레드 2 버튼 back ---------------*/
void* Do_Thread_2(void *arg)
{
    #if MUTEX_ENABLE //  mutex을 사용했을 경우
        pthread_mutex_lock(&lock); // lock으로 다른 스레드의 동시 수행 차단
    #endif

    /*스레드 2 구현부*/

    #if MUTEX_ENABLE
        pthread_mutex_unlock(&lock); // 다른 스레드가 수행할수 있도록 lock 해제
    #endif
    return NULL;
}
/*---------------------------------------*/

/*-------------스레드 3 search ---------------*/
void* Do_Thread_3(void *arg)
{
    #if MUTEX_ENABLE //  mutex을 사용했을 경우
        pthread_mutex_lock(&lock); // lock으로 다른 스레드의 동시 수행 차단
    #endif

    /*스레드 3 구현부*/

    #if MUTEX_ENABLE
        pthread_mutex_unlock(&lock); // 다른 스레드가 수행할수 있도록 lock 해제
    #endif
    return NULL;
}
/*---------------------------------------*/

/*-------------스레드 4 menu ---------------*/
void* Do_Thread_4(void *arg)
{
    #if MUTEX_ENABLE //  mutex을 사용했을 경우
        pthread_mutex_lock(&lock); // lock으로 다른 스레드의 동시 수행 차단
    #endif

    /*스레드 4 구현부*/

    #if MUTEX_ENABLE
        pthread_mutex_unlock(&lock); // 다른 스레드가 수행할수 있도록 lock 해제
    #endif
    return NULL;
}
/*---------------------------------------*/

/*-------------스레드 5 vol up ---------------*/
void* Do_Thread_5(void *arg)
{
    #if MUTEX_ENABLE //  mutex을 사용했을 경우
        pthread_mutex_lock(&lock); // lock으로 다른 스레드의 동시 수행 차단
    #endif

    /*스레드 5 구현부*/

    #if MUTEX_ENABLE
        pthread_mutex_unlock(&lock); // 다른 스레드가 수행할수 있도록 lock 해제
    #endif
    return NULL;
}
/*---------------------------------------*/

/*-------------스레드 6 vol up ---------------*/
void* Do_Thread_6(void *arg)
{
    #if MUTEX_ENABLE //  mutex을 사용했을 경우
        pthread_mutex_lock(&lock); // lock으로 다른 스레드의 동시 수행 차단
    #endif

    /*스레드 6 구현부*/

    #if MUTEX_ENABLE
        pthread_mutex_unlock(&lock); // 다른 스레드가 수행할수 있도록 lock 해제
    #endif
    return NULL;
}
/*---------------------------------------*/


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
    ledLibInit();
    temp_init();
    accelInit()
    magInit()
    gyroInit()
    buttonLibInit();
    buzzerInit();
    pwmLedInit();
    textLCD_Init();
}

void AllDeviceClose()
{
    ledLibExit();
    temp_exit();
    buttonLibExit();
    buzzerExit();
    pwmInactiveAll();
    fndOff(void);
    textLCD_off();
}


int main(void){
    /*스타트*/
    AllDeviceInit();
    //--------------
    /*스레드 전용 변수*/
    int err;
    if (pthread_mutex_init(&lock, NULL) != 0)   //스레드 초기화
    {
        printf (“\n Mutex Init Failed!!\n”);
        return 1;
    }
    /*버튼 전용 변수*/
	struct input_event stEvent;
	BUTTON_MSG_T msgRx;
	int msgID = msgget ((key_t)MESSAGE_ID, IPC_CREAT|0666);
    /*------------*/
    /*메인 스레드*/
    while(1)
	{
		int returnValue = 0 ;
		returnValue = msgrcv(msgID, &msgRx, sizeof(int), 0 ,0);
			switch(msgRx.keyInput)
			{
                /*각 키가 눌렸을 때 행동 지정.*/
				case KEY_VOLUMEUP: 
                    printf("Volume up key : "); 
                    err = pthread_create(&(tid[0]), NULL, &doSomeThing, NULL);  //스레드 1
                    if (err != 0) printf (“Thread Create Error: [%d]\n”, err);
                break; 
				case KEY_HOME: 
                    printf("Home key : ");
                    err = pthread_create(&(tid[1]), NULL, &doSomeThing, NULL);  //스레드 2
                    if (err != 0) printf (“Thread Create Error: [%d]\n”, err);
                break;
				    case KEY_SEARCH:
                    printf("Search key : ");                    
                    err = pthread_create(&(tid[2]), NULL, &doSomeThing, NULL);  //스레드 3
                    if (err != 0) printf (“Thread Create Error: [%d]\n”, err);
                break;
				case KEY_BACK:
                    printf("Back key : ");                     
                    err = pthread_create(&(tid[3]), NULL, &doSomeThing, NULL);  //스레드 4
                    if (err != 0) printf (“Thread Create Error: [%d]\n”, err);
                break;
				case KEY_MENU: 
                    printf("Menu key : ");                     
                    err = pthread_create(&(tid[4]), NULL, &doSomeThing, NULL);  //스레드 5
                    if (err != 0) printf (“Thread Create Error: [%d]\n”, err);
                break;
				case KEY_VOLUMEDOWN:
                    printf("Volume down key):");
                    err = pthread_create(&(tid[5]), NULL, &doSomeThing, NULL);  //스레드 6
                    if (err != 0) printf (“Thread Create Error: [%d]\n”, err);
                break;
			}
	}


    /*종료료*/
    AllDeviceClose();
    return 0
}
