#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(void) {
    long long Iteration_total = 1000000000;
    long long checkpoint = 10000000;

    double x = 0;  // x 좌표
    double y = 0;  // y 좌표

    long long count = 0, circle = 0;

    int nowpersent = 0;

    srand(time(NULL));

    for (long long i = 1; i <= Iteration_total; i++){
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;

        if (x * x + y * y <= 1) {
            circle++;
        }

        if (i % checkpoint == 0) {
            double pi_estimate = 4.0 * circle / i;
            nowpersent++;
            printf("%d%%진행.. 원주율 : %.6f ", nowpersent, pi_estimate);
            for (int j = 1; j <=  20; j++) {
                if (j * 5 <= nowpersent) {
                    printf("■");
                }
                else {
                    printf("□");
                }
            }
            printf("\n");
        }
    }

    double pi_estimate = 4.0 * (double)circle / (double)Iteration_total;
    printf("원주율: %.6f\n", pi_estimate);

    return 0;
}
