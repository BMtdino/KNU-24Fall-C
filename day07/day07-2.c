#include<stdio.h>
#include<stdlib.h>;
#include<time.h>
#include<math.h>

int main(void) {
	long long lteration_total = 1000000000;
	long long checkpoint = 10000000;

	double x = 0;
	double y = 0;

	int count = 0, circle = 0;

	srand(time(NULL));

	while (count < 10000) {
		x = (double)rand() / (double)RAND_MAX;
		y = (double)rand() / (double)RAND_MAX;
		count++;
	}

	for (long long i = 1; i <= lteration_total; i++) {
		if (i % checkpoint == 0) {
			double pi_estimate = 4.0 * inside_circle / i;  // �� ����
			printf("%lld\%���� / %lld, ������: %.8f\n", i/lteration_total, pi_estimate);
		}
	}
}