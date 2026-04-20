/*迷宮

給定一張二維平面圖，起點為整張圖中權重最小的點。
在此平面圖上從起點開始走出一條路徑，求此路徑經過點的總權重。
往下一個點移動時，必須遵循以下規則：
只能從「上、下、左、右」四個相鄰的點中選擇。
已經走過的點不能重複走。
移動條件切換（重點）：
當進行第奇數次移動（第 1, 3, 5... 步）時，必須從相鄰未走過的點中，選擇權重最小的點走。
當進行第偶數次移動（第 2, 4, 6... 步）時，必須從相鄰未走過的點中，選擇權重最大的點走。
若周圍已經沒有未走過的相鄰點，則結束移動。
假設測資中，每次要選擇的最小或最大權重點皆為唯一，不會有權重相同需要額外判斷順序的情況。
剛開始找整張圖中權重最小的點當作起點，不算第一步。
【輸入格式】
第一行包含兩個正整數 R 與 C，分別代表矩陣的列數 (Row) 與欄數 (Column)，10>=R/C>=2。
接下來有 R 行，每行有 C 個由空白隔開的正整數，代表該座標點的權重。
【輸出格式】
請輸出一個整數，代表這條路徑所經過的所有點的總權重。
【輸入範例】
3 4 (3*4的二維陣列)
10 25 8 12
15 2 30 5
20 18 22 9
【輸出範例】
146 (從2開始走，起點不算是第一步，所以要找相鄰沒走過的最小值，2->15->20->18->22->9->5->12->8->25->10，2+15+20+18+22+9+5+12+8+25+10=146)

【測試資料一】
輸入:
2 2
10 20
40 30
輸出:
100
【測試資料二】
輸入:
3 3
1 9 8
2 10 7
3 4 5
輸出:
46
【測試資料三】
輸入:
2 5
5 1 10 2 15
8 9 12 7 11
輸出:
80
【測試資料四】
輸入:
4 3
1 10 2
20 100 21
3 30 4
40 200 41
輸出:
404
*/

#include <stdio.h>

int find_next(int r_size, int c_size, int data[10][10], int mark[10][10], int *cur_i, int *cur_j, int step) {
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    int target_i = -1, target_j = -1;
    int best_val;

    if (step % 2 == 1) best_val = 1e9;
    else best_val = -1e9;

    for (int k = 0; k < 4; k++) {
        int ni = *cur_i + dr[k];
        int nj = *cur_j + dc[k];

        if (ni >= 0 && ni < r_size && nj >= 0 && nj < c_size && mark[ni][nj] == 0) {
            if (step % 2 == 1) {
                if (data[ni][nj] < best_val) {
                    best_val = data[ni][nj];
                    target_i = ni; target_j = nj;
                }
            } else {
                if (data[ni][nj] > best_val) {
                    best_val = data[ni][nj];
                    target_i = ni; target_j = nj;
                }
            }
        }
    }

    if (target_i == -1) return -1; 

    *cur_i = target_i;
    *cur_j = target_j;
    mark[target_i][target_j] = 1;
    return best_val;
}

int main(void){
    int r=0,c=0;

    scanf("%d %d", &r,&c);

    int data[10][10], mark[10][10];
    for (int i=0 ; i<r ; i++){
        for (int j=0 ; j<c ; j++){
            scanf("%d", &data[i][j]);
            mark[i][j] = 0;
        }
    }

    int min_index_i=0,min_index_j=0;

    for (int i=0 ; i<r ; i++){
        for (int j=0 ; j<c ; j++){
            if (data[i][j] < data[min_index_i][min_index_j]){
                min_index_i = i;
                min_index_j = j;
            }
        }
    }

    int total = data[min_index_i][min_index_j];
    mark[min_index_i][min_index_j] = 1;

    int step = 1;
    while (1) {
        int next_weight = find_next(r, c, data, mark, &min_index_i, &min_index_j, step);
        
        if (next_weight == -1) break;

        total += next_weight;
        step++;
    }

    printf("%d\n", total);
    return 0;
}