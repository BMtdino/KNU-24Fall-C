#include <stdio.h>

int solution(int N) {
    int battery_usage = 0;

    while (N > 0) {
        if (N % 2 == 0) {
            // �����̵� ����
            N /= 2;
        }
        else {
            // ���� �ʿ�
            N -= 1;
            battery_usage++;
        }
    }

    return battery_usage;
}

int main() {
    // �׽�Ʈ ���̽�
    printf("%d\n", solution(5));  // ���: 2
    printf("%d\n", solution(6));  // ���: 2
    printf("%d\n", solution(5000));  // ���: 5
    return 0;
}
