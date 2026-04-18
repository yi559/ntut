/*給定平面上兩個點座標，求直線方程式 y = mx + b，
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

int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void calculateEquation(int x1, int y1, int x2, int y2, int *m_num, int *m_den, int *b_num, int *b_den) {
    *m_num = y1 - y2;
    *m_den = x1 - x2;
    
    *b_num = x2 * y1 - x1 * y2;
    *b_den = x2 - x1;

    if (*m_den != 0) {
        int g = gcd(*m_num, *m_den);
        *m_num /= g;
        *m_den /= g;
        if (*m_den < 0) {
            *m_num = -(*m_num);
            *m_den = -(*m_den);
        }
    }

    if (*b_den != 0) {
        int g = gcd(*b_num, *b_den);
        *b_num /= g;
        *b_den /= g;
        if (*b_den < 0) {
            *b_num = -(*b_num);
            *b_den = -(*b_den);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    while (n--) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

        int m_num, m_den, b_num, b_den;
        
        calculateEquation(x1, y1, x2, y2, &m_num, &m_den, &b_num, &b_den);

        printf("y = ");

        if (m_num == 0) {
            if (b_num == 0) {
                printf("0\n");
            } else {
                if (b_den == 1) printf("%d\n", b_num);
                else printf("%d/%d\n", b_num, b_den);
            }
        } else {
            if (m_num == 1 && m_den == 1) {
                printf("x");
            } else if (m_num == -1 && m_den == 1) {
                printf("-x");
            } else {
                if (m_den == 1) printf("%dx", m_num);
                else printf("%d/%dx", m_num, m_den);
            }
            
            if (b_num != 0) {
                if (b_num > 0) {
                    printf(" + ");
                    if (b_den == 1) printf("%d\n", b_num);
                    else printf("%d/%d\n", b_num, b_den);
                } else {
                    printf(" - ");
                    if (b_den == 1) printf("%d\n", -b_num);
                    else printf("%d/%d\n", -b_num, b_den);
                }
            } else {
                printf("\n");
            }
        }
    }

    return 0;
}