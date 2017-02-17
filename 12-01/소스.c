#include <stdio.h>
#include <stdlib.h>

int main()
{
	const char* readFileName = "12-01-read.txt", *writeFileName = "12-01-write.txt";
	FILE* readFile, *writeFile;

	// read a file
	if ((readFile = fopen(readFileName, "r")) == NULL)
	{
		puts("cannot open file");
		return 0;
	}

	// file to write
	writeFile = fopen(writeFileName, "w");

	// readline
	while (!feof(readFile))
	{
		int studentId;
		char name[20];
		double score, sum = 0;

		fscanf(readFile, "%d %s", &studentId, name);
		fprintf(writeFile, "%d %s ", studentId, name);

		for (int i = 0; i < 3; ++i)
		{
			fscanf(readFile, "%lf", &score);
			fprintf(writeFile, "%lf ", score);

			sum += score;

		}

		// write to file
		fprintf(writeFile, "sum : %lf\n", sum);
	}

	fclose(readFile);
	fclose(writeFile);
}