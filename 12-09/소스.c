#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct personscore
{
	int number;
	char name[40];
	int mid;
	int final;
	int quiz;
};
typedef struct personscore pscore;

void printhead();
void printscore(FILE* f);
void appendscore(FILE* f, int cnt);
void searchById(FILE* f, int id);

int main()
{
	char fname[] = "score.bin";
	FILE* f;
	int cnt = 0;
	long offset = 0;
	pscore score = { 0 };

	// if((f = fopen(fname, "a+")) == NULL)
	if (fopen_s(&f, fname, "a+") != 0)
	{
		printf("파일이 열리지 않습니다.\n");
		exit(1);
	}
	printscore(f);
	offset = (long) sizeof(pscore);			// 구조체 하나의 크기
	fseek(f, -offset, SEEK_CUR);			// 파일의 현재 포인터에서 한 학생만큼 뒤로 이동

	fread(&score, sizeof(pscore), 1, f);	// 그 학생(마지막 학생)을 읽음

	// 제일 마지막 자료의 번호를 찾기 위하여
	cnt = score.number;
	printf("\n제일 마지막 번호가 %d번 입니다.\n\n", cnt);

	while (1)
	{
		int command;

		puts("학생 번호 검색 : 1, 학생 추가 : 2, 종료 : 0 입력 >>");
		scanf(" %d", &command);

		if (command == 1)
		{
			int id;
			puts("검색할 학생 번호를 입력 >>");
			scanf("%d", &id);
			searchById(f, id);
		}
		else if (command == 2)
		{
			// 버퍼 비우기
			getchar();
			fseek(f, 0L, SEEK_END);
			appendscore(f, cnt);
			printscore(f);
		}
		else if (command == 0)
		{
			break;
		}
		else
		{
			puts("다시 입력하시오");
		}
	}
	fclose(f);

	return 0;
}

int fileSize(FILE* f)
{
	fseek(f, 0, SEEK_END);
	return ftell(f);
}

void searchById(FILE* f, int id)
{
	pscore score;
	long offset = (long) sizeof(pscore);			// 구조체 하나의 크기

	// 예외 처리
	if (id <= 0 || fileSize(f) <= offset * (id - 1))
	{
		puts("원하는 번호의 학생이 없습니다.");
		return;
	}

	fseek(f, offset * (id - 1), SEEK_SET);			// 파일의 처음 포인터에서 학생 번호만큼 뒤로 이동

	fread(&score, sizeof(pscore), 1, f);			// 그 학생(마지막 학생)을 읽음

	printhead();
	fprintf(stdout, "%6d%18s%8d%8d%8d\n", score.number, score.name, score.mid, score.final, score.quiz);
	fprintf(stdout, "%s\n", "---------------------------------------------------------");
}

void appendscore(FILE* f, int cnt)
{
	pscore score;
	char line[80];
	printf("추가할 이름과 성적(중간, 기말, 퀴즈)을 입력하세요.\n\n");
	fgets(line, 80, stdin);
	while (!feof(stdin))
	{
		sscanf_s(line, "%s %d %d %d", score.name, 40, &score.mid, &score.final, &score.quiz);
		score.number = ++cnt;
		fwrite(&score, sizeof(pscore), 1, f);
		fgets(line, 80, stdin);
	}
}

void printhead()
{
	printf("\n현재의 성적 내용은 >>\n");
	fprintf(stdout, "%s\n", "---------------------------------------------------------");
	fprintf(stdout, "%8s%15s%10s%8s%8s\n", "번호", "이름", "중간", "기말", "퀴즈");
	fprintf(stdout, "%s\n", "---------------------------------------------------------");
}

void printscore(FILE* f)
{
	pscore score;
	rewind(f);
	printhead();
	fread(&score, sizeof(pscore), 1, f);
	while (!feof(f))
	{
		// 표준출력에 쓰기
		fprintf(stdout, "%6d%18s%8d%8d%8d\n", score.number, score.name, score.mid, score.final, score.quiz);
		fread(&score, sizeof(pscore), 1, f);
	}
	fprintf(stdout, "%s\n", "---------------------------------------------------------");
}