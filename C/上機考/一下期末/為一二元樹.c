/*Final_Exam6
唯一二元樹
請使用以下結構實作。

Link List 架構:
typedef struct node_s {
char data;
struct node_s * right, * left;
} tree_t;
typedef tree_t * btree;

給定前序或後序以及中序，請建構唯一的Binary Tree(非二元搜尋樹)。
輸出該Tree的內容，輸出順序為由上而下，由左而右印出。

前序或後序以及中序代號分別為:
前序代號：P
中序代號：I
後序代號：O

【輸入說明】
第一行輸入前序、中序或後序的代號。
第二行輸入上一行輸入尋訪的字串結果A(1<=A的字串長度<=20)，結果皆為大寫英文字母。
第三行輸入前序、中序或後序的代號。
第四行輸入上一行輸入尋訪的字串結果B(1<=B的字串長度<=20)。

範例輸入說明:
Sample Input:
P (下一行輸入前序結果)
ABDHIEJKCFLMGNO (前序尋訪Tree的結果)
I (下一行輸入中序結果)
HDIBJEKALFMCNGO(中序尋訪Tree的結果)

【輸出說明】
輸出唯一二元樹的內容，輸出順序為由上而下，由左而右。

Sample Output:
ABCDEFGHIJKLMNO(唯一二元樹由上而下，由左而右的輸出結果)。

【測試資料一】
輸入：
P
ABDHIEJKCFLMGNO
I
HDIBJEKALFMCNGO

輸出：
ABCDEFGHIJKLMNO

【測試資料二】
輸入：
I
CHRONEMIA
O
AIMENORHC

輸出：
CHRONEMIA

【測試資料三】
輸入：
P
MQVYBJAWZCDKXHT
I
YBVJQWAMCZKDHXT

輸出：
MQZVACDYJWKXBHT

【測試資料四】
輸入：
I
MXFIPNOEAGDRL
O
MFIONPXDRGLAE

輸出：
EXAMPLINGFORD

【測試資料五】
輸入：
O
EGATNIV
I
ITGEANV

輸出：
VINTAGE
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s{
    char data;
    struct node_s *right, *left;
} tree_t;

typedef tree_t *btree;

btree buildTreePI(char *pre, char *in, int inStart, int inEnd, int *pIdx){
    if (inStart > inEnd) return NULL;

    btree root = (btree)malloc(sizeof(tree_t));
    root->data = pre[(*pIdx)++];
    root->left = NULL;
    root->right = NULL;

    if (inStart == inEnd) return root;

    int inIdx;
    for (int i = inStart; i <= inEnd; i++){
        if(in[i] == root->data){
            inIdx = i;
            break;
        }
    }

    root->left = buildTreePI(pre, in, inStart, inIdx - 1, pIdx);
    root->right = buildTreePI(pre, in, inIdx + 1, inEnd, pIdx);

    return root;
}

btree buildTreeIO(char *post, char *in, int inStart, int inEnd, int *oIdx){
    if (inStart > inEnd) return NULL;

    btree root = (btree)malloc(sizeof(tree_t));
    root->data = post[(*oIdx)--]; 
    root->left = NULL;
    root->right = NULL;

    if (inStart == inEnd) return root;

    int inIdx;
    for (int i = inStart; i <= inEnd; i++) {
        if (in[i] == root->data) {
            inIdx = i;
            break;
        }
    }

    root->left = buildTreeIO(post, in, inStart, inIdx - 1, oIdx);
    root->right = buildTreeIO(post, in, inIdx + 1, inEnd, oIdx);

    return root;
}

void printLevelOrder(btree root){
    if (root == NULL) return;

    btree queue[50];
    int front = 0;
    int rear = 0;

    queue[rear++] = root;

    while (front < rear){
        btree current = queue[front++];
        printf("%c", current->data);

        if (current->left != NULL){
            queue[rear++] = current->left;
        }

        if (current->right != NULL){
            queue[rear++] = current->right;
        }
    }
    printf("\n");
}

int main(void){
    char code1, code2;
    char tree1[25], tree2[25];

    if (scanf(" %c", &code1) != 1) return 0;
    scanf("%s", tree1);
    if (scanf(" %c", &code2) != 1) return 0;
    scanf("%s", tree2);

    char *pre = NULL;
    char *in = NULL;
    char *post = NULL;

    if (code1 == 'P') pre = tree1;
    else if (code1 == 'I') in = tree1;
    else if (code1 == 'O') post = tree1;

    if (code2 == 'P') pre = tree2;
    else if (code2 == 'I') in = tree2;
    else if (code2 == 'O') post = tree2;

    btree root = NULL;
    int len = strlen(in);

    if(pre != NULL && in != NULL){
        int pIdx = 0;
        root = buildTreePI(pre, in, 0, len - 1, &pIdx);
    }else if (post != NULL && in != NULL){
        int oIdx = len - 1;
        root = buildTreeIO(post, in, 0, len - 1, &oIdx);
    }

    printLevelOrder(root);

    return 0;
}