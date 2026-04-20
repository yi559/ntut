/*分數運算

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
#include <stdlib.h>
#include <string.h>

long long gcd(long long a, long long b) {
    a = llabs(a);
    b = llabs(b);
    while (b) {
        a %= b;
        long long temp = a;
        a = b;
        b = temp;
    }
    return a;
}

typedef struct {
    long long num;
    long long den;
    int is_error;
} Fraction;

Fraction parse_fraction(char *s) {
    Fraction f = {0, 1, 0};
    long long a, b, c;
    
    if (sscanf(s, "%lld(%lld/%lld)", &a, &b, &c) == 3) {
        if (c == 0) { f.is_error = 1; return f; }
        if (a < 0) f.num = a * c - b;
        else f.num = a * c + b;
        f.den = c;
    } else if (sscanf(s, "%lld/%lld", &b, &c) == 2) {
        if (c == 0) { f.is_error = 1; return f; }
        f.num = b;
        f.den = c;
    } else {
        f.num = atoll(s);
        f.den = 1;
    }
    return f;
}

void print_fraction(Fraction f) {
    if (f.is_error || f.den == 0) {
        printf("error\n");
        return;
    }
    if (f.num == 0) {
        printf("0\n");
        return;
    }

    long long common = gcd(f.num, f.den);
    f.num /= common;
    f.den /= common;
 
    if (f.den < 0) {
        f.num = -f.num;
        f.den = -f.den;
    }

    long long integer_part = f.num / f.den;
    long long remainder_num = llabs(f.num % f.den);

    if (remainder_num == 0) {
        printf("%lld\n", integer_part);
    } else {
        if (integer_part == 0) {
            if (f.num < 0) printf("-");
            printf("%lld/%lld\n", remainder_num, f.den);
        } else {
            printf("%lld(%lld/%lld)\n", integer_part, remainder_num, f.den);
        }
    }
}

int main() {
    char s1[100], op[2], s2[100], cont[2];
    
    while (1) {
        if (scanf("%s %s %s %s", s1, op, s2, cont) != 4) break;

        Fraction f1 = parse_fraction(s1);
        Fraction f2 = parse_fraction(s2);
        Fraction res = {0, 1, 0};

        if (f1.is_error || f2.is_error) {
            res.is_error = 1;
        } else {
            if (op[0] == '+') {
                res.num = f1.num * f2.den + f2.num * f1.den;
                res.den = f1.den * f2.den;
            } else if (op[0] == '-') {
                res.num = f1.num * f2.den - f2.num * f1.den;
                res.den = f1.den * f2.den;
            } else if (op[0] == '*') {
                res.num = f1.num * f2.num;
                res.den = f1.den * f2.den;
            } else if (op[0] == '/') {
                if (f2.num == 0) res.is_error = 1;
                else {
                    res.num = f1.num * f2.den;
                    res.den = f1.den * f2.num;
                }
            }
        }

        print_fraction(res);
        if (cont[0] == 'n') break;
    }

    return 0;
}