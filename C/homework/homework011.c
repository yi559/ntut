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