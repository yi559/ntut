#include <stdio.h>
#include <string.h>

float change(char s[]){
    if (strcmp(s, "10") == 0) return 10.0;

    char c = s[0];
    if (c >= '2' && c <= '9'){
        return (float)(c - '0');
    }

    if (c == 'A') return 1.0;
    if (c == 'J' || c == 'Q' || c == 'K') return 0.5;

    return 0.0;
}

int main(void){
    float x = 0, y = 0;
    char s[10]; 

    for (int i = 0 ; i < 3 ; i++){
        scanf("%9s", s); 
        x += change(s);
    }
    for (int i = 0 ; i < 3 ; i++){
        scanf("%9s", s);
        y += change(s);
    }

    if (x > 10.5) x = 0;
    if (y > 10.5) y = 0;

    printf("%g\n", x);
    printf("%g\n", y);

    if (x > y) printf("X Win\n");
    else if (y > x) printf("Y Win\n");
    else printf("Tie\n"); 
    
    return 0;
}