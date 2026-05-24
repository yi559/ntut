/*033. 專案時程
本題必須使用 struct 架構實作，否則將不予計分。

開發專案時，
專案會被分割為許多項目，分配給多組程式設計師開發。
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
2
8 1 2
2 0
5
6 2 2 3
5 1 4
11 1 5
4 1 5
8 0

輸出 :
10
25


【測試資料二】
輸入 :
1
11
1 2 2 4
2 1 3
3 2 4 5
4 1 5
5 1 6
6 3 7 8 9
7 2 8 10
8 2 9 10
9 1 11
10 1 11
11 0

輸出 :
57

【測試資料三】
輸入 :
1
9
1 1 2
6 2 3 4
5 2 4 5
11 1 6
4 1 6
8 2 7 9
9 1 8
1 1 9
10 0

輸出 :
51


【測試資料四】
輸入 :
1
8
3 2 2 8
4 2 3 8
5 2 4 8
6 2 5 8
7 2 6 8
8 2 7 8
9 1 8
20 0

輸出 :
62


【測試資料五】
輸入 :
1
20
1 0
3 0
5 0
7 0
9 0
11 0
13 0
15 0
17 0
19 0
21 0
23 0
25 0
27 0
29 0
31 0
33 0
35 0
37 0
39 0

輸出 :
39
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 105

typedef struct {
    int days;
    int k;
    int next[MAX_NODES];
    int indegree;
    int earliest_end;
} JobNode;

void solve() {
    int M;
    if (scanf("%d", &M) != 1) return;

    JobNode nodes[MAX_NODES];
    
    for (int i = 1; i <= M; i++) {
        nodes[i].indegree = 0;
        nodes[i].earliest_end = 0;
    }

    for (int i = 1; i <= M; i++) {
        scanf("%d %d", &nodes[i].days, &nodes[i].k);
        for (int j = 0; j < nodes[i].k; j++) {
            scanf("%d", &nodes[i].next[j]);
        }
    }

    for (int i = 1; i <= M; i++) {
        for (int j = 0; j < nodes[i].k; j++) {
            int target = nodes[i].next[j];
            nodes[target].indegree++;
        }
    }

    int queue[MAX_NODES];
    int head = 0, tail = 0;

    for (int i = 1; i <= M; i++) {
        if (nodes[i].indegree == 0) {
            queue[tail++] = i;
            nodes[i].earliest_end = nodes[i].days;
        }
    }

    while (head < tail) {
        int u = queue[head++];
        
        for (int i = 0; i < nodes[u].k; i++) {
            int v = nodes[u].next[i];
            
            int candidate_end = nodes[u].earliest_end + nodes[v].days;
            if (candidate_end > nodes[v].earliest_end) {
                nodes[v].earliest_end = candidate_end;
            }
            
            nodes[v].indegree--;
            if (nodes[v].indegree == 0) {
                queue[tail++] = v;
            }
        }
    }

    int project_duration = 0;
    for (int i = 1; i <= M; i++) {
        if (nodes[i].earliest_end > project_duration) {
            project_duration = nodes[i].earliest_end;
        }
    }

    printf("%d\n", project_duration);
}

int main() {
    int N;
    if (scanf("%d", &N) == 1) {
        while (N--) {
            solve();
        }
    }
    return 0;
}