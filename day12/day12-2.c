#include <stdio.h>

int solution(int N) {
    int battery_usage = 0;

    while (N > 0) {
        if (N % 2 == 0) {
            // 순간이동 가능
            N /= 2;
        }
        else {
            // 점프 필요
            N -= 1;
            battery_usage++;
        }
    }

    return battery_usage;
}

int main() {
    // 테스트 케이스
    printf("%d\n", solution(5));  // 출력: 2
    printf("%d\n", solution(6));  // 출력: 2
    printf("%d\n", solution(5000));  // 출력: 5
    return 0;
}
