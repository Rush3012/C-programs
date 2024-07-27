#include<stdio.h>
#include<stdlib.h>

struct ele {
    int weight;
    int node;
    int parent;
};

void swap(struct ele** a, struct ele** b)
{
    struct ele* temp= *a;
    *a=*b;
    *b=temp;
}

struct disjoint_set {
    int* size;
    int* parent;
};

struct disjoint_set* create_ds(int size)
{
    struct disjoint_set* ds= (struct disjoint_set*)malloc(sizeof(struct disjoint_set));
    
    ds->size= (int*)malloc(size * sizeof(int));
    ds->parent= (int*)malloc( size * sizeof(int));
    
    for(int i=0; i<size ; i++)
        ds->size[i]=1;
    
    for(int i=0; i<size ; i++)
        ds->parent[i]=i;
    
    return ds;
}


void sort(struct ele* arr[],int* arr_ix) 
{ 
    int i, j, min_idx; 
  
    for (i = 0; i < *arr_ix-1; i++) 
    { 
        min_idx = i; 
        for (j = i+1; j < *arr_ix; j++) 
          if (arr[j]->weight < arr[min_idx]->weight) 
            min_idx = j; 
  
        if(min_idx != i) 
            swap(&arr[min_idx],&arr[i]); 
    } 
} 



void labellist_2(struct ele* arr[],int* arr_ix, char list[], int flag )
{
    
    int ix=0; // index of list
    int parent=0;
    
    while(list[ix]!='\0')
    {
        if(list[ix]==' ')
        {    ix++; continue; }
        
        int num=0;
        
        while(list[ix]>='0' && list[ix]<='9')
        {
            num= (num*10) + (list[ix]-'0');
            ix++;
        }
        
        if(flag==0)
        {
            parent=num;
            flag=1;
            continue;
        }

        
        arr[*arr_ix]->weight=num;
        (*arr_ix)++;
    }
    
}


void labellist_1(struct ele* arr[],int* arr_ix, char list[], int flag )
{
    int ix=0; 
    int parent=0;
    
    while(list[ix]!='\0')
    {
        
        if(list[ix]==' ')
        {    ix++; continue; }
        
        int num=0;
        
        while(list[ix]>='0' && list[ix]<='9')
        {
            num= (num*10) + (list[ix]-'0');
            ix++;
        }
        
        if(flag==0)
        {
            parent=num;
            flag=1;
            continue;
        }
        
        struct ele* elem= (struct ele*)malloc(sizeof(struct ele));
        elem->weight=-1;
        elem->node=num;
        elem->parent=parent;
        
        arr[*arr_ix]=elem;
        (*arr_ix)++;
    }
    
}


int findpar(struct disjoint_set* ds,int u)
{
    if(u==ds->parent[u])
        return u;
    return findpar(ds,ds->parent[u]);
}

void kruskal_ubs(struct disjoint_set* ds, struct ele* arr[])
{
    int ix=0;
    int sum=0;
    
    while(arr[ix]!=NULL)
    {
        int ulp_a=findpar(ds,arr[ix]->node);
        int ulp_b=findpar(ds,arr[ix]->parent);
        
        if(ulp_a!=ulp_b)
        {
            if(ds->size[ulp_a]>ds->size[ulp_b])
            {
                ds->parent[ulp_b]=ulp_a;
                ds->size[ulp_a]+=ds->size[ulp_b];
            }
            
            else
            {
                ds->parent[ulp_a]=ulp_b;
                ds->size[ulp_b]+=ds->size[ulp_a];
            }
            
            sum+=arr[ix]->weight;
        }
        
        ix++;
    }
    
    printf("%d\n",sum);
}


int main()
{
    int n;
    scanf("%d\n",&n);
    
    
    struct ele* arr[n*n]; //struct ele** arr = (struct ele*)malloc(n * n * sizeof(struct ele));
    
    for(int i=0; i<n*n ;i++)
       arr[i]=NULL;
    

    int arr_ix=0;
    
    for(int i=0 ; i<n ; i++)
    {
        char list[1000];
        scanf(" %[^\n]",list);
        int flag=0;
        labellist_1(arr,&arr_ix,list,flag);
    }
    arr_ix=0;
    for(int i=0 ; i<n ; i++)
    {
        
        char list[1000];
        scanf(" %[^\n]",list);
        int flag=0;
        labellist_2(arr,&arr_ix,list,flag);
    }
    sort(arr,&arr_ix);       
    struct disjoint_set* ds=create_ds(n); 
    kruskal_ubs(ds,arr);
    return 0;
}