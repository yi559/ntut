#include <stdio.h>

int main(void){
    struct team{
        char name;
        int total_score;
        int win;
    }teams[3];
    int m=0;

    for (int i = 0 ; i<3 ; i++){
        teams[i].name = i+65;
        teams[i].total_score = 0;
        teams[i].win = 0;
    }
    
    scanf("%d", &m);
    for (int i=0 ; i<m ; i++){
        char t1, t2;
        int idx1, idx2, s1, s2;
        scanf(" %c %c", &t1, &t2);
        idx1 = t1-'A';
        idx2 = t2-'A';

        int gs1=0, gs2=0;
        for (int j=0 ; j<4 ; j++){
            scanf("%d %d", &s1, &s2);
            gs1 += s1;
            gs2 += s2;
        }

        teams[idx1].total_score += gs1;
        teams[idx2].total_score += gs2;

        if (gs1 > gs2){
            teams[idx1].win += 1;
        }else{
            teams[idx2].win += 1;
        }
    }

    int win_idx = 0;
    for (int i=0 ; i<3 ; i++){
        if (teams[i].win > teams[win_idx].win){
            win_idx = i;
        }
    }

    printf("%c %d", teams[win_idx].name, teams[win_idx].total_score);
    return 0;
}