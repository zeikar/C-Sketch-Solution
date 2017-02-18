#include <stdio.h>
#include <stdlib.h>

const char* grade[] = {"A+", "A0", "B+", "B0", "C+", "C0", "D+", "D0", "F"};

const char* getScore(double score)
{
	int standard = 95;

	// 학점 계산
	for (int i = 0; i < 8; ++i)
	{
		if (score >= standard - 5 * i)
		{
			return grade[i];
		}
	}
	return grade[8];
}

int main()
{
	const char* readFileName = "12-12-read.txt", *writeFileName = "12-12-write.txt";
	FILE* readFile, *writeFile;

	// read file
	if ((readFile = fopen(readFileName, "r")) == NULL)
	{
		printf("cannot open file %s\n", readFileName);
		return 0;
	}

	writeFile = fopen(writeFileName, "w");

	fputs("순번 학번 성명 중간 기말 과제 출석 총합, 학점\n", writeFile);

	// 한 글자씩 writefile의 뒤에 추가
	while (!feof(readFile))
	{
		int no, id, mid, final, assignment1, assignment2, attendance;
		char name[40];
		fscanf(readFile, "%d %d %s %d %d %d %d %d", &no, &id, name, &mid, &final, &assignment1, &assignment2, &attendance);

		double totalScore = mid * 0.3 + final * 0.4 + (assignment1 + assignment2) / 60.0 * 20 + attendance / 10.0 * 10;

		fprintf(writeFile, "%2d %d %s %10f %10f %10f %10f %10f %2s\n", no, id, name, mid * 0.3, final * 0.4, (assignment1 + assignment2) / 60.0 * 20, attendance / 10.0 * 10, totalScore, getScore(totalScore));
	}

	fclose(readFile);
	fclose(writeFile);
}