#include<stdio.h>
#include<stdlib.h>

int main() {
	int N;
	int* snum;
	int* score;
	char** name;

	int num = 0, average = 0, min = 0, max = 0;

	printf("�л� �� �Է� : ");
	scanf_s("%d", &N);

	snum = (int*)malloc(N * sizeof(int));
	score = (int*)malloc(N * sizeof(int));
	name = (char**)malloc(N * sizeof(char*));

	for (int i = 0; i < N; i++) {
		name[i] = (char*)malloc(100 * sizeof(char));
	}

	for (int i = 0; i < N; i++) {
		printf("�л�%d�� �й�, �̸�, ������ �Է��ϼ���.\n", i + 1);

		printf("�й� : ");
		scanf_s("%d", &snum[i]);

		printf("�̸� : ");
		scanf_s("%s", name[i], 100);

		printf("���� : ");
		scanf_s("%d", &score[i]);

		num += score[i];
		if (i == 0) {
			max = score[i];
			min = score[i];
		}
		else {
			if (max >= score[i]) {
				max = max;
			}
			else {
				max = score[i];
			}

			if (min <= score[i]) {
				min = min;
			}
			else {
				min = score[i];
			}
		}
	}
	average = num / N;
	for (int i = 0; i < N; i++) {
		printf("%d %s %d\n", snum[i], name[i], score[i]);
	}
	printf("�ִ� : %d\n", max);
	printf("�ּ� : %d\n", min);
	printf("��� : %d\n", average);
	/*
	int arr[10];

	int* arr2;
	arr2 = (int*)malloc(10 * sizeof(int));

	for (int i = 0; i < 10; i++) {
		arr[i] = i;
		arr2[i] = i;
	}
	for (int i = 0; i < 10; i++) {
		printf("%d, %d\n", arr[i], arr2[i]);
	}

	free(arr2);
	arr2 = NULL;
	*/
}