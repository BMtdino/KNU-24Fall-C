#include <stdio.h>
#include <string.h> 

void filter_string(char* str) {
    int i = 0, j = 0;
    while (str[i]) {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';  
}

void reverse_string(char* str) {
    int length = strlen(str);  
    char* left = str;
    char* right = str + length - 1;

    while (left < right) {
        char temp = *left;
        *left = *right;
        *right = temp;

        left++;
        right--;
    }
}

int main() {
    char str[100];

    printf("문자열을 입력하세요: ");
    fgets(str, sizeof(str), stdin);

    filter_string(str);
    reverse_string(str);
    printf("뒤집어진 문자열: %s\n", str);

    return 0;
}
