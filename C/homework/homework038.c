/*038 Stack
本題必須使用Link List實作，否則不予計分。
請使用 Linked List 實作 Stack（堆疊），並模擬以下操作。
Stack 為後進先出（LIFO, Last In First Out）

兩種Stack基本操作：
push：將數據放入堆疊的頂端(串列形式)，堆疊頂端top指標加一。
pop：將頂端數據資料輸出(回傳)，堆疊頂端top指標減一。

每一筆資料都包含姓名、年齡、生日(年、月、日)。

【輸入說明】
每一行都先輸入一個整數：
輸入 1 代表 push，後續依照姓名、年齡、生日(年、月、日)的順序輸入，參數間以空白間隔。
輸入 2 代表 pop，後續再輸入一個整數，進行不同操作，操作數字對應如下：
1：印出該次 pop 的資料中的姓名。
2：印出該次 pop 的資料中的年齡。
3：印出該次 pop 的資料中的生日(年、月、日之間以底線連結)。
任一操作如果 stack 中為空則印出“The Stack is empty”。
輸入3代表結束程式。

範例說明:
Sample Input:
1 "Marry Hu" 19 1989 7 16 (push 名為Marry Hu、年齡為19、生日為1989_7_16 的資料)
1 "Tom Chen" 22 1996 10 19 (push 名為Tom Chen、年齡為22、生日為1996_10_19 的資料)
2 1 (印出 pop 資料的姓名)
1 "Billy Wu" 15 2005 3 18 (push 名為Billy Wu、年齡為15、生日為2005_3_18 的資料)
2 3 (印出 pop 資料的生日)
2 2 (印出 pop 資料的年齡)
1 "Lucas Su" 24 1993 5 21 (push 名為Lucas Su、年齡為24、生日為1993_5_21 的資料)
2 3 (印出 pop 資料的生日)
2 1 (印出 pop 資料的姓名)
3 (結束程式)

【輸出說明】
有 pop 操作才需要根據相對應的操作輸出，輸入3則結束程式。

Sample Output:
Tom Chen (對應輸入的第3行，pop 出頂端 Tom Chen 的姓名)
2005_3_18 (對應輸入的第5行，pop 出頂端 Billy Wu 的生日)
19 (對應輸入的第6行，pop 出頂端 Marry Hu 的年齡)
1993_5_21 (對應輸入的第8行，pop 出頂端 Lucas Su 的生日)
The Stack is empty (此時 Stack 已為空，輸入第9行印出 “The Stack is empty”)


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
25
Charlie Koh
2006_1_12

【測試資料二】
輸入：
2 1
1 "Conan Ku" 30 1996 5 4
2 1
2 2
1 "Nick Kuo" 36 1990 5 9
3

輸出：
The Stack is empty
Conan Ku
The Stack is empty

【測試資料三】
輸入：
1 "James Harrison" 10 2016 1 1
1 "Emily Watson" 20 2006 2 2
1 "Daniel Craig" 30 1996 3 3
2 1
1 "Sophia Martinez" 40 1886 4 4
2 2
2 3
2 1
2 3
3

輸出：
Daniel Craig
40
2006_2_2
James Harrison
The Stack is empty

【測試資料四】
輸入：
1 "Tom" 37 1989 7 16
1 "Mary Hu" 22 2004 10 19
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
Mary Hu
1993_5_21
20
John
1989_7_16
The Stack is empty
The Stack is empty
25
The Stack is empty
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[100];
    int age;
    int birth_year;
    int birth_month;
    int birth_day;
    struct Node* next;
} Node;

Node* top = NULL;

void push(char* name, int age, int y, int m, int d) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->age = age;
    newNode->birth_year = y;
    newNode->birth_month = m;
    newNode->birth_day = d;
    
    newNode->next = top;
    top = newNode;
}

void pop(int sub_op) {
    if (top == NULL) {
        printf("The Stack is empty\n");
        fflush(stdout);
        return;
    }
    
    Node* temp = top;
    if (sub_op == 1) {
        printf("%s\n", temp->name);
    } else if (sub_op == 2) {
        printf("%d\n", temp->age);
    } else if (sub_op == 3) {
        printf("%d_%d_%d\n", temp->birth_year, temp->birth_month, temp->birth_day);
    }
    fflush(stdout); // 確保每次 pop 都立刻逼作業系統印出來
    
    top = top->next;
    free(temp);
}

void freeStack() {
    while (top != NULL) {
        Node* temp = top;
        top = top->next;
        free(temp);
    }
}

int main() {
    char line[2048];
    
    while (fgets(line, sizeof(line), stdin)) {
        char *ptr = line;
        
        // 1. 跳過前導空白
        while (*ptr == ' ' || *ptr == '\t') ptr++;
        if (*ptr == '\0' || *ptr == '\n' || *ptr == '\r') continue;
        
        // 2. 讀取主要操作碼
        int op = 0;
        if (sscanf(ptr, "%d", &op) != 1) continue;
        while (*ptr >= '0' && *ptr <= '9') ptr++; // 指標移過數字
        
        if (op == 3) {
            break;
        } 
        else if (op == 1) {
            // 3. 處理 Push
            while (*ptr == ' ' || *ptr == '\t') ptr++;
            
            char name[100] = {0};
            int i = 0;
            
            if (*ptr == '"') { // 如果有雙引號包裹
                ptr++; // 跳過開頭引號
                while (*ptr != '"' && *ptr != '\0' && *ptr != '\n' && *ptr != '\r') {
                    name[i++] = *ptr++;
                }
                if (*ptr == '"') ptr++; // 跳過結尾引號
            } else { // 如果沒有雙引號
                while (*ptr != ' ' && *ptr != '\t' && *ptr != '\0' && *ptr != '\n' && *ptr != '\r') {
                    name[i++] = *ptr++;
                }
            }
            name[i] = '\0';
            
            // 4. 用指標安全地抓取後面的 4 個整數 (年齡、年、月、日)
            int age = 0, y = 0, m = 0, d = 0;
            
            // 找 age
            while (*ptr == ' ' || *ptr == '\t') ptr++;
            if (sscanf(ptr, "%d", &age) != 1) continue;
            while (*ptr >= '0' && *ptr <= '9') ptr++;
            
            // 找 year
            while (*ptr == ' ' || *ptr == '\t') ptr++;
            if (sscanf(ptr, "%d", &y) != 1) continue;
            while (*ptr >= '0' && *ptr <= '9') ptr++;
            
            // 找 month
            while (*ptr == ' ' || *ptr == '\t') ptr++;
            if (sscanf(ptr, "%d", &m) != 1) continue;
            while (*ptr >= '0' && *ptr <= '9') ptr++;
            
            // 找 day
            while (*ptr == ' ' || *ptr == '\t') ptr++;
            if (sscanf(ptr, "%d", &d) != 1) continue;
            
            // 成功解析完所有欄位，安全推進 Stack
            push(name, age, y, m, d);
        } 
        else if (op == 2) {
            // 5. 處理 Pop
            while (*ptr == ' ' || *ptr == '\t') ptr++;
            int sub_op = 0;
            if (sscanf(ptr, "%d", &sub_op) == 1) {
                pop(sub_op);
            }
        }
    }
    
    freeStack();
    return 0;
}