#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	const char* readFileName;
	FILE* readFile;

	if (argc < 2)
	{
		puts("»ç¿ë¹ý : filename");
		return 0;
	}

	readFileName = argv[1];

	// read file
	if ((readFile = fopen(readFileName, "r")) == NULL)
	{
		printf("cannot open file %s\n", readFileName);
		return 0;
	}

	fseek(readFile, 0, SEEK_END);
	printf("filesize : %d\n", ftell(readFile));
	
	fclose(readFile);
}