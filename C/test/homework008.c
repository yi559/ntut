#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "homework008.h"

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

#ifndef TESTING
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
#endif