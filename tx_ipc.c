#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<sys/shm.h>
#include"myMessage.h"
///////////////////////////////////////////////////////////////////////////////
int *data;

#define MAX_SCALE_STEP 8
static const int musicScale[MAX_SCALE_STEP] =
{
    262, /*do*/ 294,330,349,392,440,494, /* si */ 523
};
///////////////////////////////////////////////////////////////////////////////

int main(void){
	structMyMsg messageTxData;
	int msgQueue = msgget((key_t)MY_MESSAGE_ID, IPC_CREAT|0666);

	if(msgQueue==-1){
	printf("Cannot get msgQueue ID \r\n");
	return -1;//실패시 에러 메세지 출력 후 -1 반환
	}


	int shmId =shmget((key_t)1234,1024,IPC_CREAT|0666);//공유 메모리 생성
	if (shmId ==-1){
	printf("shmget Error!\r\n");
	return 1;//shmId가 -1이면 에러 메세지 출력(공유메모리 생성 실패) 후 -1 반환
	}

	char *shmemAddr;//공유 메모리 주소 값 연결할 포인터변수
	shmemAddr = shmat(shmId, (void*)NULL,0);//위 포인터 변수에 공유 메모리 주소 저장
	if(((int)(shmemAddr))==-1){
	printf("shmat Erro!\r\n");
	return -2;//shmAddr이 -1이면 에러메세지 출력 후 -2 반환
	}


	if(accelInit() != 0)
	{
		printf("Accelerometer Init failed!\n");
		exit(-1);
	}

	while(1){

	data = accelRead();
	printf("Accel data is: %d\r\n",data[0]);
	
////	count++;// 한 번 보낼 때마다 카운트 1증가
////	printf("write message: ");//출력
////	scanf("%s", &msg_in);//키보드 입력을 msg_in에 저장	
	char msg_in[200];//입력 메세지 저장할 공간
	

	
	
	int check = data[0];
	if(check<0){  //if 조건부는 z값 확인 후 변경( z축 -9.8xxxxx ?? )

    msg_in[200]=data[0];//data[0]가 z축이라고 가정
    sprintf((char*) shmemAddr, "%s", msg_in);//shmemAddr에 msg_in 저장 	
    buzzerPlaySong(musicScale[1]);
    snprintf(messageTxData.piggyBlack, sizeof(messageTxData.piggyBlack)-1,"car is overturned [%d]",data[0]);
	//messageTxData.piggyBlack에 hello....저장된 메세지
	messageTxData.messageType=1;//1is good enough
	////printf("\tsending %d message\r\n",count);// 메세지 보냄 표시(표준출력에 출력)
	msgsnd(msgQueue, &messageTxData, sizeof(messageTxData.piggyBlack), 0);//보내고 싶은 메세지 보냄(단 앞4byt는 빼고)
	}
    }
}
