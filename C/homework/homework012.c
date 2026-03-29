/*
012. 反轉字串

請使用指標來實作這次的作業。
輸入格式
1.輸入兩個字串（字串長度不固定，允許包含空格）。
2.字串的開頭與結尾只能是英文字母（a-z, A-Z）或底線 (‘_’)，否則輸出 Error 並立即結束程式。
若字串符合格式，則執行以下操作：
反轉字串。
輸出反轉後的字串。
忽略字串中的空白字元，比較兩個字串的實際長度（不計空格）。
輸出長度較長的字串的原始輸入值（即未反轉前的內容）。
若兩個字串長度相同，則輸出第一個字串的原始值。


【輸入說明】
第一行:第一個字串
第二行:第二個字串

範例輸入:
Hello World
C programming

【輸出說明】
第一行:第一個字串的反轉
第二行:第二個字串的反轉
第三行:不計空白字元的最長原始字串

範例輸出:
dlroW olleH
gnimmargorp C
C programming

【測試資料一】
輸入：
Hello World_
C programming

輸出：
_dlroW olleH
gnimmargorp C
C programming

【測試資料二】
輸入：
abcdef
123 456

輸出：
Error

【測試資料三】
輸入：
A B C D
ABCD

輸出：
D C B A
DCBA
A B C D

【測試資料四】
輸入：
a@!# $%^
1234

輸出：
Error
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check_format(char *ptr) {
    int size = strlen(ptr);
    if (size == 0) return 0;
    
    char head = *ptr;
    char tail = *(ptr + size - 1);
    
    if (!(isalpha(head) || head == '_')) return 0;
    if (!(isalpha(tail) || tail == '_')) return 0;
    
    return 1;
}

void perform_reverse(char *p_str) {
    int len = strlen(p_str);
    char *left = p_str;
    char *right = p_str + len - 1;
    char swap_tmp;
    
    while (left < right) {
        swap_tmp = *left;
        *left = *right;
        *right = swap_tmp;
        left++;
        right--;
    }
}

int count_pure_len(char *p_str) {
    int total = 0;
    while (*p_str) {
        if (*p_str != ' ') total++;
        p_str++;
    }
    return total;
}

int main() {
    char strA[1024], strB[1024];
    char backupA[1024], backupB[1024];

    if (!fgets(strA, sizeof(strA), stdin)) return 0;
    strA[strcspn(strA, "\n")] = '\0';
    
    if (!fgets(strB, sizeof(strB), stdin)) return 0;
    strB[strcspn(strB, "\n")] = '\0';

    if (!check_format(strA) || !check_format(strB)) {
        printf("Error\n");
        return 0;
    }

    strcpy(backupA, strA);
    strcpy(backupB, strB);

    perform_reverse(strA);
    perform_reverse(strB);
    printf("%s\n", strA);
    printf("%s\n", strB);

    int weightA = count_pure_len(backupA);
    int weightB = count_pure_len(backupB);

    if (weightA >= weightB) {
        printf("%s\n", backupA);
    } else {
        printf("%s\n", backupB);
    }

    return 0;
}