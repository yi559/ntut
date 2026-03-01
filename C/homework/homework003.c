#include <stdio.h>

int main(void){
    int S0,S1,S2;
    char e1,e2;
    int tag = 0;

    scanf("%d", &S0);
    scanf(" %d", &S1);
    scanf(" %c", &e1);
    scanf(" %c", &e2);
    
    if (S0 <0 || S0 >63){
        printf("S0 ERROR\n");
        tag = 1;
    }
    if (S1 <0 || S1 >63){
        printf("S1 ERROR\n");
        tag = 1;
    }
    if (e1 < 'a' || e1 > 'f') {
    printf("e1 ERROR\n");
    tag = 1;
    }
    if (e2 < 'a' || e2 > 'f') {
    printf("e2 ERROR\n");
    tag = 1;
    }
    int shift1 = e1 - 'a';
    int shift2 = e2 - 'a';

    if (!tag){
        S2 = S1 | (1 << shift1);
        if (S2 & (1 << shift2)){
            printf("Y\n");
        }else{
            printf("N\n");
        }

        if ((S2 & S0) == S2) {
            printf("Y\n");
        } else {
            printf("N\n");
        }

        printf("%d\n", S0 & S2);

        printf("%d\n", S0 | S2);

        printf("%d\n", S0 & (~S2));
    }

    return 0;
}