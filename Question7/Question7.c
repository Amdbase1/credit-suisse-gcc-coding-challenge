#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int key;
    struct Node *next;
}Node;
typedef struct List{
    int size;
    struct Node *head;
}List;
void insertList(List*list, int data){
    struct Node*newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->key= data;
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
}
bool checkList(List*list, int data){
    struct Node* current= list->head;
    while(current!=NULL){
        if (current->key==data){
            return true;
        }
        current=current->next;
    }
    return false;
}

int fact(int n){
    int res=1;
    for(int i=2;i<=n;i++){
        res=res*i;
    }
    return res;
}
int combination(int k, int n){
    int res = fact(n)/(fact(k)*fact(n-k));
    return res;
}
int findMax(int*arr,int n){
    int i;
    int max = arr[0];
    for (i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

int find(int x,int*arr){
    if(x!=arr[x]){
        arr[x]=find(arr[x],arr);
    }
    return arr[x];
}

void union1(int x, int y,int *arr){
    arr[find(x,arr)] = arr[find(y,arr)];
}
void countStablePartitions(int n, int values[]){
    int max =findMax(values,n);
    int i,j, parents[max+1];
    for(i=0;i<=max;i++){
        parents[i]=i;
    }
    int count1=0;
    for(i=0;i<n;i++){
        if(values[i]==1) {
            count1++;
        }
        for(j=2;j<=(int)sqrt(values[i]);j++){
            if(values[i]%j==0){
                union1(values[i],j,parents);
                union1(values[i],values[i]/j,parents);
            }
        }
    }
    if(count1>0) count1--;
    long result=0,count=0;
    struct List *list = (struct List*) malloc(sizeof(struct List));
    list->head=NULL;
    list->size=0;

    for(i=0;i<n;i++){
        j = find(parents[values[i]],parents);
        if(!checkList(list,j)){
            insertList(list,j);
        }
    }
    count = list->size+count1;
    for(i=1;i<=count/2;i++){
        //if (i==count/2) result+=2*(combination(i,count)% (int) (pow(10,9)+7));
        //else 
        result+=2*(combination(i,count)% (int) (pow(10,9)+7));
    }
    // for(i=0;i<n;i++){
    //     printf("%d ",parents[values[i]]);
    // }printf("\n");
    if(result==0){
        printf("No\n");
        printf("0");
    }
    else{
        printf("Yes\n");
        printf("%d",result) ;
    }
}
int main(){
    int n, i;
    scanf("%d", &n);
    int answer;
    int values[n];
    for (i = 0; i < n; ++i) {
        scanf("%d", &values[i]);
    }
	countStablePartitions(n, values);
    return 0;
}
