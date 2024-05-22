int remove_duplicates(int arr[], int n) {
    if (n == 0) return 0;

    int i = 0;
    for (int j = 1; j < n; j++) {
        if (arr[i] != arr[j]) {
            i++;
            arr[i] = arr[j];
        }
    }
    return i + 1;
}
int main(){
    int n;
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    int k=remove_duplicates(arr,n);
    for (int j = 0; j < k; j++) {
        printf("%d ", arr[j]);
    }
   printf("\n");
    return 0;
}
