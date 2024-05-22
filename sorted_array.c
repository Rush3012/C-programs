#include<stdio.h>
#include<stdbool.h>
bool issorted(int arr[], int n){
    for(int i=0;i<n;i++){
        for (int j= i+1;j<n;j++){
            if(arr[j]<arr[i]){
                return false;
            }
        }
    }
    return true;
}

int main(){
    int n;
    scanf("%d",&n);
    int arr[n];
    for (int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    bool ans=issorted(arr,n);
    if(ans){
        printf("true");
    }
    else{
        printf("false");
    }
    return 0;
}
