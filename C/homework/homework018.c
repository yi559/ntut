/*018 長浮點數運算

請撰寫一程式，輸入兩個長浮點數（包含整數部分與小數部分，可能為正、負或零），計算並輸出兩數相加 (+)、相減 (-) 與相乘 (*) 的結果。輸出的整數部分與小數部分最大長度各需支援至 60 位。

【輸入說明】
-共兩行，每行各包含一個長浮點數。
-數字格式：整數部分與小數部分以小數點(.) 分隔。
-若為負數，開頭會有負號 (-);正數則無符號。
-數字長度（不含符號與小數點）：整數部分 <= 60位，小數部分 <= 60位。輸入不包含多餘的前導零。

範例輸入說明:
561561151564564987.561312318456465646451468461536445648941
6541655656464565.554644646999999945611

【輸出說明】
-第一行：輸出兩數相加的結果。
-第二行：輸出兩數相減的結果。
-第三行：輸出兩數相乘的結果。
-若結果為負數，負號必須顯示在最前面。
-若結果為 0，直接輸出 0。
-小數部分若為全 0，省略小數點與小數部分。

範例輸出說明:
568102807221029553.115956965456465592062468461536445648941
555019495908100422.006667671456465700840468461536445648941
3673539683583091767903507186701247.434856662235872099446851000885001205407648714321257599747951

【測試資料一】
輸入：
561561151564564987.561312318456465646451468461536445648941
6541655656464565.554644646999999945611

輸出：
568102807221029553.115956965456465592062468461536445648941
555019495908100422.006667671456465700840468461536445648941
3673539683583091767903507186701247.434856662235872099446851000885001205407648714321257599747951


【測試資料二】
輸入：
6455345646415646531879564161.5313
-5645646546456465651.4565646165489798465464

輸出：
6455345640769999985423098510.0747353834510201534536
6455345652061293078336029812.9878646165489798465464
-36444599854869275678931156617041753522072011927.29638644544436605604050232


【測試資料三】
輸入：
-53156313351.56356131651518489999
6546556465.5631561560000001

輸出：
-46609756886.00040516051518479999
-59702869817.12671747251518499999
-347990806857179555289.254412074010238935613744489958489999

【測試資料四】
輸入：
-51551315156151651656151561.564164661561564161111100001
-456465465465487941051641.54156415665564874897897971

輸出：
-52007780621617139597203203.105728818217212910090079711
-51094849690686163715099920.022600504905915412132120291
23531395068110826834284557857357124426712808936571.66675538568731842068294886919511539014938670475997971


【測試資料五】
輸入：
51698465156316131561.9996513153131311
-51698465156316131561.9996513153131311

輸出：
0
103396930312632263123.9993026306262622
-2672731299518833137421601593582223294188.75049262908856725686284408578721


【測試資料六】
輸入：
-56465153165116464165465.5616168498411111011
56465153165116464165465.5616168498411111011

輸出：
0
-112930306330232928330931.1232336996822222022
-3188313521960061851107507244358180236003616467.56982096194294015722487275219365442121
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 300

void reverse(char* str) {
    int len = strlen(str);
    for (int i = 0, j = len - 1; i < j; i++, j--) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

int find_dot(const char *s) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '.') return i;
    }
    return strlen(s);
}

void clean_format(char *str) {
    if (strcmp(str, "0") == 0 || strcmp(str, "-0") == 0 || str[0] == '\0') {
        strcpy(str, "0");
        return;
    }

    int has_dot = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '.') has_dot = 1;
    }

    if (has_dot) {
        int len = strlen(str);
        int right = len - 1;
        while (right >= 0 && str[right] == '0') {
            str[right] = '\0';
            right--;
        }
        if (right >= 0 && str[right] == '.') {
            str[right] = '\0';
        }
    }

    char *start = str;
    int is_neg = (str[0] == '-');
    if (is_neg) start++;

    while (*start == '0' && *(start + 1) != '\0' && *(start + 1) != '.') {
        start++;
    }

    if (start != str) {
        if (is_neg) {
            char temp[MAX_LEN];
            snprintf(temp, sizeof(temp), "-%s", start);
            strcpy(str, temp);
        } else {
            memmove(str, start, strlen(start) + 1);
        }
    }

    if (strcmp(str, "-0") == 0 || str[0] == '\0') {
        strcpy(str, "0");
    }
}

int cmp_abs(const char *a, const char *b) {
    int dot_a = find_dot(a), dot_b = find_dot(b);
    if (dot_a > dot_b) return 1;
    if (dot_a < dot_b) return -1;

    int len_a = strlen(a), len_b = strlen(b);
    int max_len = (len_a > len_b) ? len_a : len_b;

    for (int i = 0; i < max_len; i++) {
        if (i < len_a && a[i] == '.') continue;
        int num_a = (i < len_a) ? a[i] - '0' : 0;
        int num_b = (i < len_b) ? b[i] - '0' : 0;
        if (num_a > num_b) return 1;
        if (num_a < num_b) return -1;
    }
    return 0;
}

void adder(const char *s1, const char *s2, char *ans) {
    int len1 = strlen(s1), len2 = strlen(s2);
    int dot1 = find_dot(s1), dot2 = find_dot(s2);
    int frac1 = (dot1 == len1) ? 0 : len1 - dot1 - 1;
    int frac2 = (dot2 == len2) ? 0 : len2 - dot2 - 1;
    
    int max_int = (dot1 > dot2) ? dot1 : dot2;
    int max_frac = (frac1 > frac2) ? frac1 : frac2;
    int carry = 0, k = 0;

    for (int i = max_frac - 1; i >= 0; i--) {
        int n1 = (i < frac1) ? s1[dot1 + 1 + i] - '0' : 0;
        int n2 = (i < frac2) ? s2[dot2 + 1 + i] - '0' : 0;
        int sum = n1 + n2 + carry;
        ans[k++] = (sum % 10) + '0';
        carry = sum / 10;
    }
    if (max_frac > 0) ans[k++] = '.';

    for (int i = 0; i < max_int; i++) {
        int n1 = (dot1 - 1 - i >= 0) ? s1[dot1 - 1 - i] - '0' : 0;
        int n2 = (dot2 - 1 - i >= 0) ? s2[dot2 - 1 - i] - '0' : 0;
        int sum = n1 + n2 + carry;
        ans[k++] = (sum % 10) + '0';
        carry = sum / 10;
    }
    if (carry > 0) ans[k++] = carry + '0';
    ans[k] = '\0';
    reverse(ans);
}

void subtractor(const char *s1, const char *s2, char *ans) {
    int len1 = strlen(s1), len2 = strlen(s2);
    int dot1 = find_dot(s1), dot2 = find_dot(s2);
    int frac1 = (dot1 == len1) ? 0 : len1 - dot1 - 1;
    int frac2 = (dot2 == len2) ? 0 : len2 - dot2 - 1;
    
    int max_int = dot1;
    int max_frac = (frac1 > frac2) ? frac1 : frac2;
    int borrow = 0, k = 0;

    for (int i = max_frac - 1; i >= 0; i--) {
        int n1 = (i < frac1) ? s1[dot1 + 1 + i] - '0' : 0;
        int n2 = (i < frac2) ? s2[dot2 + 1 + i] - '0' : 0;
        int sub = n1 - n2 - borrow;
        if (sub < 0) { sub += 10; borrow = 1; }
        else { borrow = 0; }
        ans[k++] = sub + '0';
    }
    if (max_frac > 0) ans[k++] = '.';

    for (int i = 0; i < max_int; i++) {
        int n1 = (dot1 - 1 - i >= 0) ? s1[dot1 - 1 - i] - '0' : 0;
        int n2 = (dot2 - 1 - i >= 0) ? s2[dot2 - 1 - i] - '0' : 0;
        int sub = n1 - n2 - borrow;
        if (sub < 0) { sub += 10; borrow = 1; }
        else { borrow = 0; }
        ans[k++] = sub + '0';
    }
    ans[k] = '\0';
    reverse(ans);
}

void multiplier(const char *s1, const char *s2, char *ans) {
    int len1 = strlen(s1), len2 = strlen(s2);
    int dot1 = find_dot(s1), dot2 = find_dot(s2);
    int frac1 = (dot1 == len1) ? 0 : len1 - dot1 - 1;
    int frac2 = (dot2 == len2) ? 0 : len2 - dot2 - 1;
    int total_frac = frac1 + frac2;

    char pure1[MAX_LEN], pure2[MAX_LEN];
    int p1_len = 0, p2_len = 0;
    for (int i = 0; i < len1; i++) if (s1[i] != '.') pure1[p1_len++] = s1[i];
    for (int i = 0; i < len2; i++) if (s2[i] != '.') pure2[p2_len++] = s2[i];

    int res[MAX_LEN] = {0};

    for (int i = p1_len - 1; i >= 0; i--) {
        for (int j = p2_len - 1; j >= 0; j--) {
            int mul = (pure1[i] - '0') * (pure2[j] - '0');
            int p1 = i + j, p2 = i + j + 1;
            int sum = mul + res[p2];

            res[p2] = sum % 10;
            res[p1] += sum / 10;
        }
    }

    int k = 0;
    int res_len = p1_len + p2_len;
    int dot_pos = res_len - total_frac;

    for (int i = 0; i < res_len; i++) {
        if (total_frac > 0 && i == dot_pos) {
            ans[k++] = '.';
        }
        ans[k++] = res[i] + '0';
    }
    ans[k] = '\0';
}

void do_add(const char *n1, const char *n2, char *ans) {
    int is_neg1 = (n1[0] == '-'), is_neg2 = (n2[0] == '-');
    const char *p1 = is_neg1 ? n1 + 1 : n1;
    const char *p2 = is_neg2 ? n2 + 1 : n2;
    char temp[MAX_LEN];

    if (!is_neg1 && !is_neg2) {
        adder(p1, p2, temp);
    } else if (is_neg1 && is_neg2) {
        adder(p1, p2, temp);
        sprintf(ans, "-%s", temp);
        clean_format(ans);
        return;
    } else if (!is_neg1 && is_neg2) {
        if (cmp_abs(p1, p2) >= 0) subtractor(p1, p2, temp);
        else { subtractor(p2, p1, temp); sprintf(ans, "-%s", temp); clean_format(ans); return; }
    } else {
        if (cmp_abs(p2, p1) >= 0) subtractor(p2, p1, temp);
        else { subtractor(p1, p2, temp); sprintf(ans, "-%s", temp); clean_format(ans); return; }
    }
    strcpy(ans, temp);
    clean_format(ans);
}

void do_sub(const char *n1, const char *n2, char *ans) {
    int is_neg1 = (n1[0] == '-'), is_neg2 = (n2[0] == '-');
    const char *p1 = is_neg1 ? n1 + 1 : n1;
    const char *p2 = is_neg2 ? n2 + 1 : n2;
    char temp[MAX_LEN];

    if (!is_neg1 && !is_neg2) {
        if (cmp_abs(p1, p2) >= 0) subtractor(p1, p2, temp);
        else { subtractor(p2, p1, temp); sprintf(ans, "-%s", temp); clean_format(ans); return; }
    } else if (is_neg1 && is_neg2) {
        if (cmp_abs(p2, p1) >= 0) subtractor(p2, p1, temp);
        else { subtractor(p1, p2, temp); sprintf(ans, "-%s", temp); clean_format(ans); return; }
    } else if (!is_neg1 && is_neg2) {
        adder(p1, p2, temp);
    } else {
        adder(p1, p2, temp);
        sprintf(ans, "-%s", temp);
        clean_format(ans);
        return;
    }
    strcpy(ans, temp);
    clean_format(ans);
}

void do_mul(const char *n1, const char *n2, char *ans) {
    if (strcmp(n1, "0") == 0 || strcmp(n2, "0") == 0) {
        strcpy(ans, "0");
        return;
    }

    int is_neg1 = (n1[0] == '-'), is_neg2 = (n2[0] == '-');
    const char *p1 = is_neg1 ? n1 + 1 : n1;
    const char *p2 = is_neg2 ? n2 + 1 : n2;
    char temp[MAX_LEN];

    multiplier(p1, p2, temp);

    if (is_neg1 ^ is_neg2) {
        sprintf(ans, "-%s", temp);
    } else {
        strcpy(ans, temp);
    }
    clean_format(ans);
}

int main(void) {
    char num1[MAX_LEN], num2[MAX_LEN];
    char add_ans[MAX_LEN], sub_ans[MAX_LEN], mul_ans[MAX_LEN];

    if (scanf("%s", num1) == 1 && scanf("%s", num2) == 1) {
        do_add(num1, num2, add_ans);
        do_sub(num1, num2, sub_ans);
        do_mul(num1, num2, mul_ans);

        printf("%s\n", add_ans);
        printf("%s\n", sub_ans);
        printf("%s\n", mul_ans);
    }

    return 0;
}