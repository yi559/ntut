/*037 多項式相加
本題必須使用Link List實作，否則不予計分。
題目給定兩個多項式，請輸出兩個多項式相加的結果。

多項式運算結果輸出規範:
1. 輸出計算後從最高次方到0次方的結果
2. 每一項須輸出係數、x、x的次方數，輸出格式如下:
x的次方數 > 1，輸出ax^k (a為係數，k為次方數)
x的次方數 = 1，輸出ax (a為係數)
x的次方數 = 0，輸出a (a為係數)
如果所有係數都為0，則該行輸出0

正負號規範:
若該項係數為0，不輸出該項
若該項的次方數不為多項式的最高次方數，則該項根據係數值的正負數輸出對應的 "+" 或 "-"
若該項的係數值為1或-1，則不輸出係數值，僅輸出對應的 "+" 或 "-"

【輸入說明】
輸入共兩行，每行各代表一個多項式。
每一行輸入 n 個整數，第一個數字代表多項式中 n-1次方項的係數，第 n 個代表多項式中 0 次方項的係數。

Sample Input:
2 3 0 1 -1 (代表輸入的多項式為2x^4+3x^3+x-1)
1 0 -1 4 -3 2 (代表輸入的多項式為x^5-x^3+4x^2-3x+2)

【輸出說明】
輸出兩個多項式相加的結果

Sample Output:
x^5+2x^4+2x^3+4x^2-2x+1 (2x^4+3x^3+x-1+x^5-x^3+4x^2-3x+2的結果)

【測試資料一】
輸入：
2 3 0 1 -1
1 0 -1 4 -3 2

輸出：
x^5+2x^4+2x^3+4x^2-2x+1

【測試資料二】
輸入：
3 5 -2 1
-3 2 4 5

輸出：
7x^2+2x+6

【測試資料三】
輸入：
4 -1 2 -9
7 1 6 -1 5

輸出：
7x^4+5x^3+5x^2+x-4

【測試資料四】
輸入：
3 5 4 2 9
-3 -5 -4 -2 -9

輸出：
0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// 定義多項式節點結構
typedef struct Node {
    int coef;           // 係數
    int power;          // 次方
    struct Node* next;  // 指向下一個節點的指標
} Node;

// 建立新節點的函式
Node* createNode(int coef, int power) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coef = coef;
    newNode->power = power;
    newNode->next = NULL;
    return newNode;
}

// 將節點接在 Linked List 尾端的函式
void appendNode(Node** head, Node** tail, int coef, int power) {
    Node* newNode = createNode(coef, power);
    if (*head == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

// 解析輸入的一行字串並建立多項式 Linked List
Node* parseLine(char* line) {
    int temp[2000];
    int count = 0;
    
    // 使用 strtok 切割空白字元以讀取整數
    char* token = strtok(line, " \t\n\r");
    while (token != NULL) {
        temp[count++] = atoi(token);
        token = strtok(NULL, " \t\n\r");
    }
    
    Node* head = NULL;
    Node* tail = NULL;
    // 第一個數字為最高次方 (count - 1)，依序遞減到 0 次方
    for (int i = 0; i < count; i++) {
        appendNode(&head, &tail, temp[i], count - 1 - i);
    }
    return head;
}

// 兩個多項式相加的函式
Node* addPolynomials(Node* p1, Node* p2) {
    Node* resHead = NULL;
    Node* resTail = NULL;
    
    while (p1 != NULL || p2 != NULL) {
        int c = 0, p = 0;
        
        if (p1 != NULL && (p2 == NULL || p1->power > p2->power)) {
            c = p1->coef;
            p = p1->power;
            p1 = p1->next;
        } else if (p2 != NULL && (p1 == NULL || p2->power > p1->power)) {
            c = p2->coef;
            p = p2->power;
            p2 = p2->next;
        } else { // 次方相同時，係數相加
            c = p1->coef + p2->coef;
            p = p1->power;
            p1 = p1->next;
            p2 = p2->next;
        }
        
        // 只有在相加後係數不為 0 時，才加入結果串列中
        if (c != 0) {
            appendNode(&resHead, &resTail, c, p);
        }
    }
    return resHead;
}

// 依題目規範輸出多項式
void printPolynomial(Node* head) {
    // 如果結果串列為空，代表所有係數都為 0
    if (head == NULL) {
        printf("0\n");
        return;
    }
    
    Node* curr = head;
    int is_first = 1; // 用來標記是否為輸出的第一項
    
    while (curr != NULL) {
        int coef = curr->coef;
        int power = curr->power;
        
        // 1. 處理正負號
        if (is_first) {
            if (coef < 0) {
                printf("-");
            }
        } else {
            if (coef > 0) {
                printf("+");
            } else {
                printf("-");
            }
        }
        
        // 2. 處理係數值的輸出數字
        int abs_coef = abs(coef);
        if (power == 0) {
            // 0 次方項不論係數是不是 1 都要輸出數字
            printf("%d", abs_coef);
        } else {
            // 非 0 次方項若絕對值為 1 則隱藏數字
            if (abs_coef != 1) {
                printf("%d", abs_coef);
            }
        }
        
        // 3. 處理 x 與次方的文字輸出
        if (power > 1) {
            printf("x^%d", power);
        } else if (power == 1) {
            printf("x");
        }
        
        is_first = 0;
        curr = curr->next;
    }
    printf("\n");
}

// 釋放 Linked List 記憶體
void freeList(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    char line1[20000];
    char line2[20000];
    
    // 讀取兩行輸入
    if (fgets(line1, sizeof(line1), stdin) == NULL) return 0;
    if (fgets(line2, sizeof(line2), stdin) == NULL) return 0;
    
    // 解析並建立兩個多項式的 Linked List
    Node* poly1 = parseLine(line1);
    Node* poly2 = parseLine(line2);
    
    // 執行相加
    Node* result = addPolynomials(poly1, poly2);
    
    // 輸出結果
    printPolynomial(result);
    
    // 釋放記憶體
    freeList(poly1);
    freeList(poly2);
    freeList(result);
    
    return 0;
}