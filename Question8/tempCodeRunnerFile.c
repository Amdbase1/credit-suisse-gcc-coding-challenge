#include <stdio.h>

int calculateMaximizedReturns(int, int, int, int, int[]);
void calculate(int n, int k, int d, int m, int returns[],int *tempReturn);
void combination(int returns[], int data[], int start, int end, int index, int k, int*tempReturn,int d,int m);

int main()
{
    int n, k, d, m;
    int returns[5000];
    // int sum=0;
    scanf("%d %d %d %d", &n, &k, &d, &m);
    for(int i=0; i<n; i++)
        scanf("%d", &returns[i]);
    int maximizedReturns = calculateMaximizedReturns(n, k, d, m, returns);
    //do not remove the following line
    printf("%lld", maximizedReturns);
    return 0;
}
void combination(int returns[], int data[], int start, int end, int index, int k,int *tempReturn,int d,int m){
    //if data have enough k values
    if (index==k){
        int temp = 0,i,j;
        //initilize multiplier for return in each day
        int multiplier[end+1];
        for(i=0;i<=end;i++){
            multiplier[i]=1;
        }
        for(i=0;i<k;i++){
            multiplier[data[i]]=0;
            for(j=1;j<=d && j<=end-data[i];j++){
                multiplier[data[i]+j]=m;
            }
        }
        //find temp total return
        for(i=0;i<=end;i++){
            temp+=returns[i]*multiplier[i];
        }
        if(temp>*tempReturn) *tempReturn=temp;
        return;
    }

    //recursive to find combination
    for(int i = start; i<=end && end-i+1>=k-index;i++){
        //restore index of each element of a combination  in the data array. 
        data[index]=i;
        combination(returns,data,i+1,end,index+1,k,tempReturn,d,m);
    }
}
void calculate(int n, int k, int d, int m, int returns[],int *tempReturn){
    int data[k];
    //recursive to find combination k out of n, for each combination, save max temp return to tempReturn 
    //https://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/
    combination(returns, data, 0, n-1, 0, k,tempReturn,d,m);
}
int  calculateMaximizedReturns(int n, int k, int d, int m, int returns[])
{
    // Complete the calculateMaximizedReturns function.
    int i, max =0, tempReturn=0;
    //try with different times of investments: 0 time, 1 time, ... k times
    calculate(n,0,d,m,returns,&max);
    for (i=1;i<=k;i++){
        calculate(n,i,d,m,returns,&tempReturn);
        max = tempReturn>max ? tempReturn : max ;
    }
    return max;
}