#include "textlcd.h"

unsigned int linenum = 0;
stTextLCD stlcd;
int fd;
int len;

void doHelp(void)
{
	printf("usage: textlcdtest <option> <linenum> <'string'>\n");
	printf("       				option = 0 or 1\n");
	printf("       				option = 0 : ERASE\n");
	printf("       				option = 1 : WR\n");
	printf("       					     linenum => 1 ~ 2\n");
	printf("  ex) textlcdtest 2 'test hello'\n");
}

int textLCD_Init(void)
{
	fd = open(TEXTLCD_DRIVER_NAME, O_RDWR);
	if (fd < 0)
	{
		perror("driver (//dev//peritextlcd) open error.\n");
		return 1;
	}
	memset(&stlcd, 0, sizeof(stTextLCD));
}

void writeLCD(int linenum, char *str)
{
	printf("linenum :%d\n", linenum);

	if (linenum == 1)
	{ // firsst line
		stlcd.cmdData = CMD_DATA_WRITE_LINE_1;
	}
	else if (linenum == 2)
	{ // second line
		stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
	}
	else
	{
		printf("linenum : %d  wrong .  range (1 ~ 2)\n", linenum);
	}

	printf("LCD Write:%s\n", str);
	len = strlen(str);
	if (len > COLUMN_NUM)
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1], str, COLUMN_NUM);
	}
	else
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1], str, len);
	}
	stlcd.cmd = CMD_WRITE_STRING;

	write(fd, &stlcd, sizeof(stTextLCD));
}

void textLCD_off(void)
{
	char str[] = {"                  "};
	writeLCD(1, str);
	writeLCD(2, str);
	close(fd);
}