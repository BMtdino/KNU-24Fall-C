#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Student {
	int snum;
	int score;
	char name[100];
};

int main() {
	int N;

	int num = 0, average = 0, min = 0, max = 0;

	printf("학생 수 입력 : ");
	scanf_s("%d", &N);

	struct Student* std = (struct Student*)malloc(N * sizeof(struct Student));

	for (int i = 0; i < N; i++) {
		printf("학생%d의 학번, 이름, 점수를 입력하세요.\n", i + 1);

		printf("학번 : ");
		scanf_s("%d", &std[i].snum);

		printf("이름 : ");
		scanf_s("%s", std[i].name, 100);

		printf("점수 : ");
		scanf_s("%d", &std[i].score);

		num += std[i].score;
		if (i == 0) {
			max = std[i].score;
			min = std[i].score;
		}
		else {
			if (max >= std[i].score) {
				max = max;
			}
			else {
				max = std[i].score;
			}

			if (min <= std[i].score) {
				min = min;
			}
			else {
				min = std[i].score;
			}
		}
	}
	average = num / N;
	for (int i = 0; i < N; i++) {
		printf("학번 : %d 이름 : %s 점수 : %d\n", std[i].snum, std[i].name, std[i].score);
	}
	printf("최대 : %d\n", max);
	printf("최소 : %d\n", min);
	printf("평균 : %d\n", average);
}