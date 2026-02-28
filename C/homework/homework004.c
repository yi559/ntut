#include <stdio.h>

int main(void) {
    int h,w,tem,bmi;
    double BMI,H;

    scanf("%d", &w);
    scanf(" %d", &h);

    if (w < 20 || w > 100 || h < 100 || h > 200) {
        printf("ERROR");
    } else {
        H = (double)h / 100.0;
        BMI = w / (H * H);

        int integer_part = (int)BMI;
        tem = (int)((BMI - integer_part) * 10);

        if (tem <= 4) {
            bmi = integer_part;
        } else if (tem >= 6) {
            bmi = integer_part + 1;
        } else {
            if (integer_part % 2 != 0) {
                bmi = integer_part;
            } else {
                bmi = integer_part + 1;
            }
        }

        if (BMI < 18) {
            printf("%d", bmi);
            printf("\ntoo low");
        } else if (BMI > 24) {
            printf("%d", bmi);
            printf("\ntoo high");
        } else {
            printf("%d", bmi);
        }
    }
    return 0;
}