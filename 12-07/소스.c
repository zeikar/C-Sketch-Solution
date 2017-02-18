#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	const char* readFileName, *searchString;
	FILE* readFile;
	char buffer[1000];
	int rowCount = 1;

	if (argc < 3)
	{
		puts("사용법 : srcfile string");
		return 0;
	}

	readFileName = argv[1];
	searchString = argv[2];

	// read file
	if ((readFile = fopen(readFileName, "r")) == NULL)
	{
		printf("cannot open file %s\n", readFileName);
		return 0;
	}

	printf("찾을 단어 %s, 길이 : %d\n", searchString, strlen(searchString));

	puts("\n검색 내용 출력 : -->\n");

	// 한 줄씩 읽어옴
	while (!feof(readFile))
	{
		fgets(buffer, 1000, readFile);

		if (strstr(buffer, searchString) != NULL)
		{
			printf("%d : %s", rowCount, buffer);
		}

		++rowCount;
	}

	fclose(readFile);
}