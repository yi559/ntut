/*029 騎車
小明騎腳踏車挑戰一日N塔,N<10。每一個塔位在編號 1, 2,3, ...,N 城市中。兩兩個城市都有一段距離的公路相連。小明原本已經規劃好從第 1 個城市出發,騎過每一個城市的最短距離,但是在騎到第C個城市時，發現某一段路不能夠走了，於是小明馬上計算走完剩下的程式所需要的最短距離，請問小明完成一日N塔所花的距離是多少

城市之間的路徑
0 2 1 0
2 0 5 2
1 5 0 1
0 2 1 0
以第一行為範例。例如
0 代表城市 1 無法抵達城市 1,
2 代表城市 1 和城市 2 的距離是 2,
1 代表城市 1 和城市 3 的距離是 1,
0 代表城市 1 無法抵達城市 4

【輸入說明】
第一行輸入一個整數N代表有幾座塔(N <= 10)
其後N行代表城市N與其他城市所相鄰的距離
下一行輸入一個整數C代表在騎到第幾個城市發生哪段路無法通行
再下一行輸入兩個整數u, v 代表哪一段路無法通行

範例輸入說明:
4 (代表有4座城市)
0 2 1 0 (第一座城市與其他座城市的距離)
2 0 5 2 (第二座城市與其他座城市的距離)
1 5 0 1 (第三座城市與其他座城市的距離)
0 2 1 0 (第四座城市與其他座城市的距離)
2 (代表走到第幾個城市發生道路無法通行)
3 4 (代表城市3,城市 4之間的路無法通行)

【輸出說明】
第一行輸出小明完成一日N塔的路徑
第二行輸出完成路徑所花的距離

(原本計算的最短路徑為1 3 4 2,因走到第2個城市發現3 4路徑無法通行,所以保留走過的1 3路徑往後找沒有3 4路徑的又可以走完所有城市的路徑)

範例輸出說明:
1 3 2 4 (最終完成一日N塔的路徑)
8 (花費的距離 : 1+5+2 = 8)

【測試資料一】
輸入:
5
0 3 1 4 2
3 0 6 10 0
1 6 0 6 10
4 10 6 0 4
2 0 10 4 0
3
4 3

輸出:
1 5 4 2 3
22

【測試資料二】
輸入:
6
0 1 5 1 9 0
1 0 4 7 0 3
5 4 0 9 4 8
1 7 9 0 0 9
9 0 4 0 0 10
0 3 8 9 10 0
3
6 2

輸出:
1 4 6 5 3 2
28

【測試資料三】
輸入:
8
0 3 0 6 0 0 2 0
3 0 1 0 3 4 0 0
0 1 0 5 0 0 3 8
6 0 5 0 2 0 0 4
0 3 0 2 0 6 0 1
0 4 0 0 6 0 2 0
2 0 3 0 0 2 0 5
0 0 8 4 1 0 5 0
4
2 3

輸出:
1 7 6 2 5 8 4 3
21
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 1e9

int N, C, blocked_u, blocked_v;
int graph[11][11];

int current_path[11];
int best_path[11];
int min_distance;

void dfs(int step, int current_city, int current_dist, bool visited[]) {
    if (step == N + 1) {
        if (current_dist < min_distance) {
            min_distance = current_dist;
            for (int i = 1; i <= N; i++) {
                best_path[i] = current_path[i];
            }
        }
        return;
    }

    if (current_dist >= min_distance) return;

    for (int next_city = 1; next_city <= N; next_city++) {
        if (!visited[next_city] && graph[current_city][next_city] > 0) {
            visited[next_city] = true;
            current_path[step] = next_city;
            
            dfs(step + 1, next_city, current_dist + graph[current_city][next_city], visited);
            
            visited[next_city] = false;
        }
    }
}

int main(void) {
    if (scanf("%d", &N) != 1) return 0;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    scanf("%d", &C);
    scanf("%d %d", &blocked_u, &blocked_v);

    bool visited[11] = {false};
    min_distance = INF;
    
    visited[1] = true;
    current_path[1] = 1;
    dfs(2, 1, 0, visited);

    int fixed_path[11];
    bool fixed_visited[11] = {false};
    int fixed_dist = 0;

    for (int i = 1; i <= C; i++) {
        fixed_path[i] = best_path[i];
        fixed_visited[best_path[i]] = true;
        if (i > 1) {
            fixed_dist += graph[best_path[i-1]][best_path[i]];
        }
    }

    graph[blocked_u][blocked_v] = 0;
    graph[blocked_v][blocked_u] = 0;

    min_distance = INF;
    for (int i = 1; i <= C; i++) {
        current_path[i] = fixed_path[i];
    }

    dfs(C + 1, fixed_path[C], fixed_dist, fixed_visited);

    for (int i = 1; i <= N; i++) {
        printf("%d%c", best_path[i], (i == N) ? '\n' : ' ');
    }
    printf("%d\n", min_distance);

    return 0;
}