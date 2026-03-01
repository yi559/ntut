#include <stdio.h>

int main(void) {
    int hitter, score = 0;
    int player = 0;
    int one=0,two=0,thr=0;
    for (int i = 0; i < 3; i++) {
        scanf("%d", &hitter);

        if (hitter > 0) {
            player |= 1; 
            
            for (int j = 0; j < hitter; j++) {
                player <<= 1;
                if ((player & (1 << 4))) {
                    score += 1;
                    player &= ~(1 << 4);
                }
            }
        }
    }
    printf("%d\n", score);
    one = (player & (1 << 1)) ? 1 : 0;
    two = (player & (1 << 2)) ? 1 : 0;
    thr = (player & (1 << 3)) ? 1 : 0;
    printf("%d %d %d", one,two,thr);
    return 0;
}