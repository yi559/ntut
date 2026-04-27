#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void scrollFront(int *dice, char *dir){
    int times = atoi(dir+1) % 4;
    if (dir[0] == 'B') times = (times * 3) % 4;

    while(times--){
        int temp = dice[0];
        dice[0] = dice[5];
        dice[5] = dice[1];
        dice[1] = dice[4];
        dice[4] = temp;
    }
}

void scrollLeft(int *dice, char *dir){
    int times = atoi(dir+1) % 4;
    if (dir[0] == 'R') times = (times * 3) % 4;

    while(times--){
        int temp = dice[0];
        dice[0] = dice[3];
        dice[3] = dice[1];
        dice[1] = dice[2];
        dice[2] = temp;
    }
}

void time(int *x, int *y, char *dir){
    if (dir[0] == 'F') *x -= atoi(dir+1);
    else if (dir[0] == 'B') *x += atoi(dir+1);
    else if (dir[0] == 'L') *y -= atoi(dir+1);
    else if (dir[0] == 'R') *y += atoi(dir+1);
}

void retime(int *x, int *y, char *dir){
    if (dir[0] == 'F') *x += atoi(dir+1);
    else if (dir[0] == 'B') *x -= atoi(dir+1);
    else if (dir[0] == 'L') *y += atoi(dir+1);
    else if (dir[0] == 'R') *y -= atoi(dir+1);
}

int main(void){
    int n=0;
    scanf("%d", &n);

    int plastic[10][10];
    for (int i=0 ; i<n ; i++){
        for (int j=0 ; j<n ; j++){
            scanf("%d", &plastic[i][j]);
        }
    }

    int dice[10];
    char dir[100];
    int k=0,x=0,y=0;
    scanf("%d", &k);
    scanf("%d %d %d %d %d %d ", &dice[0], &dice[1], &dice[2], &dice[3], &dice[4], &dice[5]);//上下左右前後

    int total=0;
    while(k--){
        scanf("%s" , dir);

        time(&x,&y,dir);
        if (x>=0 && x<n && y>=0 && y<n){
            if (dir[0] == 'F' || dir[0] == 'B') scrollFront(dice,dir);
            else scrollLeft(dice,dir);
            total += dice[0] * plastic[x][y];
        }else{
            retime(&x,&y,dir);
        }

    }

    printf("(%d,%d)\n", x, y);
    printf("%d", total);

}