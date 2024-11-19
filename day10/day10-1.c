#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Student 구조체 정의
typedef struct {
    char name[50];
    int score;
} Student;

// 노드 정의
typedef struct Node {
    Student student;
    struct Node* next;
} Node;

// 새로운 학생을 노드에 삽입하는 함수
void insertStudent(Node** head, const char* name, int score) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    strcpy_s(new_node->student.name, sizeof(new_node->student.name), name);
    new_node->student.score = score;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

// 학생 정보를 입력받아 insertStudent에 추가함
void inputStudent(Node** head) {
    char name[50];
    int score;

    printf("학생 이름 : ");
    scanf_s("%49s", &name, sizeof(name));  // %49s로 길이 제한 설정

    printf("%s의 성적 : ", name);
    scanf_s("%d", &score);

    // 입력 받은 정보를 리스트에 추가함
    insertStudent(head, name, score);
}

// 이름을 기준으로 학생을 제거하는 함수
void deleteStudent(Node** head) {
    char name[50];
    Node* temp = *head;
    Node* prev = NULL;

    // 제거할 학생 입력
    printf("제거할 학생의 이름 : ");
    scanf_s("%49s", &name, sizeof(name));

    // 리스트가 비어 있는 경우
    if (temp == NULL) {
        printf("삭제할 학생이 없습니다.\n");
        return;
    }

    // 첫 번째 노드가 삭제 대상일 경우
    if (strcmp(temp->student.name, name) == 0) {
        *head = temp->next;
        free(temp);
        printf("'%s' 가 삭제되었습니다.\n", name);
        return;
    }

    // 리스트의 중간 또는 마지막 노드를 탐색하며 삭제 대상 찾기
    while (temp != NULL && strcmp(temp->student.name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // 삭제할 학생이 없는 경우
    if (temp == NULL) {
        printf("삭제할 학생이 존재하지 않습니다.\n");
        return;
    }

    // 학생을 리스트에서 제거하고 메모리 해제
    prev->next = temp->next;
    free(temp);
    printf("'%s' 가 삭제되었습니다.\n", name);
}

// 전체 학생 정보를 출력하는 함수
void PrintAllStudents(Node* head) {
    // 리스트에 아무것도 없는 경우
    if (head == NULL) {
        printf("-----------------------------------\n");
        printf("학생이 없습니다.\n");
        printf("-----------------------------------\n");
        return;
    }

    // 리스트에 값이 있는 경우
    Node* temp = head;
    printf("-----------------------------------\n");
    while (temp != NULL) {
        printf("%s : %d\n", temp->student.name, temp->student.score);
        temp = temp->next;
    }
    printf("-----------------------------------\n");
}

int main() {
    Node* head = NULL;
    int input;

    insertStudent(&head, "홍길동", 99);
    
    while (1) {
        PrintAllStudents(head);
        printf("1. 학생의 성적을 입력\n2. 학생 정보 제거\n3. 프로그램 종료\n");
        printf("input: ");
        scanf_s("%d", &input);

        switch (input) {
        case 1:
            inputStudent(&head);
            break;
        case 2:
            deleteStudent(&head);
            break;
        case 3:
            exit(0);
        default:
            printf("잘못된 입력입니다. 다시 입력하세요.\n");
        }

    }

    return 0;
}
