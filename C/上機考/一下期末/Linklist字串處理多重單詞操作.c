/*Final_Exam9
Linklist 字串處理多重單詞操作

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

typedef struct node{
    char *word;
    struct node *next;
} node;

node* createNode(const char *word){
    node *newNode = (node*)malloc(sizeof(node));
    newNode->word = strdup(word);
    newNode->next = NULL;
    return newNode;
}

void printList(node *head){
    node *curr = head;
    while (curr != NULL){
        printf("%s", curr->word);
        if (curr->next != NULL){
            printf(" ");
        }
        curr = curr->next;
    }
    printf("\n");
}

void freeList(node *head) {
    node *curr = head;
    while (curr != NULL) {
        node *temp = curr;
        curr = curr->next;
        free(temp->word);
        free(temp);
    }
}

node* cloneList(node *head) {
    if (head == NULL) return NULL;
    node *newHead = createNode(head->word);
    node *curr = head->next;
    node *newCurr = newHead;
    while (curr != NULL) {
        newCurr->next = createNode(curr->word);
        newCurr = newCurr->next;
        curr = curr->next;
    }
    return newHead;
}

node* insertBefore(node *head, const char *p, const char *q){
    if (head == NULL) return NULL;

    node *curr = head;

    if (strcmp(head->word, p) == 0) {
        node *newNode = createNode(q);
        newNode->next = head;
        head = newNode;
    }

    while (curr != NULL && curr->next != NULL){
        if (strcmp(curr->next->word, p) == 0){
            node *newNode = createNode(q);
            newNode->next = curr->next;
            curr->next = newNode;
            
            curr = newNode->next; 
        }else{
            curr = curr->next;
        }
    }

    return head;
}

node* replace(node *head, const char *p, const char *q){
    node *curr = head;

    while (curr != NULL){
        if (strcmp(curr->word, p) == 0){
            free(curr->word);
            curr->word = strdup(q);
        }
        curr = curr->next;
    }
    return head;
}

node* deleteNode(node *head, const char *p){
    while (head != NULL && strcmp(head->word, p) == 0){
        node *temp = head;
        head = head->next;
        free(temp->word);
        free(temp);
    }

    if (head == NULL) return NULL;

    node *curr = head;
    while (curr != NULL && curr->next != NULL){
        if (strcmp(curr->next->word, p) == 0){
            node *temp = curr->next;
            curr->next = temp->next;
            free(temp->word);
            free(temp);
        }else{
            curr = curr->next;
        }
    }
    return head;
}

int main(void){
    char data[200];
    if (fgets(data, sizeof(data), stdin) == NULL) return 0;

    data[strcspn(data, "\n")] = '\0';

    node *head = NULL;
    node *tail = NULL;

    char *token = strtok(data, " ");
    while (token != NULL){
        node *newNode = createNode(token);

        if (head == NULL){
            head = newNode;
            tail = newNode;
        }else{
            tail->next = newNode;
            tail = newNode;
        }

        token = strtok(NULL, " ");
    }

    char p[100], q[100];
    if (scanf("%s %s", p, q) != 2) {
        freeList(head);
        return 0;
    }

    node *list1 = cloneList(head);
    list1 = insertBefore(list1, p, q);
    printList(list1);
    freeList(list1);

    node *list2 = cloneList(head);
    list2 = replace(list2, p, q);
    printList(list2);
    freeList(list2);

    node *list3 = cloneList(head);
    list3 = deleteNode(list3, p);
    printList(list3);
    freeList(list3);

    freeList(head);
    
    return 0;
}