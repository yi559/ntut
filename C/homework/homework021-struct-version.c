#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int top, bottom, left, right, front, back;
} Dice;

void rotateVertical(Dice *d, char *direction) {
    int times = atoi(direction + 1) % 4;
    if (direction[0] == 'B') times = (times * 3) % 4;

    while (times--) {
        int temp = d->top;
        d->top = d->back;
        d->back = d->bottom;
        d->bottom = d->front;
        d->front = temp;
    }
}

void rotateHorizontal(Dice *d, char *direction) {
    int times = atoi(direction + 1) % 4;
    if (direction[0] == 'R') times = (times * 3) % 4;

    while (times--) {
        int temp = d->top;
        d->top = d->right;
        d->right = d->bottom;
        d->bottom = d->left;
        d->left = temp;
    }
}

int calculateScore(Dice *d) {
    int p[3] = {d[0].top, d[1].top, d[2].top};
    if (p[0] == p[1] && p[1] == p[2]) return p[0] * 2;
    if (p[0] == p[1]) return p[2];
    if (p[1] == p[2]) return p[0];
    if (p[0] == p[2]) return p[1];
    return 0;
}

int main() {
    Dice A[3], B[3];
    int N;

    for (int i = 0; i < 3; i++) {
        int t, b, l, r, f, ba;
        scanf("%d %d %d %d %d %d", &t, &b, &l, &r, &f, &ba);
        A[i] = (Dice){t, b, l, r, f, ba};
        B[i] = A[i];
    }

    scanf("%d", &N);
    char cmd[10];
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%s", cmd);
            if (cmd[0] == 'F' || cmd[0] == 'B') rotateVertical(&A[i], cmd);
            else rotateHorizontal(&A[i], cmd);
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%s", cmd);
            if (cmd[0] == 'F' || cmd[0] == 'B') rotateVertical(&B[i], cmd);
            else rotateHorizontal(&B[i], cmd);
        }
    }

    int scoreA = calculateScore(A);
    int scoreB = calculateScore(B);

    if (scoreA > scoreB) printf("A win\n");
    else if (scoreB > scoreA) printf("B win\n");
    else printf("Tie\n");

    printf("%d %d\n", scoreA, scoreB);

    return 0;
}