/*043 唯一二元樹
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

typedef struct node_s {
    char data;
    struct node_s *right, *left;
} tree_t;
typedef tree_t *btree;

// 建立新節點
btree createNode(char data) {
    btree newNode = (btree)malloc(sizeof(tree_t));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 尋找字元在中序字串中的位置
int findIndex(char *str, int start, int end, char value) {
    for (int i = start; i <= end; i++) {
        if (str[i] == value) return i;
    }
    return -1;
}

// 根據 P+I 重建樹
btree buildFromPI(char *P, int *pIdx, char *I, int iStart, int iEnd) {
    if (iStart > iEnd) return NULL;
    btree root = createNode(P[*pIdx]);
    (*pIdx)++;
    if (iStart == iEnd) return root;
    int iIdx = findIndex(I, iStart, iEnd, root->data);
    root->left = buildFromPI(P, pIdx, I, iStart, iIdx - 1);
    root->right = buildFromPI(P, pIdx, I, iIdx + 1, iEnd);
    return root;
}

// 根據 O+I 重建樹
btree buildFromOI(char *O, int *oIdx, char *I, int iStart, int iEnd) {
    if (iStart > iEnd) return NULL;
    btree root = createNode(O[*oIdx]);
    (*oIdx)--;
    if (iStart == iEnd) return root;
    int iIdx = findIndex(I, iStart, iEnd, root->data);
    root->right = buildFromOI(O, oIdx, I, iIdx + 1, iEnd);
    root->left = buildFromOI(O, oIdx, I, iStart, iIdx - 1);
    return root;
}

// 層序遍歷 (Queue)
void levelOrder(btree root) {
    if (!root) return;
    btree queue[100];
    int head = 0, tail = 0;
    queue[tail++] = root;
    while (head < tail) {
        btree curr = queue[head++];
        printf("%c", curr->data);
        if (curr->left) queue[tail++] = curr->left;
        if (curr->right) queue[tail++] = curr->right;
    }
    printf("\n");
}

int main() {
    char type1, type2;
    char str1[25], str2[25];
    btree root = NULL;

    scanf(" %c %s %c %s", &type1, str1, &type2, str2);

    // 判斷順序並建樹
    if (type1 == 'P' || type2 == 'P') {
        char *P = (type1 == 'P') ? str1 : str2;
        char *I = (type1 == 'I') ? str1 : str2;
        int pIdx = 0;
        root = buildFromPI(P, &pIdx, I, 0, strlen(I) - 1);
    } else {
        char *O = (type1 == 'O') ? str1 : str2;
        char *I = (type1 == 'I') ? str1 : str2;
        int oIdx = strlen(O) - 1;
        root = buildFromOI(O, &oIdx, I, 0, strlen(I) - 1);
    }

    levelOrder(root);

    return 0;
}