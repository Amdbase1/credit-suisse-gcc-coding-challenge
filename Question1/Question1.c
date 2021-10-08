#include<stdio.h>
#include <math.h>

int solution(int n)
{
    int b1 = floor((double)n/3);
    int b2 = ceil((double)n/3) ;
    if(abs(n-3*b1)>abs(n-3*b2)){
        printf("a:%d b:%d a-b:%d\n",n-2*b2,b2,n-3*b2);
        return n-b2;
    }
    printf("a:%d b:%d a-b:%d\n",n-2*b1,b1,n-3*b1);
    return n-b1;
}

/* Do not edit below code */
int main(void) {
    int n;
    scanf("%d",&n);
    int answer=solution(n);
    printf("%d",answer);
    return 0;
}