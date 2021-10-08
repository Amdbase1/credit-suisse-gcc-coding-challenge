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

int profit_maxi(int maxSum, int* a, int* b,int a_count, int b_count) {
    int i,aindex=0,bindex=0,sum=0,max=0,items=0;
    for(i=0;i<a_count;i++){
        if( sum+a[i]>maxSum) break;
        sum+=a[i];
        aindex++;
        items++;
    }
    for (i=0;i<b_count;i++){
        if( sum+b[i]>maxSum) break;
        sum+=b[i];
        bindex++;
        items++;
    }
    max=items;
    while(bindex<b_count && aindex>0){
        items--;
        aindex--;
        sum-=a[aindex];
        
        while (bindex<b_count){
            if (sum+b[bindex]>maxSum){
                break;
            }
            items++;
            sum=sum+b[bindex];
            bindex++;
        }
        if (items>max) max=items;
    }
    return max;
}

int main()
{
    int n, m, x, i, result;
    scanf("%d %d %d", &n, &m, &x);

    int a[n], b[m];
    for (i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }

    for (i = 0; i < m; ++i) {
        scanf("%d", &b[i]);
    }

    result = profit_maxi(x, a, b,n,m);

    printf("%d", result);
    return 0;
}