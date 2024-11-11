#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 100

typedef enum {
    VIP = 1,
    GOLD,
    SILVER,
    BRONZE
} Rank;

typedef struct Customer {
    int id;
    char* customerName;
    Rank rank;
    int order_amount;
    int points;
    struct Customer* prev;
    struct Customer* next;
} Customer;

Customer* head = NULL;
Customer* tail = NULL;
int customer_count = 0;

void add_customer() {
    Customer* new_customer = (Customer*)malloc(sizeof(Customer));
    if (!new_customer) {
        printf("�޸� �Ҵ� ����\n");
        return;
    }

    new_customer->id = ++customer_count;

    char name[50];
    printf("�� �̸�: ");
    scanf_s("%49s", name, (unsigned int)sizeof(name));  // unsigned int �� ��ȯ �߰�
    new_customer->customerName = _strdup(name);


    int rank;
    printf("�� ��� (1: VIP, 2: GOLD, 3: SILVER, 4: BRONZE): ");
    scanf_s("%d", &rank);
    new_customer->rank = (Rank)rank;

    printf("��ü �ֹ���: ");
    scanf_s("%d", &new_customer->order_amount);

    printf("����Ʈ: ");
    scanf_s("%d", &new_customer->points);

    new_customer->prev = NULL;
    new_customer->next = NULL;

    if (!head) {
        head = tail = new_customer;
    }
    else {
        tail->next = new_customer;
        new_customer->prev = tail;
        tail = new_customer;
    }

    printf("���� �߰��Ǿ����ϴ�.\n");
}

void delete_customer(int id) {
    Customer* current = head;

    while (current) {
        if (current->id == id) {
            if (current->prev)
                current->prev->next = current->next;
            else
                head = current->next;

            if (current->next)
                current->next->prev = current->prev;
            else
                tail = current->prev;

            free(current->customerName);
            free(current);
            printf("���� �����Ǿ����ϴ�.\n");
            return;
        }
        current = current->next;
    }
    printf("�� ID�� ã�� �� �����ϴ�.\n");
}

void update_customer(int id) {
    Customer* current = head;

    while (current) {
        if (current->id == id) {
            printf("���ο� �� �̸�: ");
            char name[50];
            scanf_s("%49s", name, (unsigned)_countof(name));
            free(current->customerName);
            current->customerName = _strdup(name);

            int rank;
            printf("���ο� �� ��� (1: VIP, 2: GOLD, 3: SILVER, 4: BRONZE): ");
            scanf_s("%d", &rank);
            current->rank = (Rank)rank;

            printf("���ο� ��ü �ֹ���: ");
            scanf_s("%d", &current->order_amount);

            printf("���ο� ����Ʈ: ");
            scanf_s("%d", &current->points);

            printf("�� ������ �����Ǿ����ϴ�.\n");
            return;
        }
        current = current->next;
    }
    printf("�� ID�� ã�� �� �����ϴ�.\n");
}

int compare_customers(const void* a, const void* b);

void print_customers() {
    Customer* sorted_customers[MAX_CUSTOMERS];
    int count = 0;
    Customer* current = head;

    while (current) {
        sorted_customers[count++] = current;
        current = current->next;
    }

    qsort(sorted_customers, count, sizeof(Customer*), compare_customers);

    printf("ID\t�̸�\t���\t�ֹ���\t����Ʈ\n");
    printf("-----------------------------------------\n");
    for (int i = 0; i < count; i++) {
        Customer* c = sorted_customers[i];
        printf("%d\t%s\t%d\t%d\t%d\n", c->id, c->customerName, c->rank, c->order_amount, c->points);
    }
}

int compare_customers(const void* a, const void* b) {
    Customer* c1 = *(Customer**)a;
    Customer* c2 = *(Customer**)b;

    if (c1->rank != c2->rank)
        return c1->rank - c2->rank;
    if (c1->order_amount != c2->order_amount)
        return c2->order_amount - c1->order_amount;
    return c2->points - c1->points;
}

void free_all_customers() {
    Customer* current = head;
    while (current) {
        Customer* next = current->next;
        free(current->customerName);
        free(current);
        current = next;
    }
}

int main() {
    int choice, id;

    while (1) {
        printf("\n--- �� ���� �ý��� ---\n");
        printf("1. �� �߰�\n");
        printf("2. �� ����\n");
        printf("3. �� ����\n");
        printf("4. ��ü ����Ʈ ���\n");
        printf("5. ����\n");
        printf("����: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            add_customer();
            break;
        case 2:
            printf("������ �� ID: ");
            scanf_s("%d", &id);
            delete_customer(id);
            break;
        case 3:
            printf("������ �� ID: ");
            scanf_s("%d", &id);
            update_customer(id);
            break;
        case 4:
            print_customers();
            break;
        case 5:
            free_all_customers();
            printf("���α׷��� �����մϴ�.\n");
            exit(0);
        default:
            printf("�ùٸ� ��ȣ�� �����ϼ���.\n");
        }
    }

    return 0;
}
