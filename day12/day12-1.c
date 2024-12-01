#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_TOPPING 100000 //토핑 최대 길이

int solution(int topping[], size_t topping_len) {
    int answer = 0;
    int left_counter[MAX_TOPPING + 1] = { 0 }; // 토핑 왼쪽부터
    int right_counter[MAX_TOPPING + 1] = { 0 }; // 토핑 오른쪽 부터
    int left_TC = 0, right_TC = 0; // 좌우 토핑 카운터

    //오른쪽 생성
    for (int i = 0; i < topping_len; i++) {
        if (right_counter[topping[i]] == 0) {
            right_TC++;
        }
        right_counter[topping[i]]++;
    }

    //좌우 비교
    for (int i = 0; i < topping_len; i++) {
        if (left_counter[topping[i]] == 0) {
            left_TC++;
        }
        left_counter[topping[i]]++;

        right_counter[topping[i]]--;
        if (right_counter[topping[i]] == 0) {
            right_TC--;
        }

        if (left_TC == right_TC) {
            answer++;
        }
    }
    return answer;
}

int main() {
    // 토핑 구성
    int topping_1[] = {1, 2, 1, 3, 1, 4, 1, 2};
    int topping_2[] = {1, 2, 3, 1, 4};

    //구성된 토핑의 길이
    int topping_1_len = sizeof(topping_1) / sizeof(topping_1[0]);
    int topping_2_len = sizeof(topping_2) / sizeof(topping_2[0]);

    // 결과 저장
    int result_1 = solution(topping_1, topping_1_len);
    int result_2 = solution(topping_2, topping_2_len);

    //출력
    printf("%d\n", result_1);
    printf("%d\n", result_2);

}