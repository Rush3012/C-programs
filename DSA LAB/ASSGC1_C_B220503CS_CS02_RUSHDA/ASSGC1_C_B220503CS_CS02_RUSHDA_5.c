#include <stdio.h>

#define MAX_SIZE 1000000

void countDistinct(int arr[], int n, int k) {
    int distinctCount[MAX_SIZE] = {0};
    int distinct = 0;

    for (int i = 0; i < k; i++) {
        if (distinctCount[arr[i]] == 0)
            distinct++;
        distinctCount[arr[i]]++;
    }

    printf("%d ", distinct);

    for (int i = k; i < n; i++) {
        if (distinctCount[arr[i - k]] == 1)
            distinct--;
        distinctCount[arr[i - k]]--;

        if (distinctCount[arr[i]] == 0)
            distinct++;
        distinctCount[arr[i]]++;

        printf("%d ", distinct);
    }
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    int A[MAX_SIZE];
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }

    countDistinct(A, N, K);
    return 0;
}
