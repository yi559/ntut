#include <stdio.h>

int main(void){
    int N,M;
    scanf("%d", &N);
    getchar();
    scanf("%d", &M);

    if (N<1 || N>2 || M<2 || M>9){
        printf("error");
        return 0;
    }

    if (N == 1){
        for (int i=0 ; i<M ; i++){
            for (int j=M-i-1 ; j>0 ; j--){
                printf("#");
            }
            printf("*");
            
            if (i>0){
                for (int j = 0; j < i; j++) {
                printf("%c", 'A' + (i - 1) % 3);
                printf("*");
            }
            }
            for (int j=M-i-1 ; j>0 ; j--){
                printf("#");
            }
            printf("\n");
        }
    }else{
        for (int i=0 ; i<M ; i++){
            for (int j=1+i ; j>0 ; j--){
                printf("%d", j);
            }
            for (int j=M-i ; j>0 ; j--){
                printf("*");
            }
            for (int j=M-i ; j>0 ; j--){
                printf("*");
            }
            for (int j=1 ; j<2+i ; j++){
                printf("%d", j);
            }
            printf("\n");
        }
    }
    return 0;
}