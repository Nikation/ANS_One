#include<iostream>
#include<stdio.h>
#include<string>

//п╢нд╪Ч
int writecodeTofile(const char* filepath, unsigned char *data, int dataLen)
{
	FILE *fp = NULL;
	fp = fopen(filepath, "w");
	if (NULL == fp)
	{
		printf("fopen failed ..\n");
		return 1;
	}

	fwrite(data, sizeof(char), dataLen, fp);

	fclose(fp);
	return 0;
}