/*
014 直線方程式
給定平面上兩個點座標，求直線方程式 y = mx + b，
m = (y1 - y2) / (x1 - x2)
b = (x2 * y1 - x1 * y2) / (x2 - x1)
分數表示格式：分子/分母，例如7/3
※函式傳遞參數需使用指標

【輸入說明】
第一行：輸入整數N，代表其後有多少筆輸入測資
第二到N+1行：輸入平面上兩個點座標位置，依序為x1, y1, x2, y2，中間以空格隔開，座標皆以整數表示

範例輸入：
2
2 -2 7 2 (x1=-2, y1=-2, x2=7, y2=2)
3 -6 -4 8 (x1=3, y1=-6, x2=-4, y2=8)

【輸出說明】
輸出格式為y = mx + b，且m, b的值須化為最簡分數或整數
若m或b為0，則該項不輸出
※注意事項
若m 為 1時，輸出格式應為 y = x + b，而不是 y = 1x + b
若m 為 -1時，輸出格式應為 y = -x + b，而不是 y = -1x + b
若m 為 0且b > 0時，輸出格式應為 y = b
若m 為 0且b < 0時，輸出格式應為 y = -b

範例輸出：
y = 4/5x - 18/5
y = -2x

【測試資料一】
輸入：
5
2 -2 7 2
8 -2 -3 9
2 1 7 2
-2 -5 1 4
9 6 15 12

輸出：
y = 4/5x - 18/5
y = -x + 6
y = 1/5x + 3/5
y = 3x + 1
y = x - 3

【測試資料二】
輸入：
3
3 -6 -4 8
-6 6 -1 1
20 10 10 5

輸出：
y = -2x
y = -x
y = 1/2x

【測試資料三】
輸入：
3
6 -3 -3 -3
5 10 -3 10
2 8 9 8

輸出：
y = -3
y = 10
y = 8
*/

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