#include <stdio.h>

int main(void){
    int S0,S1,S2;
    char e1,e2;

    scanf("%d", &S0);
    scanf(" %d", &S1);
    scanf(" %c", &e1);
    scanf(" %c", &e2);
    
    S2 = S1 | (1<<e1);
    printf("%d", S1);
    printf("\n%d", S2);
    return 0;
}