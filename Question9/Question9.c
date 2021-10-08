#include <stdio.h>
#include <stdlib.h>
int INFINITY = 20000;

void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
void permutationBanker(int**time,int data2[],int data[],int c,int *temp2,int left,int right){
    int i;
    if(left==right){
        int temp3=0,i,j,indexdata=0,indexdata2=0;
        for(i=0;i<c;i++){
            if(i==data[indexdata]){
                indexdata++;
                indexdata2++;
            }
            temp3+=time[data2[indexdata2]][i];
        }
        *temp2 = *temp2>temp3 ? temp3 : *temp2;
    }
    else{
        for (i = left; i <= right; i++)
        {
            swap((data2+left), (data2+i));
            permutationBanker(time, data2, data, c, temp2, left+1, right);
            swap((data2+left), (data2+i)); //backtrack
        }
    }
}
void combinationBanker(int**time,int data2[],int data[],int start,int end,int index,int c, int k,int*temp){
    //donot pass b and r cuz b=end+1 and r=k-1, data2 has k elements, data has k-1 elements
    if(index==k){
        //Now have data[k-1] contains position of partitioner client groups
        //data={1,3} means client'index groups: 0, [1,2], 3
        //data2[k] contains banker'index combination
        int temp2=INFINITY;
        permutationBanker(time,data2,data,c,&temp2,0,k-1);
        *temp = *temp>temp2 ? temp2 : *temp;
        return;
    }
    
    for(int i =start;i<=end&&end-i+1>=k-index;i++){
        data2[index]=i;
        combinationBanker(time,data2,data,i+1,end,index+1,c,k,temp);
    }
}
void calculateBankerGroup(int ** time, int data[], int*temp,int c,int b,int r){
    //data2 has r+1 elements, data has r elements
    int data2[r+1];
    
    combinationBanker(time,data2,data,0,b-1,0,c,r+1,temp);
}

void combinationClient(int ** time, int data[], int start, int end,int index, int r,int b,int* tempTotal){
    if(index==r){
        int temp=INFINITY;
        calculateBankerGroup(time,data,&temp,end+1,b,r);
        *tempTotal= *tempTotal>temp ? temp : *tempTotal;

        return;
    }
    for(int i =start; i<=end && end-i+1>=r-index;i++){
        data[index]=i;
        combinationClient(time,data,i+1,end,index+1,r,b,tempTotal);
    }
}
void calculateClientGroup(int c,int i ,int b, int ** time,int* tempTotal){
    int data[i-1];
    combinationClient(time, data, 1, c-1, 0, i-1,b,tempTotal);
}
int bankersAndClients(int c,int b,int** time){
	// Complete the bankersAndClients function .
    int i,min=INFINITY;
    for(i=1;i<=b;i++){
        int tempTotal=INFINITY;
        calculateClientGroup(c,i,b,time,&tempTotal);
        min = tempTotal<min ? tempTotal : min ;
    }
    return min;
}


int main(){
    int b,c;
    scanf("%d %d", &c, &b);
    int answer;
    int** time;
    time = malloc(b * sizeof *time);
    for (int i=0; i<b; i++)
	 {
		time[i] = malloc(c * sizeof *time[i]);
	 }
    for(int i = 0; i < b; i++){
        
        for(int j = 0;j < c;j++){
          scanf("%d",&time[i][j]);
        }
    }
	answer = bankersAndClients(c,b,time);
    // Do not remove below line
    printf("%d",answer);
    // Do not print anything after this line
        
    return 0;
}
