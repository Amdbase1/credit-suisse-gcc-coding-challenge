#include <stdio.h>
//98/100 
int totalPairs(int n, int values[]){
    // Complete the total Pairs function
    int i,j,k,count=0,largest;
    for(i=0;i<n-1;i++){
        for(j=i+1;j<n;j++){
            if(j==i+1){
                count++;
                largest=0;
            }
            else{
                largest= largest<values[j-1] ? values[j-1] : largest;
                if(largest>=values[i]){
                    break;
                }
                if(largest>=values[j]){
                    continue;
                }
                count++;
            }
        }
    }
    return count;
}
int main(){
    int n, i;
    scanf("%d", &n);
    int answer;
    int values[n];
    for (i = 0; i < n; ++i) {
        scanf("%d", &values[i]);
    }
	answer = totalPairs(n, values);
    // Do not remove below line
    printf("%d",answer);
    // Do not print anything after this line
    return 0;
}
