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
// first read input device
#define INPUT_DEVICE_LIST "/dev/input/event4"

/*------------ 버튼 home ---------------*/
void BT_HOME(void)
{
        /*버튼 전용 변수*/
	struct input_event stEvent;
	BUTTON_MSG_T msgRx;
	int msgID = msgget ((key_t)MESSAGE_ID, IPC_CREAT|0666);
	int status = 0;
    /*------------*/ 
    writeLCD(1, "                  ");
    writeLCD(2, "                  ");
    writeLCD(1, "home");
    fndDisp(0 , 0b0000);
    /*무한루프*/
    while(1)
    {
    double thermal;
    int cnt;
    int mode ;
int number, num_date;

struct tm *ptmcur;
struct tm* date;
time_t tTime, base;
if ( -1 == time(&tTime) )
return -1; 

if ( -1 == time(&base) )
return -1; 

        int returnValue = 0 ;
		returnValue = msgrcv(msgID, &msgRx, sizeof(int), 0 ,IPC_NOWAIT);

		switch(msgRx.keyInput)
		{
            /*각 키가 눌렸을 때 행동 지정.*/
			case KEY_VOLUMEUP: 
                //printf("volume key : ");

	temp_init();
	
    thermal = temp_read();
    if (status != 1){
		status = 1;
	writeLCD(1, "                           ");
    writeLCD(2, "                           ");
		writeLCD(1, "temperature");
          printf("temperature : %f\n", temp_read());
	}
    fndDisp(thermal , 0b00000);
            break; 
			case KEY_HOME: 
                printf("Home key : ");
                BT_HOME();
            break;
			case KEY_SEARCH:
 //               printf("Search key : ");          
 date = localtime(&base);    

 num_date = (date->tm_year -100) * 10000;
 num_date += (date->tm_mon + 1) * 100; 
 num_date += date->tm_mday;
   if (status != 3){
		status = 3;
	writeLCD(1, "                           ");
    writeLCD(2, "                           ");
		writeLCD(1, "date");
        printf("date : %d \n" , num_date);
	}
    fndDisp(num_date , 0b1010);


            break;
            
			case KEY_BACK:
                printf("Back key : ");                                     
                return NULL;    //빠져나감.
            break;
            
			case KEY_MENU: 
                printf("Menu key : ");             
                break;
                
			case KEY_VOLUMEDOWN:
             //   printf("Volume down key :");
ptmcur = localtime(&tTime);

number = ptmcur->tm_hour * 10000;
number += ptmcur->tm_min *100;
number += ptmcur->tm_sec;
  if (status != 2){
		status = 2;
	writeLCD(1, "                           ");
    writeLCD(2, "                           ");
		writeLCD(1, "time");
        printf("time : %d \n" , number);
	}
fndDisp(number , 0b1010);

break;
		}
	usleep(50000);	
    }
    return NULL;
}
/*---------------------------------------*/

/*------------ 버튼 BACK ---------------*/

//void BT_BACK(void)
//{
//        /*버튼 전용 변수*/
//	struct input_event stEvent;
//	BUTTON_MSG_T msgRx;
//	int msgID = msgget ((key_t)MESSAGE_ID, IPC_CREAT|0666);
//    /*------------*/
//    /*무한루프*/
//    while(1)
//    {
//        writeLCD(1, "BACK");
//        int returnValue = 0 ;
//		returnValue = msgrcv(msgID, &msgRx, sizeof(int), 0 ,0);
//
//		switch(msgRx.keyInput)
//		{
//           /*각 키가 눌렸을 때 행동 지정.*/
//			case KEY_VOLUMEUP: 
//               printf("volume key : ");
//            break; 
//			case KEY_HOME: 
//                printf("Home key : ");
//            break;
//			case KEY_SEARCH:
//                printf("Search key : ");                    
//            break;
//			case KEY_BACK:
//                printf("Back key : ");                                     
//                return NULL;    //빠져나감.
//            break;
//			case KEY_MENU: 
//                printf("Menu key : ");                     
//            break;
//			case KEY_VOLUMEDOWN:
//                printf("Volume down key :");
//            break;
//		}
//    }
//    return NULL;
//}

/*---------------------------------------*/

/*------------ 버튼 SEARCH ---------------*/
void BT_SEARCH(void)
{
        /*버튼 전용 변수*/
	struct input_event stEvent;
	BUTTON_MSG_T msgRx;
	int msgID = msgget ((key_t)MESSAGE_ID, IPC_CREAT|0666);
    /*------------*/
    /*무한루프*/
    while(1)
    {
        writeLCD(1, "search");
        int returnValue = 0 ;
		returnValue = msgrcv(msgID, &msgRx, sizeof(int), 0 ,0);

		switch(msgRx.keyInput)
		{
            /*각 키가 눌렸을 때 행동 지정.*/
			case KEY_VOLUMEUP: 
                printf("volume key : ");
            break; 
			case KEY_HOME: 
			BT_HOME();
                printf("Home key : ");
            break;
			case KEY_SEARCH:
                printf("Search key : ");                    
            break;
			case KEY_BACK:
                printf("Back key : ");                                     
                return NULL;    //빠져나감.
            break;
			case KEY_MENU: 
                printf("Menu key : ");                     
            break;
			case KEY_VOLUMEDOWN:
                printf("Volume down key :");
            break;
		}
    }
    return NULL;
}
/*---------------------------------------*/

