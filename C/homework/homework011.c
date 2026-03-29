/*
011. 分數運算

給定兩個分數和一個運算符號，請依據題目給定的分數與運算符號進行分數運算
請輸出計算後的結果，需化為最簡分數，且分子不可大於分母，需化為帶分數
最簡分數定義: 分子和分母互質

分數表示格式:
真分數或假分數: 分子/分母
帶分數: 整數(分子/分母)

【輸入說明】
輸入說明:
第一行輸入第一個分數
第二行輸入所做運算，加減乘除分別為+ 、 - 、 * 、 /
第三行輸入第二個分數
第四行輸入是否繼續運算: y代表繼續 n代表結束
當繼續運算時，重複第一到第四行輸入

範例輸入說明:
1(3/4) (第一個分數的整數為1、分子為3、分母為4)
+ (運算為加)
1/2 (第二個分數的整數為0、分子為1、分母為2)
n (結束)

【輸出說明】
輸出計算結果，結果分數須化為最簡分數
若輸入分數的分母為0，或是運算結果分數的分母為0，輸出 error
若計算結果為假分數, 需轉化為帶分數格式輸出
帶分數格式: 整數(分子/分母)
若計算結果為整數，則只需輸出整數
若計算結果為負真分數，需在分子前面輸出負號
若計算結果為負帶分數為，在整數前面輸出負號
若計算結果為 0, 輸出 0

範例輸出說明
2(1/4) (兩個分數相加的結果化成帶分數，整數為2、分子為1、分母為4)

【測試資料一】
輸入：
1/2
-
1/2
y
9/2
*
15/3
y
5/0
/
3/2
n

輸出：
0
22(1/2)
error

【測試資料二】
輸入：
6(5/17)
*
2(13/5)
y
-1(7/13)
+
1(5/3)
y
-1(13/3)
*
15/13
n

輸出：
28(81/85)
1(5/39)
-6(2/13)

【測試資料三】
輸入：
6(7/8)
/
0/8
y
3(3/11)
-
-2(5/22)
y
1/3
-
1/2
y
1/2
+
1/3
n

輸出：
error
5(1/2)
-1/6
5/6
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

long long abs_val(long long x) {
    return x < 0 ? -x : x;
}

long long gcd(long long a, long long b) {
    a = abs_val(a);
    b = abs_val(b);
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

void improper_fraction(char *improper){
    long long i = 0, n = 0, d = 1;
    
    if (strchr(improper, '(')) {
        sscanf(improper, "%lld(%lld/%lld)", &i, &n, &d);
        if (i < 0) {
            n = i * d - n;
        } else {
            n = i * d + n;
        }
        sprintf(improper, "%lld/%lld", n, d);
    }
}

void operation(char *one, char *two, char op, char *ans){
    long long n1, d1, n2, d2;
    
    sscanf(one, "%lld/%lld", &n1, &d1);
    sscanf(two, "%lld/%lld", &n2, &d2);

    if (d1 == 0 || d2 == 0) {
        sprintf(ans, "error");
        return;
    }

    long long nr = 0, dr = 1;
    
    if (op == '+') {
        nr = n1 * d2 + n2 * d1;
        dr = d1 * d2;
    } else if (op == '-') {
        nr = n1 * d2 - n2 * d1;
        dr = d1 * d2;
    } else if (op == '*') {
        nr = n1 * n2;
        dr = d1 * d2;
    } else if (op == '/') {
        nr = n1 * d2;
        dr = d1 * n2;
    }

    if (dr == 0) {
        sprintf(ans, "error");
        return;
    }
    
    if (nr == 0) {
        sprintf(ans, "0");
        return;
    }

    long long g = gcd(nr, dr);
    nr /= g;
    dr /= g;

    if (dr < 0) {
        nr = -nr;
        dr = -dr;
    }

    if (dr == 1) {
        sprintf(ans, "%lld", nr); 
    } else if (abs_val(nr) > dr) {
        long long i = nr / dr;
        long long rem = abs_val(nr % dr);
        sprintf(ans, "%lld(%lld/%lld)", i, rem, dr);
    } else {
        sprintf(ans, "%lld/%lld", nr, dr);
    }
}

int main(void){
    char first[50], second[50], operators, next;
    char ans[50]; 

    while(1){
        scanf("%s", first);
        scanf(" %c", &operators);
        scanf("%s", second);
        scanf(" %c", &next);

        improper_fraction(first);
        improper_fraction(second);

        operation(first, second, operators, ans);

        printf("%s\n", ans);

        if (next == 'n') break;
    }
    
    return 0;
}