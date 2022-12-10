#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
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
#define MY_MESSAGE_ID 8282
typedef struct{
long int messageType;
char piggyBlack[1000];

} structMyMsg;

/*------------ 버튼 home ---------------*/
void BT_HOME(void)
{
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
        writeLCD(1, "home");
        int returnValue = 0 ;
		returnValue = msgrcv(msgID, &msgRx, sizeof(int), 0 ,0);

		switch(msgRx.keyInput)
		{
            /*각 키가 눌렸을 때 행동 지정.*/
			case KEY_VOLUMEUP: 
                printf("volume key : ");
            break; 
			case KEY_HOME: 
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

/*------------ 버튼 BACK ---------------*/
void BT_BACK(void)
{
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
        writeLCD(1, "BACK");
        int returnValue = 0 ;
		returnValue = msgrcv(msgID, &msgRx, sizeof(int), 0 ,0);

		switch(msgRx.keyInput)
		{
            /*각 키가 눌렸을 때 행동 지정.*/
			case KEY_VOLUMEUP: 
                printf("volume key : ");
            break; 
			case KEY_HOME: 
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
        writeLCD(1, "                  ");
        writeLCD(2, "                  ");
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
        writeLCD(1, "                  ");
        writeLCD(2, "                  ");
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
        writeLCD(1, "                  ");
        writeLCD(2, "                  ");
        writeLCD(1, "volup");
        writeLCD(2, "music");
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
                printf("");
            break;
			case KEY_SEARCH:
                printf("");                  
            break;
			case KEY_BACK:
				printf("Back key : ");                                     
                return NULL;    //빠져나감.
            break;
			case KEY_MENU: 
                
                pid = fork();
                if(pid>0){
                    printf("play music");
                }   //parent
                if(pid == 0){
                    system("vlc sample.mp3");  
                }
                              
            break;
			case KEY_VOLUMEDOWN:
                printf("");
                system("");
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
				printf("ambientlight r");
				pwmSetPercent(50,0); //r
				pwmSetPercent(0,1); //g
				pwmSetPercent(0,2); //b
				sleep(1);
				pwmInactiveAll();
            break;
			case KEY_SEARCH:
				pwmLedInit();
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
    system("insmod buttondrv.ko");
    system("insmod buzzerdrv.ko");
    system("insmod leddrv.ko");
    system("insmod textlcddrv.ko");
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

	structMyMsg messageRxData;
	int msgQueue = msgget((key_t)MY_MESSAGE_ID, IPC_CREAT|0666);//메세지큐 id를 얻음, 반환 메세지큐 식별자

	if(msgQueue==-1){
	printf("Cannot get msgQueue ID \r\n");
	return -1;//실패시 에러 메세지 출력 후 -1 반환
	}

	int shmId =shmget((key_t)1234,1024,IPC_CREAT|0666);//공유 메모리 생성
	if (shmId==-1){
	printf("shmget Error!\r\n");
	return 1;//shmId가 -1이면 에러 메세지 출력(공유메모리 생성 실패) 후 1 반환
	}

	char *shmemAddr;//공유 메모리 주소 값 연결할 포인터변수
	shmemAddr = shmat(shmId, (void*)NULL,0);//위 포인터 변수에 공유 메모리 주소 저장
	if(((int)(shmemAddr))==-1){
	printf("shmat Erro!\r\n");
	return -2;//shmAddr이 -1이면(실패시)  에러메세지 출력 후 -2 반환
	}
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
        writeLCD(1, "HELLO");
		int returnValue1 = 0 ;
printf("%s\r\n", (char*)shmemAddr);//메세지 내용 출력

		returnValue1= msgrcv(msgQueue, &messageRxData, sizeof(messageRxData.piggyBlack),0,0);
		
		//if(returnValue){ //메세지 올때까지 기다리면서 메세지 받음
		//if(returnValue==-1)break;//받은게 없으면 멈춤
		printf("%s\r\n", messageRxData.piggyBlack);//쌓인 메세지 갯수출력
		//returnValue = msgrcv(msgID, &msgRx, sizeof(int), 0 ,0);
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
                    BT_BACK();
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


