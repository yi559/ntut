/*
019 大數除法
請撰寫一程式，輸入兩個大數整數，計算並輸出兩數相除 (/) 的結果。輸入的整數部分最大長度需支援至 100 位。

【輸入說明】
- 共兩行，每行各包含一個整數。
- 數字長度（不含符號）滿足 1 <= 位數 <= 100。
- 負數輸入會以 - 開頭，正數則無符號。
- 輸入不包含多餘的前導零（例如:00123）
- 除數不為0。

範例輸入說明:
561651651641616585615168
8789896545646546546546546545

【輸出說明】
-第一行：輸出第一行輸入大數除以第二行輸入大數的結果，精確至小數後100位(無條件捨去)。
-若結果為負數，負號必須顯示在最前面。
-當商小於 1 時，整數部分應顯示 0。
-小數部分末尾若有多餘的 0 必須去除。若小數部分全為 0，則省略小數點。
-若結果為 0，直接輸出 0。

範例輸出說明:
0.0000638974132090088136266711504330108022047811740580016393508386512247549054919848477554807164036891

【測試資料一】
輸入：
4534534535995165165161651
99956651651651651651454535434

輸出：
0.0000453650103426632535755907261508426787440597369399154208522541004893405150403003606712780036823468

【測試資料二】
輸入：
-99485111511613131894161651
-65616518161616515646165165161616

輸出：
0.000001516159563154154356888844993736042429497901276513858910718522047603245880549184413247296067319

【測試資料三】
輸入：
9999654174541651561654165415615616541654654
-6541651654165161651651651651465146654165444

輸出：
-1.5286130633652330065468314355861751449171060788940748097204110218294313662223526230132854827737207443

【測試資料四】
輸入：
-45156156156115161131321361561231561651
51651651561561515313514151561

輸出：
-874244187.5705632411471953478501844547842474724754131584826102234482774800613052965013599060144061478203877585

【測試資料五】
輸入：
0
8885613521515251653515135841561651651310631516

輸出：
0

【測試資料六】
輸入：
-4646546546546546546546546546465489789465999
4646546546546546546546546546465489789465999

輸出：
-1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 500

void clean_leading_zeros(char *s) {
    int len = strlen(s);
    int i = 0;
    while (i < len - 1 && s[i] == '0') {
        i++;
    }
    if (i > 0) {
        memmove(s, s + i, len - i + 1);
    }
}

void append_char(char *s, char c) {
    int len = strlen(s);
    if (len == 1 && s[0] == '0') {
        s[0] = c;
        s[1] = '\0';
    } else {
        s[len] = c;
        s[len + 1] = '\0';
    }
}

int cmp_abs(const char *a, const char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    if (len_a > len_b) return 1;
    if (len_a < len_b) return -1;
    return strcmp(a, b);
}

void subtractor(const char *a, const char *b, char *res) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int borrow = 0, k = 0;
    char temp[MAX_LEN];

    for (int i = 0; i < len_a; i++) {
        int na = a[len_a - 1 - i] - '0';
        int nb = (i < len_b) ? b[len_b - 1 - i] - '0' : 0;
        int diff = na - nb - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        temp[k++] = diff + '0';
    }
    
    while (k > 1 && temp[k - 1] == '0') {
        k--;
    }
    temp[k] = '\0';

    for (int i = 0; i < k; i++) {
        res[i] = temp[k - 1 - i];
    }
    res[k] = '\0';
}

void do_divide(const char *n1, const char *n2) {
    int is_neg1 = (n1[0] == '-');
    int is_neg2 = (n2[0] == '-');
    int out_neg = is_neg1 ^ is_neg2;

    const char *p1 = is_neg1 ? n1 + 1 : n1;
    const char *p2 = is_neg2 ? n2 + 1 : n2;

    if (strcmp(p1, "0") == 0) {
        printf("0\n");
        return;
    }

    char B_mult[10][MAX_LEN];
    strcpy(B_mult[0], "0");
    for (int i = 1; i <= 9; i++) {
        int carry = 0, k = 0;
        int len_p2 = strlen(p2);
        char temp[MAX_LEN];
        for (int j = len_p2 - 1; j >= 0; j--) {
            int prod = (p2[j] - '0') * i + carry;
            temp[k++] = (prod % 10) + '0';
            carry = prod / 10;
        }
        if (carry) temp[k++] = carry + '0';
        
        for (int j = 0; j < k; j++) B_mult[i][j] = temp[k - 1 - j];
        B_mult[i][k] = '\0';
    }

    char current_rem[MAX_LEN] = "0";
    char int_ans[MAX_LEN] = "";
    int int_ans_len = 0;

    for (int i = 0; p1[i] != '\0'; i++) {
        append_char(current_rem, p1[i]);
        
        int d = 9;
        while (d > 0 && cmp_abs(current_rem, B_mult[d]) < 0) {
            d--;
        }
        
        int_ans[int_ans_len++] = d + '0';
        int_ans[int_ans_len] = '\0';
        
        char next_rem[MAX_LEN];
        subtractor(current_rem, B_mult[d], next_rem);
        strcpy(current_rem, next_rem);
    }
    
    clean_leading_zeros(int_ans);
    if (int_ans_len == 0 || int_ans[0] == '\0') {
        strcpy(int_ans, "0");
    }

    char dec_ans[MAX_LEN] = "";
    int dec_ans_len = 0;
    
    for (int i = 0; i < 100; i++) {
        if (strcmp(current_rem, "0") == 0) {
            break;
        }
        
        append_char(current_rem, '0');
        
        int d = 9;
        while (d > 0 && cmp_abs(current_rem, B_mult[d]) < 0) {
            d--;
        }
        
        dec_ans[dec_ans_len++] = d + '0';
        dec_ans[dec_ans_len] = '\0';
        
        char next_rem[MAX_LEN];
        subtractor(current_rem, B_mult[d], next_rem);
        strcpy(current_rem, next_rem);
    }

    while (dec_ans_len > 0 && dec_ans[dec_ans_len - 1] == '0') {
        dec_ans[--dec_ans_len] = '\0';
    }

    if (strcmp(int_ans, "0") == 0 && dec_ans_len == 0) {
        out_neg = 0;
    }

    if (out_neg) printf("-");
    printf("%s", int_ans);
    if (dec_ans_len > 0) {
        printf(".%s", dec_ans);
    }
    printf("\n");
}

int main(void) {
    char num1[MAX_LEN], num2[MAX_LEN];

    if (scanf("%s", num1) == 1 && scanf("%s", num2) == 1) {
        do_divide(num1, num2);
    }

    return 0;
}