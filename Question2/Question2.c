#include <stdio.h>
void insertionSort(int arr[], int n,int arr2[])
{
    int i, key, j,key2;
    for (i = 1; i < n; i++) {
        key = arr[i];
        key2 = arr2[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            arr2[j+1]=arr2[j];
            j = j - 1;
        }
        arr[j + 1] = key;
        arr2[j+1]=key2;
    }
}
int securitiesBuying(int z,int security_value[],int size)
{
    int no_of_stocks=0;
   // participants code here
    int sum = 0,smallest,i,arr[size],j,check;
    for(i=0;i<size;i++){
        arr[i]=i+1;
    }
    insertionSort(security_value,size,arr);
    

    for(i=0;i<size;i++){
        check=0;
        for(j=0;j<arr[i];j++){
            if (sum+security_value[i]<=z){
                sum+=security_value[i];
                no_of_stocks++;
            }
            else {
                check=1;
                break;
            }
        }
        if(check==1) break;
    }

    return no_of_stocks;
}

int main(void) {
    int z;
    scanf("%d",&z);
    int input,security_value[50],size=0;
    while(scanf("%d",&input)==1)
    {
    	security_value[size++]=input;
    }
    
    int no_of_stocks_purchased = securitiesBuying(z,security_value,size);
    printf("%d",no_of_stocks_purchased);
    return 0;
}
