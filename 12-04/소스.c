#include <stdio.h>
#include <stdlib.h>

char toUpper(char ch)
{
	if (ch >= 'a' && ch <= 'z')
	{
		ch += 'A' - 'a';
	}

	return ch;
}

int main(int argc, char *argv[])
{
	const char* readFileName;
	FILE* readFile;

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

	puts("원래의 파일 내용 출력 :-->");

	// 한 글자씩 출력
	while (!feof(readFile))
	{
		putchar(fgetc(readFile));
	}

	fseek(readFile, 0, SEEK_SET);

	puts("\n변환된 파일 내용 출력 :-->");

	// 한 글자씩 읽어와서 대문자로 변환 후 출력
	while (!feof(readFile))
	{
		putchar(toUpper(fgetc(readFile)));
	}

	fclose(readFile);
}