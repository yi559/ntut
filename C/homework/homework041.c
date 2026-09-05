/*41 Linklist 字串處理多重單詞操作

本題須使用以下 struct 實作 link list 才計分
typedef struct Node {
char *word;
struct Node *next;
} Node;

給定一篇英文文章、英文單詞 P 以及英文單詞 Q
針對文章中的英文單詞依序進行以下操作：
1. 單詞前插入：在英文文章中所有的單詞 P 前插入單詞 Q
2. 單詞取代：以單詞 Q 取代英文文章中所有的單詞 P
3. 單詞刪除：將英文文章中所有的單詞 P 刪除
每項操作的結果不影響其他操作。

【輸入說明】
第一行，輸入一行英文文章。
第二行，輸入英文單詞 P 以及英文單詞 Q (中間用空格隔開)

範例輸入說明：
This is a apple (輸入待操作的原始英文文章)
apple an (輸入單詞 P = apple，單詞 Q = an)


【輸出說明】
第一行~第三行，依序輸出操作後的完整英文文章。

範例輸出說明：
This is a an apple (原英文文章的 apple 前加入 an)
This is a an (以 an 取代原英文文章的 apple)
This is a (刪除原英文文章的 apple)


【測試資料一】
輸入：
the cat sat on the mat
the a

輸出：
a the cat sat on a the mat
a cat sat on a mat
cat sat on mat

【測試資料二】
輸入：
no no pain no no gain
no yes

輸出：
yes no yes no pain yes no yes no gain
yes yes pain yes yes gain
pain gain

【測試資料三】
輸入：
apple juice and green apple
apple delicious

輸出：
delicious apple juice and green delicious apple
delicious juice and green delicious
juice and green

【測試資料四】
輸入：
keep coding everyday
sleep night

輸出：
keep coding everyday
keep coding everyday
keep coding everyday

【測試資料五】
輸入：
one two one three one four
one zero

輸出：
zero one two zero one three zero one four
zero two zero three zero four
two three four
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 題目要求的 struct 架構
typedef struct Node {
    char *word;
    struct Node *next;
} Node;

// 安全複製字串的函式 (替代非標準的 strdup)
char *my_strdup(const char *s) {
    char *p = malloc(strlen(s) + 1);
    if (p) {
        strcpy(p, s);
    }
    return p;
}

// 複製整份 Link List
Node* copy_list(Node *head) {
    if (head == NULL) return NULL;
    
    Node *new_head = malloc(sizeof(Node));
    new_head->word = my_strdup(head->word);
    new_head->next = NULL;
    
    Node *curr = head->next;
    Node *new_curr = new_head;
    
    while (curr != NULL) {
        Node *new_node = malloc(sizeof(Node));
        new_node->word = my_strdup(curr->word);
        new_node->next = NULL;
        new_curr->next = new_node;
        new_curr = new_node;
        curr = curr->next;
    }
    return new_head;
}

// 印出整份 Link List
void print_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        printf("%s", curr->word);
        if (curr->next != NULL) {
            printf(" ");
        }
        curr = curr->next;
    }
    printf("\n");
}

// 釋放 Link List 記憶體
void free_list(Node *head) {
    Node *curr = head;
    while (curr != NULL) {
        Node *temp = curr;
        curr = curr->next;
        free(temp->word);
        free(temp);
    }
}

// 操作 1：在所有單詞 P 前插入單詞 Q
void insert_before(Node **head_ref, const char *P, const char *Q) {
    Node **curr = head_ref;
    while (*curr != NULL) {
        if (strcmp((*curr)->word, P) == 0) {
            Node *new_node = malloc(sizeof(Node));
            new_node->word = my_strdup(Q);
            new_node->next = *curr;
            *curr = new_node;
            // 為了跳過剛插入的 Q 以及原本的 P，指標向後移動兩格
            curr = &((*curr)->next->next);
        } else {
            curr = &((*curr)->next);
        }
    }
}

// 操作 2：以單詞 Q 取代所有單詞 P
void replace_word(Node *head, const char *P, const char *Q) {
    Node *curr = head;
    while (curr != NULL) {
        if (strcmp(curr->word, P) == 0) {
            free(curr->word);
            curr->word = my_strdup(Q);
        }
        curr = curr->next;
    }
}

// 操作 3：將所有單詞 P 刪除
void delete_word(Node **head_ref, const char *P) {
    Node **curr = head_ref;
    while (*curr != NULL) {
        if (strcmp((*curr)->word, P) == 0) {
            Node *temp = *curr;
            *curr = (*curr)->next;
            free(temp->word);
            free(temp);
        } else {
            curr = &((*curr)->next);
        }
    }
}

int main() {
    char article[1005];
    char P[105], Q[105];
    
    // 讀取英文文章
    if (fgets(article, sizeof(article), stdin) == NULL) return 0;
    // 移除換行符號
    article[strcspn(article, "\r\n")] = '\0';
    
    // 讀取單詞 P 與 Q
    if (scanf("%s %s", P, Q) != 2) return 0;
    
    // 將文章切成單詞並建立原始 Link List
    Node *origin_head = NULL;
    Node *tail = NULL;
    char *token = strtok(article, " ");
    
    while (token != NULL) {
        Node *new_node = malloc(sizeof(Node));
        new_node->word = my_strdup(token);
        new_node->next = NULL;
        
        if (origin_head == NULL) {
            origin_head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        token = strtok(NULL, " ");
    }
    
    // 執行操作 1: 單詞前插入
    Node *list1 = copy_list(origin_head);
    insert_before(&list1, P, Q);
    print_list(list1);
    free_list(list1);
    
    // 執行操作 2: 單詞取代
    Node *list2 = copy_list(origin_head);
    replace_word(list2, P, Q);
    print_list(list2);
    free_list(list2);
    
    // 執行操作 3: 單詞刪除
    Node *list3 = copy_list(origin_head);
    delete_word(&list3, P);
    print_list(list3);
    free_list(list3);
    
    // 釋放原始 list
    free_list(origin_head);
    
    return 0;
}