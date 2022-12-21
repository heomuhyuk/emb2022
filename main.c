/*
2022년 임베디드 시스템 프로젝트 데모 코드입니다.
작성자 -권예찬, 박문수, 허무혁, 황찬동-
연구 주제 : 카 인포테이먼트
간략 설명 : 버튼을 누르면 모드가 바뀌고 모드에 해당하는 센서의 값을 읽어 작동.
모드 1. 메인화면(온도, 시간, 날짜, 가속도에 해당하는 정보 표시)
모드 2. 모드선택(버튼으로 조작)
모드 3. 음악재생(vlc 이용)
모드 4. 미니게임(간단한 bit맵과 버튼을 이용한 게임)
모드 5. 조명선택(버튼으로 color led 조작)
*/
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
#define MAX_SCALE_STEP 8
static const int musicScale[MAX_SCALE_STEP] =
{
    262, /*do*/ 294,330,349,392,440,494, /* si */ 523
};

/*------------ 버튼 home ---------------*/
/*메인 (이)가 돌아가는 부분임.*/
void BT_HOME(void)
{
    bitmainfunc("mainmode.bmp");
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

        int *data;
        data = accelRead();
        if(data[0]>5000 || data[0] <-5000){
            bitmainfunc("warning.bmp");
            buzzerPlaySong(musicScale[1]);
            sleep(1);
            buzzerStopSong();
        }
        printf("print accel :: %d\n",data[0]);
    
        int returnValue = 0 ;
	    returnValue = msgrcv(msgID, &msgRx, sizeof(int), 0 ,IPC_NOWAIT);

	    switch(msgRx.keyInput)
	    {
            /*각 키가 눌렸을 때 행동 지정.*/
		    case KEY_VOLUMEUP: 
                //printf("volume key : ");
                thermal = temp_read();
                if (status != 1){
		            status = 1;
	                writeLCD(1, "                           ");
                    writeLCD(2, "                           ");
                    /*온도 센싱*/
		            writeLCD(1, "temperature");
                    printf("temperature : %f\n", temp_read());
                    if(temp_read() > 30){
                        bitmainfunc("warning.bmp");
                        buzzerPlaySong(musicScale[1]);
                        sleep(1);
                        buzzerStopSong();
                    }
	            }
                fndDisp(thermal , 0b00000);
            break; 
		    case KEY_HOME: 
                //printf("Home key : ");
                //BT_HOME();
            break;
		    case KEY_SEARCH:
            /*날짜 표기*/       
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
            /*모드 선택으로*/ 
                printf("Search Menu \n");    
                BT_SEARCH();         
            break;
            case KEY_VOLUMEDOWN:
            /*시간 표시*/
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

/*------------ 버튼 SEARCH ---------------*/
/*모드 선택*/
void BT_SEARCH(void)
{
    bitmainfunc("main.bmp");
        /*버튼 전용 변수*/
	struct input_event stEvent;
	BUTTON_MSG_T msgRx;
	int msgID = msgget ((key_t)MESSAGE_ID, IPC_CREAT|0666);
    /*------------*/
    /*무한루프*/
    while(1)
    {
         bitmainfunc("main.bmp");
		writeLCD(1, "                  ");
        writeLCD(2, "                  ");
        writeLCD(1, "search menu");
        int returnValue = 0 ;
		returnValue = msgrcv(msgID, &msgRx, sizeof(int), 0 ,0);

		switch(msgRx.keyInput)
		{
            /*각 키가 눌렸을 때 행동 지정.*/
			case KEY_VOLUMEUP: 
                printf("volume key : ");
                BT_VOL_UP();
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
                BT_MENU();                     
            break;
			case KEY_VOLUMEDOWN:
                printf("Volume down key :");
                BT_VOL_DOWN();
            break;
		}
    }
    return NULL;
}
/*---------------------------------------*/

/*------------ 버튼 menu ---------------*/
/*미니게임 실행*/
void BT_MENU(void)
{
    bitmainfunc("game.bmp");
        /*버튼 전용 변수*/
	struct input_event stEvent;
	BUTTON_MSG_T msgRx;
	int msgID = msgget ((key_t)MESSAGE_ID, IPC_CREAT|0666);
    /*------------*/
    /*무한루프*/

    int select, game_start, score;
    while(1)
    {
        writeLCD(1, "                  ");
        writeLCD(2, "                  ");
        writeLCD(1, "game play");
        writeLCD(2, "volup button");
        usleep(50000);
        fndDisp(score , 0);
        select = rand()%10;
        printf("%d", select);
        if(game_start == 1){
        if(select < 5)
            bitmainfunc("hit.bmp");
        else if(select == 8)
            bitmainfunc("miss.bmp");
        else 
            bitmainfunc("game_default.bmp");
        }

        int returnValue = 0 ;
		returnValue = msgrcv(msgID, &msgRx, sizeof(int), 0 , IPC_NOWAIT);

		switch(msgRx.keyInput)
		{
            /*각 키가 눌렸을 때 행동 지정.*/
			case KEY_VOLUMEUP: 
                printf("volume key : game start");
                game_start = 1;
                    writeLCD(1, "                  ");
                    writeLCD(2, "                  ");
                    writeLCD(1, "hit");
                    writeLCD(2, "press home_key");
                score = 200;
            break; 
			case KEY_HOME: 
                printf("Home key : hit");
                writeLCD(1, "                  ");
                writeLCD(2, "                  ");
                writeLCD(1, "playing");
                writeLCD(2, "stop voldown");
                if(game_start == 1){
                    if(select < 5)score = score + 10;
                    else score = 0;                
                    }
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
                printf("Volume down key : game stop");
                writeLCD(1, "                  ");
                writeLCD(2, "                  ");
                writeLCD(1, "return home");
                writeLCD(2, "press back");
                game_start = 0;
                score = 0;
            break;
		}
    }
    return NULL;
}
/*---------------------------------------*/

/*------------ 버튼 VOL_UP ---------------*/
/*음악 재생*/
void BT_VOL_UP(void)
{
    bitmainfunc("music.bmp");
        /*버튼 전용 변수*/
	struct input_event stEvent;
	BUTTON_MSG_T msgRx;
	int msgID = msgget ((key_t)MESSAGE_ID, IPC_CREAT|0666);
    /*------------*/
    /*무한루프*/
    while(1)
    {
        writeLCD(1, "                  ");
        writeLCD(2, "                  ");
        writeLCD(1, "music play");
        writeLCD(2, "press bt_munu");
        int returnValue = 0 ;
		returnValue = msgrcv(msgID, &msgRx, sizeof(int), 0 ,0);
        int a;
        pid_t pid;
		switch(msgRx.keyInput)
		{
            /*각 키가 눌렸을 때 행동 지정.*/
			case KEY_VOLUMEUP: 
                printf("");
            break; 
			case KEY_HOME: 
                system("killall -9 vlc");   //종료
                //BT_HOME();
            break;
			case KEY_SEARCH:
                printf("");                  
            break;
			case KEY_BACK:
                printf("Back key : ");                                     
                return NULL;    //빠져나감.
            break;
			case KEY_MENU: 
                writeLCD(1, "                  ");
                writeLCD(2, "                  ");
                writeLCD(1, "volup");
                writeLCD(2, "music");
                
                /*사실 fork 필요없는거 같습니다.*/
                pid = fork();
                if(pid>0){
                    printf("play music");
                }   //parent
                if(pid == 0){
                    system("vlc sample.mp3");   //재생
                }
                              
            break;
			case KEY_VOLUMEDOWN:
                printf("");
            break;
		}
    }
    return NULL;
}
/*---------------------------------------*/

/*------------ 버튼 VOL_DOWN ---------------*/
/*조명 선택*/
void BT_VOL_DOWN(void)
{
    bitmainfunc("ambient.bmp");
        /*버튼 전용 변수*/
	struct input_event stEvent;
	BUTTON_MSG_T msgRx;
	int msgID = msgget ((key_t)MESSAGE_ID, IPC_CREAT|0666);
    /*------------*/
    /*무한루프*/
    while(1)
    {
        writeLCD(1, "                  ");
        writeLCD(2, "                  ");
        writeLCD(1, "ambient mode");
        int returnValue = 0 ;
		returnValue = msgrcv(msgID, &msgRx, sizeof(int), 0 ,0);

		switch(msgRx.keyInput)
		{
            /*각 키가 눌렸을 때 행동 지정.*/
			case KEY_VOLUMEUP: 
                printf("candela up : ");
            break; 
			case KEY_HOME: 
				pwmLedInit();
                writeLCD(2, "red");
				printf("ambientlight r");
				pwmSetPercent(50,0); //r
				pwmSetPercent(0,1); //g
				pwmSetPercent(0,2); //b
				sleep(1);
				pwmInactiveAll();
            break;
			case KEY_SEARCH:
				pwmLedInit();
                writeLCD(2, "green");
				printf("ambientlight g");
				pwmSetPercent(0,0); //r
				pwmSetPercent(50,1); //g
				pwmSetPercent(0,2); //b
				sleep(1);
				pwmInactiveAll();                    
            break;
			case KEY_BACK:
                printf("Back key : ");                                     
                return NULL;    //빠져나감.
            break;
			case KEY_MENU: 
                pwmLedInit();
                writeLCD(2, "blue");
				printf("ambientlight b");
				pwmSetPercent(0,0); //r
				pwmSetPercent(0,1); //g
				pwmSetPercent(50,2); //b
				sleep(1);
				pwmInactiveAll();                    
            break;
			case KEY_VOLUMEDOWN:
                printf("candela down :");
            break;
		}
    }
    return NULL;
}
/*---------------------------------------*/

/*시작 할때 드라이버 세팅 해주는 함수.*/
void AllDeviceInit()
{
    /*편의를 위해 모듈형 삽입을 system으로 했음.*/
    system("insmod buttondrv.ko");
    system("insmod buzzerdrv.ko");
    system("insmod leddrv.ko");
    system("insmod textlcddrv.ko");
    system("insmod fnddrv.ko");
    /*활성화*/
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
/*모두 닫기*/
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
    bitmainfunc("main.bmp");
    /*버튼 전용 변수*/
	struct input_event stEvent;
	BUTTON_MSG_T msgRx;
	int msgID = msgget ((key_t)MESSAGE_ID, IPC_CREAT|0666);
    /*------------*/
    BT_HOME();  //시작하면 홈으로 이동.
    /*무한루프*/
    /*밑의 무한 루프 돌지 않음. 에러발생시 확인용으로 남겨둠.*/
    while(1)
	{  
        bitmainfunc("main.bmp");
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
    /*종료*/
    AllDeviceClose();
    return 0;
}

