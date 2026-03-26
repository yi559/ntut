#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(void){
    int M, N;
    long long decimal=0;
    char data[10];
    char result[100];

    scanf("%d %s %d", &M, data, &N);

    int len = strlen(data);
    for (int i = 0; i < len; i++){
        int val;
        char c = data[i];
        if (isdigit(c)) 
            val = c - '0';
        else 
            val = c - 'A' + 10;
        
        decimal = decimal * M + val;
    }

    if (decimal == 0){
        printf("0");
    }else{
        int idx = 0;
        while (decimal > 0) {
            int rem = decimal % N;
            if (rem < 10) result[idx++] = rem + '0';
            else result[idx++] = (rem - 10) + 'A';
            decimal /= N;
        }
        for (int i = idx - 1; i >= 0; i--) {
            putchar(result[i]);
        }
    }
    return 0;
}