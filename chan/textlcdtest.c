#include "textlcd.h"
#include <string.h>
#include "stdio.h"

int main(int argc, char **argv)
{
	int line_number;
	char *str = malloc(sizeof(argv[3]) * 10);

	textLCD_Init();

	printf("LCD TEST\n");
	if (argc < 2)
	{
		doHelp();
		return 1;
	}

	line_number = atoi(argv[2]);
	printf("line_number :%d\n", line_number);
	strcpy(str, argv[3]);
	printf("string:%s\n", str);

	if (argv[1][0] == '0')
	{
		textLCD_off();
	}
	else if (argv[1][0] == '1')
	{
		writeLCD(line_number, str);
	}
	else
	{
		doHelp();
		perror("option error \n");
		return 1;
	}

	return 0;
}
