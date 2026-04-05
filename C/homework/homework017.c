/*
017 大數運算

請撰寫一程式，輸入兩個大整數（可能為正、負或零），計算並輸出兩數相加 (+)、相減 (-) 與相乘 (*) 的結果。

【輸入說明】
- 共兩行，每行各包含一個整數。
- 數字長度（不含符號）滿足 1 <= 位數 <= 100。
- 負數輸入會以 - 開頭，正數則無符號。
- 輸入不包含多餘的前導零（例如:00123）。

範例輸入說明:
561651651641616585615168
8789896545646546546546546545

【輸出說明】
第一行輸出相加的結果 (1<=輸出位數<=101)
第二行輸出相減的結果 (1<=輸出位數<=101)
第三行輸出相乘的結果 (1<=輸出位數<=200)

範例輸出說明:
8790458197298188163132161713
-8789334893994904929960931377
4936859912621323139844513105778629278692394769994560

【測試資料一】
輸入：
4534534535995165165161651
99956651651651651651454535434

輸出：
99961186186187646816619697085
-99952117117115656486289373783
453256889016852581953231905042237629576284233717441534

【測試資料二】
輸入：
-99485111511613131894161651
-65616518161616515646165165161616

輸出：
-65616617646728027259297059323267
65616418676505004033033270999965
6527866626312207359146741983744257449884858679294244388016

【測試資料三】
輸入：
9999654174541651561654165415615616541654654
-6541651654165161651651651651465146654165444

輸出：
3458002520376489910002513764150469887489210
16541305828706813213305817067080763195820098
-65414254271969959029599286664161440719533332822203505376428354678452577994745228576376

【測試資料四】
輸入：
-45156156156115161131321361561231561651
51651651561561515313514151561

輸出：
-45156156104463509569759846247717410090
-45156156207766812692882876874745713212
-2332390043635121295325476520619957306665418400256292666268329387211

【測試資料五】
輸入：
8885613521515251653515135841561651651310631516
8885613521515251653515135841561651651310631516

輸出：
17771227043030503307030271683123303302621263032
0
78954127653734671559648880690313932932989188703994051754995126309891489120724557770732458256

【測試資料六】
輸入：
-4646546546546546546546546546465489789465999
4646546546546546546546546546465489789465999

輸出：
0
-9293093093093093093093093092930979578931998
-21590394809223638052466881294956856549579606708494079665257406619876008073585577068001
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char* str) {
    int len = strlen(str), i = 0, j = len - 1;
    char temp;

    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;

        i++;
        j--;
    }
}

int compare(char s1[], char s2[]) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    if (len1 > len2) return 1;
    if (len1 < len2) return -1;
    return strcmp(s1, s2);
}

void adder(char s1[], char s2[], char ans[]) {
    int i = strlen(s1) - 1;
    int j = strlen(s2) - 1;
    int carry = 0;
    int k = 0;

    while (i >= 0 || j >= 0 || carry > 0) {
        int n1 = (i >= 0) ? s1[i] - '0' : 0;
        int n2 = (j >= 0) ? s2[j] - '0' : 0;

        int sum = n1 + n2 + carry;
        ans[k++] = (sum % 10) + '0';
        carry = sum / 10;

        i--;
        j--;
    }
    ans[k] = '\0';
    reverse(ans);
}

void subtractor(char s1[], char s2[], char ans[]){
    int i = strlen(s1) - 1;
    int j = strlen(s2) - 1;
    int borrow = 0;
    int k = 0;

    while(i >= 0){
        int n1 = s1[i] - '0';
        int n2 = (j >= 0) ? s2[j] - '0' : 0;

        int sub = n1 - n2 - borrow;

        if (sub < 0){
            sub += 10;
            borrow = 1; 
        }else{
            borrow = 0;
        }

        ans[k++] = sub + '0';
        i--;
        j--;
    }
    
    while (k > 1 && ans[k - 1] == '0') {
        k--;
    }

    ans[k] = '\0';
    reverse(ans);
}

void multiplier(char s1[], char s2[], char ans[]){
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int res[205] = {0};

    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int mul = (s1[i] - '0') * (s2[j] - '0');
            res[i + j + 1] += mul;
        }
    }

    int k = len1 + len2 - 1;
    for (int i = k; i > 0; i--) {
        res[i - 1] += res[i] / 10;
        res[i] %= 10;
    }

    int start = 0, idx = 0;
    while (start < k && res[start] == 0) start++;
    while (start <= k) {
        ans[idx++] = res[start++] + '0';
    }
    ans[idx] = '\0';
}

int main(void){
    char num1[105], num2[105], addans[200], subans[200], mulans[10000];
    scanf("%s", num1);
    scanf(" %s", num2);
    
    int neg1 = (num1[0] == '-');
    int neg2 = (num2[0] == '-');
    
    char *abs1 = neg1 ? num1 + 1 : num1;
    char *abs2 = neg2 ? num2 + 1 : num2;
    
    int cmp = compare(abs1, abs2);

    if (neg1 == neg2) {
        adder(abs1, abs2, addans);
        if (neg1 && strcmp(addans, "0") != 0) printf("-");
        printf("%s\n", addans);
    } else {
        if (cmp == 0) {
            printf("0\n");
        } else if (cmp > 0) {
            subtractor(abs1, abs2, addans);
            if (neg1) printf("-");
            printf("%s\n", addans);
        } else {
            subtractor(abs2, abs1, addans);
            if (neg2) printf("-");
            printf("%s\n", addans);
        }
    }

    int sub_neg2 = !neg2;
    
    if (neg1 == sub_neg2) {
        adder(abs1, abs2, subans);
        if (neg1 && strcmp(subans, "0") != 0) printf("-");
        printf("%s\n", subans);
    } else {
        if (cmp == 0) {
            printf("0\n");
        } else if (cmp > 0) {
            subtractor(abs1, abs2, subans);
            if (neg1) printf("-");
            printf("%s\n", subans);
        } else {
            subtractor(abs2, abs1, subans);
            if (sub_neg2) printf("-");
            printf("%s\n", subans);
        }
    }

    multiplier(abs1, abs2, mulans);
    
    if (neg1 != neg2 && strcmp(mulans, "0") != 0) {
        printf("-");
    }
    printf("%s\n", mulans);

    return 0;
}