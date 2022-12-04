#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include "myMessage.h"

int main(void){
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
		
		printf("%s\r\n", (char*)shmemAddr);//메세지 내용 출력

		int returnValue=0;
		returnValue= msgrcv(msgQueue, &messageRxData, sizeof(messageRxData.piggyBlack),0,0);
		
		//if(returnValue){ //메세지 올때까지 기다리면서 메세지 받음
		//if(returnValue==-1)break;//받은게 없으면 멈춤
		printf("%s\r\n", messageRxData.piggyBlack);//쌓인 메세지 갯수출력 //car is overturned [z값]출력
	//}
}
