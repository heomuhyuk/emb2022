#ifndef _TEXTLCD_H_
#define _TEXTLCD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define TEXTLCD_DRIVER_NAME		"/dev/peritextlcd"
#define LINE_NUM			2
#define COLUMN_NUM			16	

#define  LINE_BUFF_NUM 	(COLUMN_NUM + 4)  //for dummy

#define  MODE_CMD	0
#define  MODE_DATA	1

#define  CMD_DISPLAY_MODE		0x10       //cmd  cmd data
	#define  BIT_DISPLAY_MODE_CURSOR_DISP	0x01  //커서 깜빡임 조절
	#define  BIT_DISPLAY_MODE_CURSOR_BLINK	0x02
	#define  BIT_DISPLAY_MODE_DISP_ENABLE	0x04

#define  CMD_CURSOR_MOVE_MODE	0x11
	#define CURSOR_MOVE_MODE_ENABLE		0x01
	#define CURSOR_MOVE_MODE_RIGHT_DIR	0x02

#define  CMD_CURSOR_MOVE_POSITION	0x12
	#define  CURSOR_MOVE_X_MASK		0x3F
	#define  CURSOR_MOVE_Y_MASK		0xC0
	
#define  CMD_WRITE_STRING			0x20	  
	#define CMD_DATA_WRITE_BOTH_LINE	0   //두라인다 나온다
	#define CMD_DATA_WRITE_LINE_1		1   //위에쪽 라인만 나온다
	#define CMD_DATA_WRITE_LINE_2		2   //아래쪽 라인만 나온다
	
#define  CMD_TEST_GPIO_HIGH			0x30
#define  CMD_TEST_GPIO_LOW			0x31

typedef struct TextLCD_tag 
{
	unsigned char cmd; 
	unsigned char cmdData;  
	unsigned char reserved[2];  //넣어주면안된다 4byte 만드려고 보호해놓은 바이트
	
	char	TextData[LINE_NUM][LINE_BUFF_NUM]; //16+4=20byte 마진 
}stTextLCD,*pStTextLCD;

void doHelp(void);
void writeLCD(int linenum , char *str);
int textLCD_Init(void);
void textLCD_off(void);


#endif
