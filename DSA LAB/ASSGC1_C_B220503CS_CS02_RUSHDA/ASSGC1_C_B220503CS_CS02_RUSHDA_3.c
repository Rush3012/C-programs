#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct StudentRecord{
    char name[100];
    char rollNumber[10];
    int age;
    char branch[3];
    struct StudentRecord* next;
} StudentRecord;

StudentRecord* createNode(char *name, char *rollno, int age){
    StudentRecord* newNode = malloc(sizeof(struct StudentRecord));
    strcpy(newNode -> name, name);
    strcpy(newNode -> rollNumber, rollno);
    strncpy(newNode -> branch, &rollno[7], 2);
    newNode -> branch[2] = '\0';
    newNode -> age = age;
    newNode -> next = NULL;
    return newNode;
}

void insertRecord(StudentRecord* hash[], char name[], char rollno[], int age){
    int idx = age, len = strlen(name);
    for (int i = 0; i < len; i++){
        idx = idx + name[i];
    }
    idx = idx % 4;
    StudentRecord* newNode = createNode(name, rollno, age);
    if (hash[idx] == NULL){
        hash[idx] = newNode;
        return;
    }
    StudentRecord* current = hash[idx];
    while (current -> next != NULL){
        current = current -> next;
    }
    current -> next = newNode;
}

void printGroup(StudentRecord* hash[], int k){
    int i = 0;
    StudentRecord* current = hash[k];
    while (current != NULL){
        i++;
        current = current -> next;
    }
    printf("%d ",i);
    current = hash[k];
    while (current != NULL){
        printf("%s ", current -> name);
        current = current -> next;
    }
    printf("\n");
}

void printBranchList(StudentRecord* hash[], int m, char b[]){
    StudentRecord* current = hash[m];
    int found = 0;
    while (current != NULL){
        if (strcasecmp(current -> branch, b) == 0){
            printf("%s ", current -> name);
            found = 1;
        }
        current = current -> next;
    }
    if (!found) {
        printf("-1\n"); 
    } else {
        printf("\n"); 
    }
}

void freeRecords(StudentRecord* hash[]){
    for (int i = 0; i < 4; i++){
        StudentRecord* current = hash[i];
        while (current != NULL){
            StudentRecord* temp = current;
            current = current -> next;
            free(temp);
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    char name[100], rollno[10], ch;
    int age, k;
    StudentRecord* hashTable[n];
    for(int i = 0; i < 4; i++){
        hashTable[i] = NULL;
    }
    for (int i = 0; i < n; i++){
        scanf("%s %s %d", name, rollno, &age);
        insertRecord(hashTable, name, rollno, age);
    }
    while(1){
        scanf(" %c", &ch);
        if (ch == 'c'){
            scanf("%d", &k);
            printGroup(hashTable, k); 
        }
        else if (ch == 'e'){
            freeRecords(hashTable);
            return 0;
        }
        else {
            k = ch - '0';
            char b[3];
            scanf("%s",b);
            printBranchList(hashTable, k, b);
        }
    }
}

