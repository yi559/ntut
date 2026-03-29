/*
010 電路

模擬一個數位IC，內有回饋電路與紀錄器電路
輸入M 是二進位 8 位元，輸出是二進位 4 位元
輸入範圍從 00000000 到 11111111 (十進位 0~255)

數位IC內有一個回饋電路，回饋方式:
C(M) = M , if M = 0 or M = 1
C(M) = C(M/2) , if M is even
C(M) = C((M+1)/2) , if M is odd
數位IC內有一個紀錄器R，會記錄回饋電路的回饋次數

請以二進位輸出數位IC內紀錄器所記錄之回饋電路的回饋次數

例如：
M=00001010 (十進位 10),則電路回饋依序為十進位 5, 3, 2, 1
C(10) = C(5) = C(3) = C(2) = C(1) = 1，共回饋 4 次，R(10) = 4
則此數位IC以二進位輸出回饋次數為 0100(十進位 4)


【輸入說明】
第一行：輸入第一個測試案例資料 (二進位8位元)
第二行：輸入第二個測試案例資料 (二進位8位元)
....
第N行：-1 (結束)

範例輸入：
00001010
-1

【輸出說明】
每一行輸出一個測試案例資料的結果 (二進位4位元)

範例輸出：
0100

【測試資料一】
輸入：
00000000
11111111
00000001
10000000
-1

輸出：
0000
1000
0000
0111
【測試資料二】
輸入：
01111110
00001000
00111100
00011000
11000011
-1

輸出：
0111
0011
0110
0101
1000

【測試資料三】
輸入：
11000111
01110111
11110001
00001010
01010000
00000111
-1

輸出：
1000
0111
1000
0100
0111
0011
*/

#include <stdio.h>
#include <math.h>

int trans10(int data){
    int num = 0,rem;
    int weight = 1;

    while (data > 0) {
        rem = data % 10;
        num += rem * weight;
        data /= 10;
        weight *= 2;
    }
    return num;
}

int c(int times,int m){
    if (m == 0 || m == 1) return times;
    
    times += 1;
    if (m % 2 == 0){
        return c(times, m / 2);
    }else{ 
        return c(times, (m + 1) / 2);
    }
}

int trans2(int data){
    int num = 0;
    int weight = 1;
    while (data > 0) {
        num += (data % 2) * weight;
        data /= 2;
        weight *= 10;
    }
    return num;
}

int main(void){
    while(1){
        int data = 0;
        scanf("%d", &data);
        if (data == -1) break;

        data = trans10(data);
        printf("%04d\n", trans2(c(0,data)));
    }
    return 0;
}