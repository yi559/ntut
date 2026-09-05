/*Final_Exam2
城市旅遊

假設一個國家內有多個城市，城市之間會透過N條道路相互連通。根據輸入的兩個城市：起始城市X和目的城市Z。你需要找出從X到Z的一條最短路徑。此外，題目可能還會指定一個必經城市Y，如果有給定城市Y，則從X到Z的路徑必須經過Y，並找出X到Y再到Z的最短路徑。如果沒有給定必經城市Y，則找出從X到Z的最短路徑就好。

不考慮同時有多條最短路徑

【輸入說明】
第一行：輸入N, X, Z, Y，N 代表道路數量(3<=N<=15)，X 代表起始點城市，Z 代表終點城市，Y 代表必經城市，若沒有 Y，則不考慮中途點，中間以空白隔開。
第二行~N+1行：每一行輸入格式為 A B，代表 A 城市與 B 城市間有道路相連接，中間以空白隔開。

範例輸入說明:
3 1 3 (國家內有 3 條道路，要從起始點城市 1 到達終點城市 3，沒有必須經過的城市)
1 5 (城市 1 和城市 5 之間有一條道路)
7 5 (城市 7 和城市 5 之間有一條道路)
7 3 (城市 7 和城市 3 之間有一條道路)

【輸出說明】
若存在，則第一行輸出經過最少道路個數，第二行輸出最短路徑。
若不存在此路徑，輸出 NO。

範例輸出說明:
3 (總共經過3個道路)
1 5 7 3 (城市 1 到城市 3 能找到的最短路徑為 1 -> 5 -> 7 -> 3)

【測試資料一】
輸入:
6 1 3
1 5
7 5
4 5
3 5
2 3
4 3

輸出:
2
1 5 3

【測試資料二】
輸入:
6 1 4 3
1 2
1 3
2 4
2 5
3 5
5 4

輸出:
3
1 3 5 4

【測試資料三】
輸入:
15 1 15
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11
11 12
12 13
13 14
7 15
14 15

輸出:
7
1 2 3 4 5 6 7 15

【測試資料四】
輸入:
13 1 10 4
1 4
1 5
2 4
3 5
3 4
3 2
4 3
5 2
6 3
7 10
8 7
9 7
10 8

輸出:
NO

【測試資料五】
輸入:
7 1 10
1 4
1 5
2 4
3 5
6 3
7 10
10 8

輸出:
NO
*/

#include <stdio.h>

int adj[100][100] = {0};
int max_node = 0;

int bfs(int start, int end, int path[]){
    if (start == end){
        path[0] = start;
        return 1;
    }

    int visited[100] = {0};
    int parent[100] = {0};
    int queue[100];
    int head = 0, tail = 0;

    queue[tail++] = start;
    visited[start] = 1;
    parent[start] = -1;

    int found = 0;

    while(head < tail){
        int curr = queue[head++];

        if (curr == end){
            found = 1;
            break;
        }

        for (int next=1 ; next<=max_node ; next++){
            if (adj[curr][next] == 1 && visited[next] == 0){
                visited[next] = 1;
                parent[next] = curr;
                queue[tail++] = next;
            }
        }
    }

    if (found == 0) return 0;

    int temp_path[100];
    int len = 0;
    int curr = end;
    while(curr != -1){
        temp_path[len++] = curr;
        curr = parent[curr];
    }

    for (int i=0 ; i<len ; i++){
        path[i] = temp_path[len-1-i];
    }
    return len;
}

int main(void){
    char first_line[100];

    if (fgets(first_line, sizeof(first_line), stdin) == NULL){
        return 0;
    }

    int N, X, Z, Y = -1;

    int num_inputs = sscanf(first_line, "%d %d %d %d", &N, &X, &Z, &Y);

    for (int i=0 ; i<N ; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1;

        if (u > max_node) max_node = u;
        if (v > max_node) max_node = v;
    }

    int final_path[200];
    int final_len = 0;

    if (num_inputs == 3 || Y == -1){
        final_len = bfs(X, Z, final_path);
    }else{
        int path1[100], path2[100];
        int len1 = bfs(X, Y, path1);
        int len2 = bfs(Y, Z, path2);

        if (len1 > 0 && len2 > 0){
            for (int i=0 ; i<len1 ; i++){
                final_path[final_len++] = path1[i];
            }

            for (int i=1 ; i<len2 ; i++){
                final_path[final_len++] = path2[i];
            }
        }else{
            final_len = 0;
        }
    }

    if (final_len == 0){
        printf("NO\n");
    }else{
        printf("%d\n", final_len-1);

        for(int i=0 ; i<final_len ; i++){
            printf("%d", final_path[i]);
            if (i < final_len - 1) {
                printf(" ");
            } else {
                printf("\n");
            }
        }
    }

    return 0;
}