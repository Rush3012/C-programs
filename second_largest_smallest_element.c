#include <stdio.h>
#include<limits.h>

int max_element(int arr[], int n) {
    if (n == 0 || n == 1) {
        printf("-1 -1\n");  // edge case when only one element is present in array
        return 0;
    }
    int min = INT_MAX;int max=INT_MIN;int second_small=INT_MAX;
    int second_large=INT_MIN;
    for (int j = 0; j < n; j++) {
        if (arr[j] > max) {
            max = arr[j];
        }
        if(arr[j]<min){
            min=arr[j];
        }
    }
    for (int i = 0; i < n; i++) {
        if (arr[i] < second_small && arr[i] != min) {
            second_small = arr[i];
        }
        if (arr[i] > second_large && arr[i] != max) {
            second_large = arr[i];
        }
    }

    printf("The second largest element in the array is: %d\n", second_large);
    printf("The second smallest element in the array is: %d\n",second_small);
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int element = max_element(arr, n);
   
    return 0;
}
