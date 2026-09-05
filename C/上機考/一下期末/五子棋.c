/*Final_Exam1
五子棋
檢查10*10五子棋，找出所有「只差一顆棋子就能構成五子連線」的位置
連線方向包含水平（→）、垂直（↓）、左斜（↙）、右斜（↘）
棋盤中1表示有放棋子，0表示沒有放棋子
棋子位置表示方法nm為第n列(row)第m行(column)，例如：06表示第0列第6行

五個棋子連為一線，且不能出現六子或更長的連線情形，例如：
0 0 1 1 1 1 0 1 0 0中，第1個位置放棋子可以構成一條五子連線
若第6個位置放棋子的話則為六子連線，不構成五子連線

【輸入說明】
輸入10*10由1和0組成的棋盤，每格之間以空格隔開

範例輸入：
0 0 1 0 0 0 0 0 0 1
0 0 0 1 0 0 0 1 0 0
1 0 0 0 1 0 0 0 0 0
0 1 0 0 1 0 1 1 1 1
0 0 0 0 1 0 1 0 0 0
0 0 0 1 0 0 0 1 0 0
0 0 1 0 0 0 0 1 0 0
0 1 0 0 0 0 0 1 0 0
0 0 0 0 0 0 0 1 0 0
0 1 1 0 0 1 1 0 1 1

【輸出說明】
輸出可以構成五子連線的棋子位置及可以構成的五子連線數量，中間以空格隔開
且須依照棋子可以構成的五子連線數量由多到少排序，若數量相同，則依照位置數字由小到大輸出

範例輸出：
97 2（在第9列第7行放棋子，可以構成2條五子連線）
35 1（在第3列第5行放棋子，可以構成1條五子連線）
80 1（在第8列第0行放棋子，可以構成1條五子連線）

【測試資料一】
輸入：
0 1 1 1 1 0 0 0 0 1
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 1 0
0 1 1 0 0 0 0 1 0 0
0 0 0 0 0 0 0 0 0 0
1 0 0 0 0 1 0 0 0 1
0 1 0 0 1 0 0 0 0 0
0 0 1 0 0 0 0 0 0 1
0 0 0 0 0 0 0 1 0 1
1 1 0 0 1 0 0 0 0 1

輸出：
00 1
05 1
46 1
69 1
83 1

【測試資料二】
輸入：
0 1 0 0 0 0 1 0 0 0
0 0 0 0 0 1 0 0 0 0
1 0 0 0 0 0 0 0 0 0
0 0 0 1 0 0 0 1 1 1
0 0 1 0 0 0 0 0 0 0
0 1 0 0 1 0 0 0 1 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 1 0 0 0 0 1
1 1 0 0 1 0 0 0 0 0
0 0 0 0 1 0 1 1 1 1

輸出：
64 1

【測試資料三】
輸入：
0 0 1 0 0 0 0 0 1 0
0 1 0 0 0 0 0 0 1 0
0 0 0 0 1 0 0 0 0 0
0 0 0 1 1 0 0 0 1 0
0 1 1 1 0 1 0 0 1 0
1 0 0 0 1 1 0 0 0 0
0 1 0 0 1 0 1 0 0 1
0 0 1 0 0 0 0 1 0 0
0 0 0 1 0 0 0 0 0 0
0 1 1 1 0 1 0 1 1 0

輸出：
44 3
94 2
28 1

【測試資料四】
輸入：
0 0 1 0 0 0 0 0 0 1
0 0 0 1 0 0 0 1 0 0
1 0 0 0 1 0 0 0 0 0
0 1 0 0 1 0 1 1 1 1
0 0 0 0 1 0 1 0 0 0
0 0 0 1 0 0 0 1 0 0
0 0 1 0 0 0 0 1 0 0
0 1 0 0 0 0 0 1 0 0
0 0 0 0 0 0 0 1 0 0
0 1 1 0 0 1 1 0 1 1

輸出：
97 2
35 1
80 1
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int r;
    int c;
    int count;
} ans;

int compare(const void *a, const void *b){
    ans *ansA = (ans *)a;
    ans *ansB = (ans *)b;

    if (ansA->count != ansB->count){
        return ansB->count - ansA->count;
    }

    if (ansA->count == ansB->count){
        return ansA->r - ansB->r;
    }

    return ansA->c - ansB->c;
}

int main(void){
    int board[10][10];
    for (int i=0 ; i<10 ; i++){
        for (int j=0 ; j<10 ; j++){
            scanf("%d", &board[i][j]);
        }
    }

    int dr[4] = {0, 1, 1, 1};
    int dc[4] = {1, 0, 1, -1};

    ans results[100];
    int res_count = 0;

    for (int i=0 ; i<10 ; i++){
        for (int j=0 ; j<10 ; j++){
            if(board[i][j] == 0){
                int total_line = 0;

                for(int d=0 ; d<4 ; d++){
                    int f_count = 0;
                    int b_count = 0;

                    int nr = i+dr[d];
                    int nc = j+dc[d];
                    while(nr >= 0 && nr < 10 && nc >= 0 && nc < 10 && board[nr][nc] == 1){
                        f_count += 1;
                        nr += dr[d];
                        nc += dc[d];
                    }

                    nr = i-dr[d];
                    nc = j-dc[d];
                    while(nr >= 0 && nr < 10 && nc >= 0 && nc < 10 && board[nr][nc] == 1){
                        b_count += 1;
                        nr -= dr[d];
                        nc -= dc[d];
                    }

                    if (1+f_count+b_count == 5){
                        total_line += 1;
                    }
                }

                if (total_line > 0){
                    results[res_count].r = i;
                    results[res_count].c = j;
                    results[res_count].count = total_line;
                    res_count++;
                }
            }
        }
    }

    qsort(results, res_count, sizeof(ans), compare);

    for(int i=0 ; i<res_count ; i++){
        printf("%d%d %d\n", results[i].r, results[i].c, results[i].count);
    }
    return 0;
}