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