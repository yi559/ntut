/*
004.BMI

給定身高 h (公分) 及體重 w (公斤)，計算BMI數值「四捨六入五看偶」到整數。BMI公式：
BMI = 體重(公斤) / (身高 * 身高)(公尺)
「四捨六入五看偶」到整數規則：
(1) 小數點後第一位為4，小數捨去；20.49 => 20。
(2) 小數點後第一位為6，整數加1，小數捨去；20.60 => 21。
(3) 小數點後第一位為5，整數是奇數，小數捨去；21.55 => 21。
(4) 小數點後第一位為5，整數非奇數，整數加1，小數捨去；20.55 => 21。

【輸入說明】
第一行輸入一個整數 w (20 <= w <= 100)，代表體重的公斤。
第二行輸入一個整數 h (100 <= h <= 200)，代表身高的公分。
當BMI大於等於18且小於等於24時，顯示BMI數值
當BMI小於18時，顯示「too low」
當BMI大於24時，顯示「too high」
如果輸入的整數不符合指定範圍則輸出ERROR。

範例輸入：
85
177

【輸出說明】
輸出BMI數值，結果「四捨六入五看偶」到整數。

範例輸出：
27 (BMI=85/(1.77 * 1.77)，BMI為27.1314，且「四捨六入五看偶」到整數)
too high

【測試資料一】
輸入：
18
114

輸出：
ERROR

【測試資料二】
輸入：
20
201

輸出：
ERROR

【測試資料三】
輸入：
65
173

輸出：
22

【測試資料四】
輸入：
99
149

輸出：
45
too high

【測試資料五】
輸入：
20
163

輸出：
7
too low
*/

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