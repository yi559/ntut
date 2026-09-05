/*
039 Queue
本題必須使用Link List實作，否則不予計分。
請使用 Linked List 實作 Queue（佇列），並模擬以下操作。
Queue 為先進先出（FIFO, First In First Out）

兩種Queue基本操作：
push：將資料放入佇列的尾端（串列形式），尾端tail指標加一。
pop：將佇列前端資料輸出，並刪除前端節點，前端front指標加一。

每一筆資料都包含姓名、年齡、生日(年、月、日)。

【輸入說明】
每一行都先輸入一個整數：
輸入 1 代表 push，後續依照姓名、年齡、生日(年、月、日)的順序輸入，參數間以空白間隔。
輸入 2 代表 pop，後續再輸入一個整數，進行不同操作，操作數字對應如下：
1：印出該次 pop 的資料中的姓名。
2：印出該次 pop 的資料中的年齡。
3：印出該次 pop 的資料中的生日(年、月、日之間以底線連結)。
任一操作如果 queue 中為空則印出“The Queue is empty”。
輸入3代表結束程式。

範例說明:
Sample Input:
1 "Marry Hu" 19 1989 7 16 (push 名為 Marry Hu、年齡為19、生日為1989_7_16 的資料至尾端)
1 "Tom Chen" 22 1996 10 19 (push 名為 Tom Chen、年齡為22、生日為1996_10_19 的資料至尾端)
2 1 (印出 pop 資料的姓名)
1 "Billy Wu" 15 2005 3 18 (push 名為 Billy Wu、年齡為15、生日為2005_3_18 的資料至尾端)
2 3 (印出 pop 資料的生日)
2 2 (印出 pop 資料的年齡)
1 "Lucas Su" 24 1993 5 21 (push 名為 Lucas Su、年齡為24、生日為1993_5_21 的資料至尾端)
2 3 (印出 pop 資料的生日)
2 1 (印出 pop 資料的姓名)
3 (結束程式)

【輸出說明】
有 pop 操作才需要根據相對應的操作輸出，輸入3則結束程式。

Sample Output:
Marry Hu (最早進去的是 Marry Hu，輸入第3行 pop 印出其姓名)
Tom Chen (接著最早的是 Tom Chen，輸入第5行 pop 印出其生日)
15 (再過來最早的是 Billy Wu，輸入第6行 pop 印出其年齡)
1993_5_21 (此時剩下 Lucas Su，輸入第8行 pop 印出其生日)
The Queue is empty (此時 Queue 已為空，輸入第9行印出 “The Queue is empty”)

【測試資料一】
輸入：
1 "Alice Wang" 20 2006 1 12
1 "Bob Lin" 25 2001 11 30
2 2
1 "Charlie Koh" 18 2008 8 8
2 1
2 3
3

輸出：
20
Bob Lin
2008_8_8

【測試資料二】
輸入：
2 1
1 "Conan Ku" 30 1996 5 4
2 1
2 2
1 "Nick Kuo" 36 1990 5 9
3

輸出：
Queue is empty
Conan Ku
Queue is empty

【測試資料三】
輸入：
1 "James Harrison" 10 2016 1 1
1 "Emily Watson" 20 2006 2 2
1 "Daniel Craig" 30 1996 3 3
2 1
1 "Sophia Martinez" 40 1986 4 4
2 2
2 3
2 1
2 3
3

輸出：
James Harrison
20
1996_3_3
Sophia Martinez
Queue is empty

【測試資料四】
輸入：
1 "Tom" 19 2007 7 16
1 "Mary Hu" 30 1996 10 19
2 1
1 "John" 15 2011 3 18
1 "David" 33 1993 5 21
2 3
1 "Amy Lin" 20 2006 1 12
2 2
2 1
2 3
2 1
2 1
1 "Bob" 25 2001 11 30
2 2
2 1
3

輸出：
Tom
1996_10_19
15
David
2006_1_12
The Queue is empty
The Queue is empty
25
The Queue is empty
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定義資料節點結構
typedef struct Node {
    char name[100];
    int age;
    int year;
    int month;
    int day;
    struct Node* next; // 指向下一個節點
} Node;

// 定義佇列結構
typedef struct {
    Node* front; // 指向佇列前端 (負責 pop)
    Node* tail;  // 指向佇列尾端 (負責 push)
} Queue;

// 初始化佇列
void initQueue(Queue* q) {
    q->front = NULL;
    q->tail = NULL;
}

// Push 函式：將資料放入佇列尾端
void push(Queue* q, const char* name, int age, int year, int month, int day) {
    // 建立新節點並配置記憶體
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->age = age;
    newNode->year = year;
    newNode->month = month;
    newNode->day = day;
    newNode->next = NULL;

    // 如果佇列是空的，front 和 tail 都會指向新節點
    if (q->tail == NULL) {
        q->front = newNode;
        q->tail = newNode;
    } else {
        // 原本的 tail 指向新節點，並將 tail 更新為新節點
        q->tail->next = newNode;
        q->tail = newNode;
    }
}

// Pop 函式：輸出前端資料並刪除節點
void pop(Queue* q, int op) {
    // 檢查佇列是否為空
    if (q->front == NULL) {
        // 注意：題目規定印出 "The Queue is empty"，但部分測資(如測資2、3)範例為 "Queue is empty"。
        // 這裡我們依題目最一開始的說明與測資4為準，印出 "The Queue is empty"。
        // 若上機評測系統報錯，請視情況將前方的 "The " 刪除。
        printf("The Queue is empty\n");
        return;
    }

    // 取得前端節點的資料
    Node* temp = q->front;
    
    // 根據對應的操作指令印出資料
    if (op == 1) {
        printf("%s\n", temp->name);
    } else if (op == 2) {
        printf("%d\n", temp->age);
    } else if (op == 3) {
        printf("%d_%d_%d\n", temp->year, temp->month, temp->day);
    }

    // 將 front 指標往後移動一個節點
    q->front = q->front->next;
    
    // 如果移除節點後佇列空了，必須連同 tail 一起設為 NULL
    if (q->front == NULL) {
        q->tail = NULL;
    }
    
    // 釋放記憶體避免 Memory Leak
    free(temp);
}

int main() {
    Queue q;
    initQueue(&q);

    int cmd;
    // 讀取指令直到 EOF 或遇到指令 3
    while (scanf("%d", &cmd) != EOF) {
        if (cmd == 3) {
            break; // 結束程式
        } else if (cmd == 1) {
            char name[100];
            int age, year, month, day;
            // 讀取雙引號內的字串與後續數字
            // " \"%[^\"]\"" 會自動略過空白並匹配雙引號，捕捉括號內的所有字元直到下一個雙引號
            scanf(" \"%[^\"]\" %d %d %d %d", name, &age, &year, &month, &day);
            push(&q, name, age, year, month, day);
        } else if (cmd == 2) {
            int op;
            scanf("%d", &op);
            pop(&q, op);
        }
    }

    // 程式結束前釋放佇列殘餘的記憶體 (良好寫作習慣)
    while (q.front != NULL) {
        Node* temp = q.front;
        q.front = q.front->next;
        free(temp);
    }

    return 0;
}