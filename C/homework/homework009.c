#include <stdio.h>
#include <math.h>

void G(int n, int k){
    if (n == 1) printf("%d", k);
    else if (k < pow(2,n-1)){
        printf("0");
        G(n-1,k);
    }else if (k >= pow(2,n-1)){
        printf("1");
        G(n-1, pow(2,n)-1-k);
    }
}

int main(void){
    int n=0,k=0;
    
    while(1){
        scanf("%d", &n);
        if (n == -1) break;
        scanf("%d", &k);
        G(n,k);
        printf("\n");        
    }

    return 0;
}