/*
008 辨識輸入資料

請透過狀態轉換判斷輸入值為以下何種型態：
1. 整數
2. 真分數
3. 假分數
4. 帶分數
5. 浮點數
6. 合法變數
7. 一般字串

【整數規則】
1.整數除了負號必須所有字元皆為數字，且必須至少包含一個數字字元，也不能有前導零。
2.負號最多只有一個，且只能位於開頭。
3.輸入為 0 或 -0 的狀況也視為整數
4.長度介於 1~50 個字元。

【真分數規則】
1.真分數除了負號及除號必須所有字元皆為數字，且分子、分母皆為非 0 整數，也不能有前導零。
2.分子的絕對值必須小於分母的絕對值。
3.負號最多只有一個，且只能位於開頭。
4.長度介於 1~10 個字元。

【假分數規則】
1.假分數除了負號及除號必須所有字元皆為數字，且分子、分母皆為非 0 整數，也不能有前導零。
2.分子的絕對值必須大於等於分母的絕對值。
3.負號最多只有一個，且只能位於開頭。
4.長度介於 1~10 個字元。

【帶分數規則】
1.帶分數除了負號、分隔整數和真分數的空白及除號必須所有字元皆為數字，且分子、分母皆為非 0 整數，也不能有前導零。
2.帶分數由一個整數在前和一個真分數在後組成，中間由單一個空白分隔
3.負號最多只有一個，且只能位於開頭。
4.長度介於 1~10 個字元。

【浮點數規則】
1.浮點數除了小數點、負號，所有字元皆為數字，整數部分不可有前導零（例如 01.5 不合法），但整數部分為 0 的狀況例外（如 0.5 或 -0.5 為合法）。
2.開頭不可為小數點，結尾也不可為小數點，且小數點有且只有一個。
3.負號最多只有一個，且只能位於開頭。
4.長度介於 3~50 個字元。

【變數規則】
1.由大小寫英文字母、或數字、或 _ 組成。
2.開頭為大小寫英文字母、或 _，不能以數字為開頭。
3.長度介於 1~10 個字元。

【一般字串】
1.不滿足所有以上規則，字串由數字、大小寫英文、特殊符號@ # $ % & \ _ ...等組成。
2.長度介於 1~50 個字元。


【輸入說明】
第一行輸入一個整數 N (1 <= N <= 7)，代表接下來輸入多少行字串。
其後 N 行為字串輸入，其長度為 1~50 個字元。

請注意！
1. 輸入時應忽略換行符 '\n' 和檔案結束符 EOF，不將它們視為輸入內容的一部分。
2. 一行輸入可能包含多個空白字元 Ex: AB1 14/2 77。

範例輸入說明:
5
_abc
123
0.567
1 1/2
ghj/644

【輸出說明】
依據輸入字串，輸出對應值，
若字串為整數，輸出integer
若字串為真分數，輸出proper fraction
若字串為假分數，輸出improper fraction
若字串為帶分數，輸出mixed fraction
若字串為浮點數，輸出float
若字串為變數，輸出variable
若以上情況皆不符合，輸出string

範例輸出說明:
variable (_abc符合變數規則)
integer (123符合整數規則)
float (0.567符合浮點數規則)
mixed fraction (1 1/2符合帶分數規則)
string (ghj/644不符合整數、變數、浮點數規則)

【測試資料一】
輸入：
4
_CisEZ_EMZ
CodeBlock
_1_0_1_1_0
TestP2P__


輸出：
variable
variable
variable
variable

【測試資料二】
輸入：
7
9874437434
5920000000
1234567890221126872995282646561238461235465481231
0
1634644357
-11155577788
6637373


輸出：
integer
integer
integer
integer
integer
integer
integer

【測試資料三】
輸入：
4
3.14159265358979323
-1454864.720404254
1414.7414
987654154.000000000000000000000000000000000000

輸出：
float
float
float
float

【測試資料四】
輸入：
7
s35!@567-8!67*
-0
357346.
_sdfs.123
00
0.
1.234.75

輸出：
string
integer
string
string
string
string
string

【測試資料五】
輸入：
5
_Pneumonoultramicroscopicsilicovolcanoconiosis1234
_abc
456
10.654
-0.

輸出：
string
variable
integer
float
string

【測試資料六】
輸入：
5
12/-4
8/9
2357 12/44
4.12/88
-99/3

輸出：
string
proper fraction
mixed fraction
string
improper fraction

【測試資料七】
輸入：
5
3 9
1/1
?/8
-44/789456
-8 6/9

輸出：
string
improper fraction
string
proper fraction
mixed fraction
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int is_pure_digits(char* s, int allow_zero) {
    int len = strlen(s);
    if (len == 0) return 0;
    for (int i = 0; i < len; i++) if (!isdigit(s[i])) return 0;
    if (len > 1 && s[0] == '0') return 0;
    if (!allow_zero && len == 1 && s[0] == '0') return 0;
    return 1;
}

int is_integer(char* s) {
    int len = strlen(s);
    if (len < 1 || len > 50) return 0;
    int i = 0;
    if (s[0] == '-') i = 1;
    if (s[i] == '\0') return 0;
    if (s[i] == '0') return (len - i == 1);
    return is_pure_digits(s + i, 1);
}

int is_variable(char* s) {
    int len = strlen(s);
    if (len < 1 || len > 10) return 0;
    if (!isalpha(s[0]) && s[0] != '_') return 0;
    for (int i = 1; i < len; i++) {
        if (!isalnum(s[i]) && s[i] != '_') return 0;
    }
    return 1;
}

int is_float(char* s) {
    int len = strlen(s);
    if (len < 3 || len > 50) return 0;
    int i = 0;
    if (s[0] == '-') i = 1;
    
    char *dot = strchr(s + i, '.');
    if (!dot || dot == s + i || *(dot + 1) == '\0') return 0;
    if (strchr(dot + 1, '.')) return 0;

    int int_len = dot - (s + i);
    if (int_len > 1 && s[i] == '0') return 0;
    for (int j = 0; j < int_len; j++) if (!isdigit(s[i + j])) return 0;
    for (char* d = dot + 1; *d; d++) if (!isdigit(*d)) return 0;
    return 1;
}

const char* check_fractions(char* s) {
    int len = strlen(s);
    if (len > 10) return NULL;

    char* space = strchr(s, ' ');
    if (space) {
        char part1[50], part2[50];
        int n = sscanf(s, "%s %s", part1, part2);
        if (n != 2) return NULL;
        
        if (!is_integer(part1)) return NULL;
        char* slash = strchr(part2, '/');
        if (!slash || strchr(slash + 1, '/')) return NULL;
        *slash = '\0';
        if (is_pure_digits(part2, 0) && is_pure_digits(slash + 1, 0)) {
            if (atoll(part2) < atoll(slash + 1)) return "mixed fraction";
        }
        return NULL;
    }

    char* slash = strchr(s, '/');
    if (slash) {
        int start = (s[0] == '-') ? 1 : 0;
        if (slash == s + start || *(slash + 1) == '\0') return NULL;
        
        char num_s[50], den_s[50];
        strncpy(num_s, s + start, slash - (s + start));
        num_s[slash - (s + start)] = '\0';
        strcpy(den_s, slash + 1);

        if (is_pure_digits(num_s, 0) && is_pure_digits(den_s, 0)) {
            long long n = atoll(num_s), d = atoll(den_s);
            return (n < d) ? "proper fraction" : "improper fraction";
        }
    }
    return NULL;
}

int main() {
    int N;
    char line[256];
    if (fgets(line, sizeof(line), stdin)) {
        N = atoi(line);
    }

    while (N--) {
        if (!fgets(line, sizeof(line), stdin)) break;
        line[strcspn(line, "\r\n")] = '\0';
        if (strlen(line) == 0) { N++; continue; }

        const char* frac_type = check_fractions(line);
        if (frac_type) printf("%s\n", frac_type);
        else if (is_integer(line)) printf("integer\n");
        else if (is_float(line)) printf("float\n");
        else if (is_variable(line)) printf("variable\n");
        else printf("string\n");
    }
    return 0;
}