/*------------ 버튼 menu ---------------*/
void BT_MENU(void)
{
        /*버튼 전용 변수*/
	struct input_event stEvent;
	BUTTON_MSG_T msgRx;
	int msgID = msgget ((key_t)MESSAGE_ID, IPC_CREAT|0666);
    /*------------*/
    /*무한루프*/
    while(1)
    {
        writeLCD(1, "menu");
        int returnValue = 0 ;
		returnValue = msgrcv(msgID, &msgRx, sizeof(int), 0 ,0);

		switch(msgRx.keyInput)
		{
            /*각 키가 눌렸을 때 행동 지정.*/
			case KEY_VOLUMEUP: 
                printf("volume key : ");
            break; 
			case KEY_HOME: 
			BT_HOME();
                printf("Home key : ");
            break;
			case KEY_SEARCH:
                printf("Search key : ");                    
            break;
			case KEY_BACK:
                printf("Back key : ");                                     
                return NULL;    //빠져나감.
            break;
			case KEY_MENU: 
                printf("Menu key : ");                     
            break;
			case KEY_VOLUMEDOWN:
                printf("Volume down key :");
            break;
		}
    }
    return NULL;
}
/*---------------------------------------*/

/*------------ 버튼 VOL_UP ---------------*/
void BT_VOL_UP(void)
{
        /*버튼 전용 변수*/
	struct input_event stEvent;
	BUTTON_MSG_T msgRx;
	int msgID = msgget ((key_t)MESSAGE_ID, IPC_CREAT|0666);
    /*------------*/
    /*무한루프*/
    while(1)
    {
        writeLCD(1, "volup");
        int returnValue = 0;
		returnValue = msgrcv(msgID, &msgRx, sizeof(int), 0 ,0);

		switch(msgRx.keyInput)
		{
            /*각 키가 눌렸을 때 행동 지정.*/
			case KEY_VOLUMEUP: 
                printf("volume key : ");
            break; 
			case KEY_HOME: 
			BT_HOME();
                printf("Home key : ");
            break;
			case KEY_SEARCH:
                printf("Search key : ");                    
            break;
			case KEY_BACK:
                printf("Back key : ");                                     
                return NULL;    //빠져나감.
            break;
			case KEY_MENU: 
                printf("Menu key : ");                     
            break;
			case KEY_VOLUMEDOWN:
                printf("Volume down key :");
            break;
		}
    }
    return NULL;
}
/*---------------------------------------*/

/*------------ 버튼 VOL_DOWN ---------------*/
void BT_VOL_DOWN(void)
{
        /*버튼 전용 변수*/
	struct input_event stEvent;
	BUTTON_MSG_T msgRx;
	int msgID = msgget ((key_t)MESSAGE_ID, IPC_CREAT|0666);
    /*------------*/
    /*무한루프*/
    while(1)
    {
        writeLCD(1, "vol_down");
        int returnValue = 0 ;
		returnValue = msgrcv(msgID, &msgRx, sizeof(int), 0 ,0);

		switch(msgRx.keyInput)
		{
            /*각 키가 눌렸을 때 행동 지정.*/
			case KEY_VOLUMEUP: 
                printf("volume key : ");
            break; 
			case KEY_HOME: 
			BT_HOME();
                printf("Home key : ");
            break;
			case KEY_SEARCH:
                printf("Search key : ");                    
            break;
			case KEY_BACK:
                printf("Back key : ");                                     
                return NULL;    //빠져나감.
            break;
			case KEY_MENU: 
                printf("Menu key : ");                     
            break;
			case KEY_VOLUMEDOWN:
                printf("Volume down key :");
            break;
		}
    }
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
    accelInit();
    magInit();
    gyroInit();
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
    fndOff();
    textLCD_off();
}


int main(void){
    /*스타트*/
    AllDeviceInit();
    bitmainfunc("test.bmp");
    //--------------
    /*스레드 전용 변수
    int err;
    if (pthread_mutex_init(&lock, NULL) != 0)   //스레드 초기화
    {
        printf ("\n Mutex Init Failed!!\n");
        return 1;
    }
*/
    /*버튼 전용 변수*/
	struct input_event stEvent;
	BUTTON_MSG_T msgRx;
	int msgID = msgget ((key_t)MESSAGE_ID, IPC_CREAT|0666);
    /*------------*/
    BT_HOME();
    /*무한루프*/
    while(1)
	{  
		int returnValue = 0;
		returnValue = msgrcv(msgID, &msgRx, sizeof(int), 0 ,0);
			switch(msgRx.keyInput)
			{
                /*각 키가 눌렸을 때 행동 지정.*/
				case KEY_VOLUMEUP: 
                    printf("Volume up key : "); 
                    BT_VOL_UP();
                break; 
				case KEY_HOME: 
                    printf("Home key : ");
                    BT_HOME();
                break;
				    case KEY_SEARCH:
                    printf("Search key : ");
                    BT_SEARCH();
                break;
				case KEY_BACK:
                    printf("Back key : ");
//                    BT_BACK();
                break;
				case KEY_MENU: 
                    printf("Menu key : ");
                    BT_MENU();
                break;
				case KEY_VOLUMEDOWN:
                    printf("Volume down key):");
                    BT_VOL_DOWN();
                break;
			}
	}


    /*종료료*/

    AllDeviceClose();
    return 0;
}


