#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	const char* readFileName, *writeFileName;
	FILE* readFile, *writeFile;

	if (argc < 3)
	{
		puts("사용법 : srcfile dstfile");
		return 0;
	}

	readFileName = argv[1];
	writeFileName = argv[2];

	// read file
	if ((readFile = fopen(readFileName, "r")) == NULL)
	{
		printf("cannot open file %s\n", readFileName);
		return 0;
	}

	writeFile = fopen(writeFileName, "a");

	// 한 글자씩 writefile의 뒤에 추가
	while (!feof(readFile))
	{
		fputc(fgetc(readFile), writeFile);
	}

	fclose(readFile);
	fclose(writeFile);
}