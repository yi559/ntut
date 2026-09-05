/*40. 專案時程
本題必須使用 struct 架構實作，否則將不予計分。

開發專案時，專案會被分割為許多項目，分配給多組程式設計師開發。
這些項目有順序關係，且只有當順序在前的項目完成，才能開始開發順序在後的項目。

本題使用一個有向無環圖，表示這些項目的開發順序。
每個節點代表一個項目，節點內的數字為節點編號，
上方所列數字代表開發這個項目所需天數；
邊表示開發順序。

以下方圖示為例，只有在節點2完成後，才能開始節點4的開發。
同理，只有在節點3與節點4都完成後，才能開始節點5的開發。



請根據開發流程圖，計算該專案要多少天才能完成。


【輸入說明】
第一行為整數 N，代表有 N 組專案 ( 1 <= N <= 3 )。
第二行為整數 M，代表該專案共有 M 個工作事項 (節點) ( 2 <= M <= 100 )。
接下來 M 行，每一行依序代表一個項目節點 (從第1個節點開始)，
第一個整數表示完成這個項目節點所需的天數，
第二個整數 K ，表示這個節點有 K 個節點正在等待該項目完成，
接下來 K 個整數表示該項目所指向的每個項目編號，字元間以空白相隔開。
若 K 為 0 ，則代表沒有項目在等待，不需輸入項目編號。

第 M+1 行後，繼續輸入下一組專案資訊，
輸入方式以此類推，直到第 N 組專案結束。

範例輸入:
2 (有2組專案)
2 (第一個專案有2個工作事項)
8 1 2 (第1個工作事項需要8天完成，有1個工作事項在等待該項目完成，第2工作事項正在等待)
2 0 (第2個工作事項需要2天完成，沒有工作事項在等待該項目完成)
5 (第二個專案有5個工作事項)
6 2 2 3 (第1個工作事項需要6天完成，有2個工作事項在等待該項目完成，第2、3工作事項正在等待)
5 1 4 (第2個工作事項需要5天完成，有1個工作事項在等待該項目完成，第4工作事項正在等待)
11 1 5 (第3個工作事項需要11天完成，有1個工作事項在等待該項目完成，第5工作事項正在等待)
4 1 5 (第4個工作事項需要4天完成，有1個工作事項在等待該項目完成，第5工作事項正在等待)
8 0 (第5個工作事項需要8天完成，沒有工作事項在等待該項目完成)

【輸出說明】
第一行輸出第一組專案開發所需的時間。
第二行輸出第二組專案開發所需的時間。
以此類推，直到 N 行。

範例輸出:
10 (第一組專案需要10天)
25 (第二組專案需要10天)

【測試資料一】
輸入 :
2
4
5 2 2 3
4 1 4
7 1 4
3 0
4
6 2 2 3
8 1 4
5 1 4
4 0

輸出 :
15
18


【測試資料二】
輸入 :
1
5
10 1 3
15 1 4
5 1 5
8 1 5
3 0

輸出 :
26

【測試資料三】
輸入 :
1
6
19 0
11 0
38 0
52 0
7 0
41 0

輸出 :
52


【測試資料四】
輸入 :
1
8
4 1 2
7 1 3
2 1 4
9 1 5
5 1 6
3 1 7
8 1 8
6 0

輸出 :
44


【測試資料五】
輸入 :
2
5
4 2 2 3
7 1 4
9 1 4
11 1 5
3 0
6
5 2 2 3
11 1 4
6 1 5
4 1 6
8 1 6
9 0

輸出 :
27
29
*/

#include <stdio.h>

#define MAX_M 105

// 定義工作事項的結構體
typedef struct {
    int duration;          // 完成此項目所需的天數
    int K;                 // 有 K 個項目正在等待此項目完成
    int dependents[MAX_M]; // 儲存正在等待的項目編號
    int max_path_time;     // 記憶化欄位：以此節點為起點到結束所需的最長總天數
} Task;

// 遞迴計算從 node_idx 開始往後延伸的最長專案時間
int find_max_time(int node_idx, Task tasks[]) {
    // 如果已經計算過，直接回傳紀錄的值（記憶化）
    if (tasks[node_idx].max_path_time != -1) {
        return tasks[node_idx].max_path_time;
    }
    
    // 如果沒有後續等待的項目，該路徑時間就是自身的天數
    if (tasks[node_idx].K == 0) {
        tasks[node_idx].max_path_time = tasks[node_idx].duration;
        return tasks[node_idx].max_path_time;
    }
    
    int max_dep_time = 0;
    // 遍歷所有依賴此項目的後續節點，尋找花費時間最長的路徑
    for (int i = 0; i < tasks[node_idx].K; i++) {
        int next_node = tasks[node_idx].dependents[i];
        int dep_time = find_max_time(next_node, tasks);
        if (dep_time > max_dep_time) {
            max_dep_time = dep_time;
        }
    }
    
    // 目前節點的最長時間 = 自身天數 + 後續最長天數
    tasks[node_idx].max_path_time = tasks[node_idx].duration + max_dep_time;
    return tasks[node_idx].max_path_time;
}

int main() {
    int N; // 專案組數
    if (scanf("%d", &N) != 1) return 0;
    
    while (N--) {
        int M; // 工作事項總數
        if (scanf("%d", &M) != 1) break;
        
        // 宣告 struct 陣列（節點編號從 1 到 M）
        Task tasks[MAX_M];
        
        // 輸入各個節點資訊
        for (int i = 1; i <= M; i++) {
            scanf("%d %d", &tasks[i].duration, &tasks[i].K);
            tasks[i].max_path_time = -1; // 初始化記憶化陣列為 -1
            
            for (int j = 0; j < tasks[i].K; j++) {
                scanf("%d", &tasks[i].dependents[j]);
            }
        }
        
        int total_max_time = 0;
        // 計算所有可能的起始節點出發所能達到的最大時間
        for (int i = 1; i <= M; i++) {
            int current_time = find_max_time(i, tasks);
            if (current_time > total_max_time) {
                total_max_time = current_time;
            }
        }
        
        // 輸出該組專案的答案
        printf("%d\n", total_max_time);
    }
    
    return 0;
}