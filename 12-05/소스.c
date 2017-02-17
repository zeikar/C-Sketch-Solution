#include <stdio.h>
#include <stdlib.h>

int isAlpha(char ch)
{
	return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int isNotAlpha(char ch)
{
	return ch == 0 || ch == ' ' || ch == '\t' || ch == '\n';
}

int main(int argc, char *argv[])
{
	const char* readFileName;
	FILE* readFile;
	char buffer[1000];
	// 개수 세기
	int rowCount = 0, wordCount = 0, characterCount = 0;

	if (argc < 2)
	{
		puts("사용법 : filename");
		return 0;
	}

	readFileName = argv[1];

	// read file
	if ((readFile = fopen(readFileName, "r")) == NULL)
	{
		printf("cannot open file %s\n", readFileName);
		return 0;
	}

	// 한 줄씩 읽어옴
	while (!feof(readFile))
	{
		fgets(buffer, 1000, readFile);

		// 모든 문자들을 검사
		for (int i = 0; buffer[i]; ++i)
		{
			// 문자
			if (isAlpha(buffer[i]))
			{
				++characterCount;
			}
			// 뒤에 공백 문자가 있으면 단어
			if (isAlpha(buffer[i]) && isNotAlpha(buffer[i + 1]))
			{
				++wordCount;
			}
		}

		++rowCount;
	}

	printf("문자 수 : %d, 단어 수 : %d, 행 수 : %d\n", characterCount, wordCount, rowCount);

	fclose(readFile);
}