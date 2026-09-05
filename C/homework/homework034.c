/*034 交錯字串

一個字串全由大寫英文字母組成稱為大寫字串；全由小寫字母組成稱為小寫字串。字串的長度是字母的個數。本題字串由大小寫英文字母組成。
k-交錯字串定義：
(1) 由長度為k的大寫字串與長度為k的小寫字串交錯串接組成。例如「StRiNg」是一個1-交錯字串，因它是一個大寫一個小寫交替出現；而「heLLow」是一個2-交錯字串，因它是兩個小寫接兩個大寫再接兩個小寫。
(2) 不管k是多少，「aBBaaa」、「BaBaBB」、「aaaAAbbCCCC」都不是k-交錯字串。
對於給定k值，找出字串最長一段連續子字串滿足k交錯字串。例如 k=2 且字串「aBBaaa」，最長k-交錯字串是「BBaa」，長度為4。又如 k=1 且輸入「BaBaBB」，最長k-交錯字串是「BaBaB」，長度為5。

【輸入說明】
第一行為輸入一個整數N(1 <= N <= 5)，代表N個字串S。
其後N行，每一行輸入一個字串S (5 <= S長度 <= 50)、一個整數k，以空白隔開。

範例輸入說明:
5 (輸出5個字串)
fFwDbRaaNk 1 (輸入字串為fFwDbRaaNk，k = 1)
xxADAkwvDDXVxcxc 5 (輸入字串xxADAkwvDDXCVxcxc ，k = 5)
QSVxcDFnmFDScvQ 3 (輸入字串QSVxcDFnmFDScvQ，k = 3)
HXzxDSkYNefAT 2 (輸入字串HXzxDSkYNefAT，k = 2)
xzjhRVDWmTDJWksvx 4 ((輸入字串xzjhRVDWmTDJWksvx ，k = 4))

【輸出說明】
輸出每個字串中符合k-交錯字串的最長子字串長度，以換行隔開
若無符合的子字串輸出 0

範例輸出說明:
7 (最長1-交錯字串為"fFwDbRa", 長度為7)
0 (無符合5-交錯字串的子字串)
0 (無符合3-交錯字串的子字串)
6 (最長2-交錯字串為"HXzxDS"和"YNefAT", 長度為6)
8 (最長4-交錯字串為"xzjhRVDW"和"TDJWksvx", 長度為8)

【測試資料一】
輸入：
3
kDiKmjJKk 1
pLklJIguOKhIkjOIklJWoKJ 2
KLoppKLhiikLKJ 3

輸出：
5
8
6

【測試資料二】
輸入：
4
xyzABCDpqrs 4
AAaaBBbbCCcc 2
aAaAaAaAaA 1
abcXYZabcXYZabc 3

輸出:
8
12
10
15

【測試資料三】
5
fFwDbRaaNk 1
xxADAkwvDDXVxcxc 5
QSVxcDFnmFDScvQ 3
HXzxDSkYNefAT 2
xzjhRVDWmTDJWksvx 4

輸出：
7
0
0
6
8

【測試資料四】
輸入:
2
aAbBcC 1
aaAABBBBcccc 2

輸出:
6
4
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100

void solve() {
    char S[MAX_LEN];
    int k;
    
    // 讀取字串與 k 值
    if (scanf("%s %d", S, &k) != 2) return;
    
    int len = strlen(S);
    int runs[MAX_LEN];
    int run_count = 0;
    
    // 步驟 1: 計算連續相同大小寫的字母片段長度
    int current_run = 1;
    for (int i = 1; i < len; i++) {
        // 如果當前字元與前一個字元同為大寫，或同為小寫
        if ((isupper(S[i]) && isupper(S[i-1])) || (islower(S[i]) && islower(S[i-1]))) {
            current_run++;
        } else {
            runs[run_count++] = current_run;
            current_run = 1;
        }
    }
    runs[run_count++] = current_run; // 放入最後一個片段
    
    // 步驟 2: 根據 k 值計算最長連續符合條件的區塊數
    int current_blocks = 0;
    int max_blocks = 0;
    
    for (int i = 0; i < run_count; i++) {
        int L = runs[i];
        
        if (L < k) {
            // 長度不足，交錯中斷
            current_blocks = 0;
        } else if (L == k) {
            // 長度剛好，交錯長度加 1
            current_blocks++;
            if (current_blocks > max_blocks) {
                max_blocks = current_blocks;
            }
        } else { // L > k
            // 長度大於 k，可以提供一個 k 作為目前交錯的結尾
            current_blocks++;
            if (current_blocks > max_blocks) {
                max_blocks = current_blocks;
            }
            // 同時也可以留下尾端的 k 作為新交錯字串的開頭
            current_blocks = 1;
        }
    }
    
    // 步驟 3: 計算並輸出總長度
    // 交錯字串必須至少由大寫、小寫各一個區塊組成，因此區塊數必須 >= 2
    int ans = 0;
    if (max_blocks >= 2) {
        ans = max_blocks * k;
    }
    
    printf("%d\n", ans);
}

int main() {
    int n;
    // 讀取測資筆數
    if (scanf("%d", &n) == 1) {
        while (n--) {
            solve();
        }
    }
    return 0;
}