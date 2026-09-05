/*42 Double Link List (雙向鏈結串列)

本題必須使用Double Link List實作，否則不予計分。

Double Link List結構:
typedef struct dnode_s {
int data;
struct dnode_s * front;
struct dnode_s * back;
} node_t;
typedef node_t * nodep_t;

8種Double Link List操作：
除了remove n 以外，執行其餘任一操作(含 empty )時，如果串列是空的則輸出"Double link list is empty"。
addFront：將資料放入串列前端，不進行輸出。
addBack：將資料放入串列尾端，不進行輸出。
removeFront：將最前端的節點刪除，不進行輸出。
removeBack : 將最尾端端的節點刪除，不進行輸出。
empty：將串列中所有節點刪除，不進行輸出。
insert n : 在第n個節點後插入新的資料，最前端節點為1，不進行輸出。假如串列長度小於n則輸出"Invalid command"，其餘情況不進行輸出。
remove n : 刪除第n個節點，最前端節點為1。假如串列長度小於n則輸出"Invalid command"，其餘情況不進行輸出。
print：將串列中所有節點資料從前端到尾端依序輸出data。

【輸入說明】
第一行，輸入一整數 N ( 1 <= N <= 20 )，代表有N個操作。
第二行~第2+N行，輸入操作的種類
addFront操作:addFront data，addFront為字串，data為整數(0<=data<=100)，中間以空白隔開
addBack操做:addBack data，addBack為字串，data為整數(0<=data<=100)，中間以空白隔開
removeFront操作:removeFront，removeFront為字串
removeBack操作:removeBack，removeBack為字串
empty操作:empty，empty為字串
insert n操作：insert n data，insert為字串，n為整數(1<=n<=20)，data為整數(0<=data<=100)，中間以空白隔開
remove n操作：remove n，remove為字串，n為整數(1<=n<=20)，中間以空白隔開
print操作：print，print為字串

範例輸入說明:
13 (N為13，代表有13個操作)
addFront 13(在串列前端加入13)
addBack 12(在串列尾端加入12)
addFront 10(在串列前端加入10)
insert 2 20(在第2個節點後加入20)
insert 5 100(在第5個節點後加入100)
remove 2(移除第2個節點)
print(由前端到尾端輸出所有節點)
remove 5(移除第5個節點)
removeBack(刪除最尾端的節點)
removeFront(刪除最前端的節點)
print(由前端到尾端輸出所有節點)
empty(刪除串列所有節點)
empty(刪除串列所有節點)


【輸出說明】
第一行~第N行，根據操作輸出對應的data

範例輸出說明:
Invalid command(根據輸入的操作1、2、3、4，串列長度為4，由於5超過串列長度，故指令失效)
10(根據輸入的操作6，串列長度為3，第一個節點的data為10)
20(根據輸入的操作6，串列長度為3，第二個節點的data為20)
12(根據輸入的操作6，串列長度為3，第三個節點的data為12)
Invalid command(目前串列長度為3，由於5超過串列長度，故指令失效)
20(根據輸入操作9、10，串列長度為1，第一個節點的data為20)
Double link list is empty (在操作12時，已將Stack中所有節點刪除，故為空)

【測試資料一】
輸入：
8
print
removeFront
removeBack
empty
insert 1 50
addFront 10
print
remove 1

輸出：
Double link list is empty
Double link list is empty
Double link list is empty
Double link list is empty
Invalid command
10

【測試資料二】
輸入：
10
addBack 66
addFront 55
print
removeBack
print
addBack 77
addBack 88
print
empty
print

輸出：
55
66
55
55
77
88
Double link list is empty

【測試資料三】
輸入：
11
addFront 12
insert 1 23
insert 2 34
print
insert 5 99
removeFront
print
insert 2 45
print
removeBack
print

輸出：
12
23
34
Invalid command
23
34
23
34
45
23
34

【測試資料四】
輸入：
11
addFront 90
addFront 80
addFront 70
print
remove 2
print
insert 2 60
print
remove 1
print
remove 3

輸出：
70
80
90
70
90
70
90
60
90
60
Invalid command

【測試資料五】
輸入：
16
addFront 15
addBack 25
insert 1 20
print
remove 2
print
insert 4 99
empty
print
addFront 35
insert 1 45
remove 1
print
removeBack
print
removeFront

輸出：
15
20
25
15
25
Invalid command
Double link list is empty
45
Double link list is empty
Double link list is empty
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 題目要求的 Double Link List 結構
typedef struct dnode_s {
    int data;
    struct dnode_s * front; // 指向前方節點 (prev)
    struct dnode_s * back;  // 指向後方節點 (next)
} node_t;
typedef node_t * nodep_t;

// 全域變數維護串列狀態
nodep_t head = NULL;
nodep_t tail = NULL;
int length = 0;

// 1. addFront：將資料放入串列前端
void addFront(int data) {
    nodep_t new_node = (nodep_t)malloc(sizeof(node_t));
    new_node->data = data;
    new_node->front = NULL;
    new_node->back = head;
    
    if (head == NULL) {
        tail = new_node;
    } else {
        head->front = new_node;
    }
    head = new_node;
    length++;
}

// 2. addBack：將資料放入串列尾端
void addBack(int data) {
    nodep_t new_node = (nodep_t)malloc(sizeof(node_t));
    new_node->data = data;
    new_node->back = NULL;
    new_node->front = tail;
    
    if (tail == NULL) {
        head = new_node;
    } else {
        tail->back = new_node;
    }
    tail = new_node;
    length++;
}

// 3. removeFront：將最前端的節點刪除
void removeFront() {
    if (length == 0) {
        printf("Double link list is empty\n");
        return;
    }
    nodep_t temp = head;
    head = head->back;
    if (head == NULL) {
        tail = NULL;
    } else {
        head->front = NULL;
    }
    free(temp);
    length--;
}

// 4. removeBack：將最尾端端的節點刪除
void removeBack() {
    if (length == 0) {
        printf("Double link list is empty\n");
        return;
    }
    nodep_t temp = tail;
    tail = tail->front;
    if (tail == NULL) {
        head = NULL;
    } else {
        tail->back = NULL;
    }
    free(temp);
    length--;
}

// 5. empty：將串列中所有節點刪除
void empty() {
    if (length == 0) {
        printf("Double link list is empty\n");
        return;
    }
    nodep_t curr = head;
    while (curr != NULL) {
        nodep_t next_node = curr->back;
        free(curr);
        curr = next_node;
    }
    head = NULL;
    tail = NULL;
    length = 0;
}

// 6. insert n：在第 n 個節點後插入新的資料
void insert_n(int n, int data) {
    if (length < n) {
        printf("Invalid command\n");
        return;
    }
    
    // 尋找第 n 個節點
    nodep_t curr = head;
    for (int i = 1; i < n; i++) {
        curr = curr->back;
    }
    
    // 建立新節點並插入其後
    nodep_t new_node = (nodep_t)malloc(sizeof(node_t));
    new_node->data = data;
    new_node->front = curr;
    new_node->back = curr->back;
    
    if (curr->back == NULL) {
        tail = new_node;
    } else {
        curr->back->front = new_node;
    }
    curr->back = new_node;
    length++;
}

// 7. remove n：刪除第 n 個節點
void remove_n(int n) {
    if (length < n) {
        printf("Invalid command\n");
        return;
    }
    
    // 尋找第 n 個節點
    nodep_t curr = head;
    for (int i = 1; i < n; i++) {
        curr = curr->back;
    }
    
    // 調整前後節點的指標
    if (curr->front == NULL) {
        head = curr->back;
    } else {
        curr->front->back = curr->back;
    }
    
    if (curr->back == NULL) {
        tail = curr->front;
    } else {
        curr->back->front = curr->front;
    }
    
    free(curr);
    length--;
}

// 8. print：從前端到尾端依序輸出所有節點的 data
void print_list() {
    if (length == 0) {
        printf("Double link list is empty\n");
        return;
    }
    nodep_t curr = head;
    while (curr != NULL) {
        printf("%d\n", curr->data);
        curr = curr->back;
    }
}

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;
    
    char cmd[30];
    int n, data;
    
    for (int i = 0; i < N; i++) {
        scanf("%s", cmd);
        
        if (strcmp(cmd, "addFront") == 0) {
            scanf("%d", &data);
            addFront(data);
        } 
        else if (strcmp(cmd, "addBack") == 0) {
            scanf("%d", &data);
            addBack(data);
        } 
        else if (strcmp(cmd, "removeFront") == 0) {
            removeFront();
        } 
        else if (strcmp(cmd, "removeBack") == 0) {
            removeBack();
        } 
        else if (strcmp(cmd, "empty") == 0) {
            empty();
        } 
        else if (strcmp(cmd, "insert") == 0) {
            scanf("%d %d", &n, &data);
            insert_n(n, data);
        } 
        else if (strcmp(cmd, "remove") == 0) {
            scanf("%d", &n);
            remove_n(n);
        } 
        else if (strcmp(cmd, "print") == 0) {
            print_list();
        }
    }
    
    // 程式結束前釋放剩餘記憶體
    nodep_t curr = head;
    while (curr != NULL) {
        nodep_t next_node = curr->back;
        free(curr);
        curr = next_node;
    }
    
    return 0;
}