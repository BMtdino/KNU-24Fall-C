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

	printf("�л� �� �Է� : ");
	scanf_s("%d", &N);

	struct Student* std = (struct Student*)malloc(N * sizeof(struct Student));

	for (int i = 0; i < N; i++) {
		printf("�л�%d�� �й�, �̸�, ������ �Է��ϼ���.\n", i + 1);

		printf("�й� : ");
		scanf_s("%d", &std[i].snum);

		printf("�̸� : ");
		scanf_s("%s", std[i].name, 100);

		printf("���� : ");
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
		printf("�й� : %d �̸� : %s ���� : %d\n", std[i].snum, std[i].name, std[i].score);
	}
	printf("�ִ� : %d\n", max);
	printf("�ּ� : %d\n", min);
	printf("��� : %d\n", average);
}