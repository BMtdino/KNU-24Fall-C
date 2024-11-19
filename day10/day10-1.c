#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Student ����ü ����
typedef struct {
    char name[50];
    int score;
} Student;

// ��� ����
typedef struct Node {
    Student student;
    struct Node* next;
} Node;

// ���ο� �л��� ��忡 �����ϴ� �Լ�
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

// �л� ������ �Է¹޾� insertStudent�� �߰���
void inputStudent(Node** head) {
    char name[50];
    int score;

    printf("�л� �̸� : ");
    scanf_s("%49s", &name, sizeof(name));  // %49s�� ���� ���� ����

    printf("%s�� ���� : ", name);
    scanf_s("%d", &score);

    // �Է� ���� ������ ����Ʈ�� �߰���
    insertStudent(head, name, score);
}

// �̸��� �������� �л��� �����ϴ� �Լ�
void deleteStudent(Node** head) {
    char name[50];
    Node* temp = *head;
    Node* prev = NULL;

    // ������ �л� �Է�
    printf("������ �л��� �̸� : ");
    scanf_s("%49s", &name, sizeof(name));

    // ����Ʈ�� ��� �ִ� ���
    if (temp == NULL) {
        printf("������ �л��� �����ϴ�.\n");
        return;
    }

    // ù ��° ��尡 ���� ����� ���
    if (strcmp(temp->student.name, name) == 0) {
        *head = temp->next;
        free(temp);
        printf("'%s' �� �����Ǿ����ϴ�.\n", name);
        return;
    }

    // ����Ʈ�� �߰� �Ǵ� ������ ��带 Ž���ϸ� ���� ��� ã��
    while (temp != NULL && strcmp(temp->student.name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    // ������ �л��� ���� ���
    if (temp == NULL) {
        printf("������ �л��� �������� �ʽ��ϴ�.\n");
        return;
    }

    // �л��� ����Ʈ���� �����ϰ� �޸� ����
    prev->next = temp->next;
    free(temp);
    printf("'%s' �� �����Ǿ����ϴ�.\n", name);
}

// ��ü �л� ������ ����ϴ� �Լ�
void PrintAllStudents(Node* head) {
    // ����Ʈ�� �ƹ��͵� ���� ���
    if (head == NULL) {
        printf("-----------------------------------\n");
        printf("�л��� �����ϴ�.\n");
        printf("-----------------------------------\n");
        return;
    }

    // ����Ʈ�� ���� �ִ� ���
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

    insertStudent(&head, "ȫ�浿", 99);
    
    while (1) {
        PrintAllStudents(head);
        printf("1. �л��� ������ �Է�\n2. �л� ���� ����\n3. ���α׷� ����\n");
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
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���.\n");
        }

    }

    return 0;
}
