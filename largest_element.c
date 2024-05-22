#include <stdio.h>

int max_element(int arr[], int n) {
    int max = arr[0];
    for (int j = 1; j < n; j++) {
        if (arr[j] > max) {
            max = arr[j];
        }
    }
    return max;
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int element = max_element(arr, n);
    printf("The largest element in the array is: %d\n", element);

    return 0;
}
