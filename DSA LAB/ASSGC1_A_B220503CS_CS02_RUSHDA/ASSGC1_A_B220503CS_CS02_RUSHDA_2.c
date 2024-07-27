#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node* next;
};

struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

void listInsert(struct Node** head, int key) {
    struct Node* newNode = createNode(key);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
}

void listDelete(struct Node** head, int index) {
    if (*head == NULL) {
        printf("-1\n");
        return;
    }

    if (index == 1) {
        struct Node* temp = *head;
        *head = (*head)->next;
        printf("%d\n", temp->key);
        free(temp);
        return;
    }

    struct Node* current = *head;
    int count = 1;

    while (count < index - 1 && current->next != NULL) {
        current = current->next;
        count++;
    }

    if (count < index - 1 || current->next == NULL) {
        printf("-1\n");
        return;
    }

    struct Node* temp = current->next;
    current->next = temp->next;
    printf("%d\n", temp->key);
    free(temp);
}
void listRemoveDuplicates(struct Node** head) {
    if (*head == NULL) {
        return;
    }

    struct Node* current = *head;

    while (current != NULL) {
        struct Node* runner = current;

        while (runner->next != NULL) {
            if (current->key == runner->next->key) {
                struct Node* temp = runner->next;
                runner->next = runner->next->next;
                free(temp);
            } else {
                runner = runner->next;
            }
        }

        current = current->next;
    }
    listDisplay(*head);
}
struct Node* duplicateList(struct Node* head) {
    struct Node* duplicateHead = NULL;
    struct Node* current = head;

    while (current != NULL) {
        listInsert(&duplicateHead, current->key);
        current = current->next;
    }

    return duplicateHead;
}

struct Node* reverseList(struct Node* head) {
    struct Node* prev = NULL;
    struct Node* current = head;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

char listIsPalindrome(struct Node* head) {
    if (head == NULL) {
        return 'N';
    }
    struct Node* duplicateHead = duplicateList(head);

    struct Node* reversedDuplicate = reverseList(duplicateHead);

    while (head != NULL && reversedDuplicate != NULL) {
        if (head->key != reversedDuplicate->key) {
            freeList(duplicateHead);  
            return 'N';
        }

        head = head->next;
        reversedDuplicate = reversedDuplicate->next;
    }

    freeList(duplicateHead);  
    return 'Y';
}

void freeList(struct Node* head) {
    struct Node* current = head;
    struct Node* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
void listDisplay(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->key);
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    char choice;
    int key, index;

    do {
        scanf(" %c", &choice);

        switch (choice) {
            case 'a':
                scanf("%d", &key);
                listInsert(&head, key);
                break;
            case 'r':
                scanf("%d", &index);
                listDelete(&head, index);
                break;
            case 'd':
                listRemoveDuplicates(&head);
                break;
            case 'p':
                printf("%c\n", listIsPalindrome(head));
                break;
            case 's':
                listDisplay(head);
                break;
        }
    } while (choice != 'e');

    freeList(head);

    return 0;
}
