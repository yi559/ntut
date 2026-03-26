#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b) {
        a %= b;
        int temp = a;
        a = b;
        b = temp;
    }
    return a;
}

void slope(const int *x1, const int *y1, const int *x2, const int *y2, char *m){
    int num = *y2 - *y1;
    int den = *x2 - *x1;
    
    if (den < 0) {
        num = -num;
        den = -den;
    }

    int common = gcd(num, den);
    num /= common;
    den /= common;

    if (den == 1) {
        sprintf(m, "%d", num);
    } else {
        sprintf(m, "%d/%d", num, den);
    }
}

void discriminant(const int *x1, const int *y1, const int *x2, const int *y2, char *b){
    int num = *x2 * *y1 - *x1 * *y2;
    int den = *x2 - *x1;

    if (den < 0) {
        num = -num;
        den = -den;
    }

    int common = gcd(num, den);
    num /= common;
    den /= common;

    if (den == 1) {
        sprintf(b, "%d", num);
    } else {
        sprintf(b, "%d/%d", num, den);
    }
}

int main(void){
    int t = 0;
    int x1,y1,x2,y2;
    char m[10],b[10];
    scanf("%d", &t);
    for (int i=0 ; i<t ;i++){
        scanf("%d %d %d %d", &x1,&y1,&x2,&y2);
        slope(&x1,&y1,&x2,&y2,m);
        discriminant(&x1,&y1,&x2,&y2,b);
        
        printf("y = ");
        
        int m_is_zero = (strcmp(m, "0") == 0);
        if (strcmp(m, "1") == 0) printf("x");
        else if (strcmp(m, "-1") == 0) printf("-x");
        else if (!m_is_zero) printf("%sx", m);
        else if (m_is_zero && strcmp(b, "0") == 0){
            printf("0\n");
            continue;
        }

        if (strcmp(b, "0") != 0){
            if (b[0] == '-'){
                if (!m_is_zero) printf(" - %s", b + 1);
                else printf("%s", b);
            }else{
                if (!m_is_zero) printf(" + %s", b);
                else printf("%s", b);
            }
        }

        printf("\n");
    }
    return 0;
}