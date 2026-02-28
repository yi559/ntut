#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void){
    int a,b,c;
    double x1,x2;
    int d;
    double A,B;
    scanf("%d",&a);
    scanf(" %d",&b);
    scanf(" %d",&c);

    d = (b*b)-4*a*c;

    if (d >= 0){
        x1 = ((-b)+sqrt(d))/(2*a);
        x2 = ((-b)-sqrt(d))/(2*a);
        printf("%.1f", x1);
        if (x1 != x2){
            printf("\n%.1f", x2);
        }
    }else{
        A = (-b)/(2*a);
        B = fabs(sqrt(abs(d))/(2*a));
        printf("%.1f+%.1fi", A,B);
        printf("\n%.1f-%.1fi", A,B);
    }
    return 0;
}