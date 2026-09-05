/*035 交集字元

給定一個字串 S、一個字串 P，以及一個正整數 n。 字串P的長度可被n整除 (n | len(P))
將字串P依照長度n切割為若干子字串: p1, p2, …, plen(P)/n，
其中pi = P[(i-1)*n+1 ... i*n]

定義函數 set(X) 表示字串 X 中所有不同英文字元所形成的集合。
例如:
set(“AABAAB”) = {A, B}
set(“ABAB”) = set(“BABA”) = {A, B}

對於兩個子字串 pi​ 與 pj ，且 i < j ​，若 set(pi) 與 set(pj) 的交集和set(S)相同，則稱(i, j)為一組合法配對。
請計算合法配對的數量。

範例說明:
AABAAB
4
CDECABABABCAABBC

第一行為字串S，
第二行為數字代表以n個字元切割字串P，
第三行為字串P，
切割完成後，會得到len(p)/n個字串(p1, p2, …., plen(p)/n)。

合法配對個數計算:
(1, 2): p1(CDEC) 跟 p2(ABAB)，set(p1)∩set(p2) = {} ≠ {A, B} = set(S)，不是合法配對 。
(1, 3): p1(CDEC) 跟 p3(ABCA)，set(p1)∩set(p3) = {C} ≠ {A, B} = set(S)，不是合法配對。
(1, 4): p1(CDEC) 跟 p4(ABBC)，set(p1)∩set(p4) = {C} ≠ {A, B} = set(S)，不是合法配對。
(2, 3): p2(ABAB) 跟 p3(ABCA)，set(p2)∩set(p3) = {A, B} = {A, B} = set(S)，是合法配對。
(2, 4): p2(ABAB) 跟 p4(ABBC)，set(p2)∩set(p4) = {A, B} = {A, B} = set(S)，是合法配對。
(3, 4): p3(ABCA) 跟 p4(ABBC)，set(p3)∩set(p4) = {A, B, C} ≠ {A, B} = set(S)，不是合法配對。

總共有2組合法配對，答案為2。

--------------------------------------------------------------------------------------------------------------

輸入範例說明:
第一行為輸入一個字串S
第二行為輸入一個整數n (2 < n < 10)
第三行為輸入一個字串P，字串P的長度必為n的整數倍，長度不超過100


輸出範例說明:
輸出合法配對個數計算結果


【測試資料一】
輸入：
AABAAB
4
CDECABABABCAABBC


輸出：
2

【測試資料二】
輸入：
UIKA
3
UIOILUURMFAI


輸出：
0


【測試資料三】
輸入：
ADEAE
6
AQPEDCVFYBRTZAZDLEPMKHUYTFDEWAXCFSTHKLQDEA


輸出：
4
*/
#include <stdio.h>
#include <string.h>

// 函式：將一個字串（或字串片段）轉換成二進位位元集合
int get_char_set_mask(const char *str, int start, int length) {
    int mask = 0;
    for (int i = 0; i < length; i++) {
        char ch = str[start + i];
        // 假設字元主要為大寫 A-Z（若有小寫亦可適用，減去固定基準點即可）
        // 這裡以 ASCII 碼作為位元偏移量
        int bit_pos = ch - 'A'; 
        mask |= (1 << bit_pos);
    }
    return mask;
}

int main() {
    char S[105];
    int n;
    char P[105];

    // 讀取輸入資料
    if (scanf("%s", S) != 1) return 0;
    if (scanf("%d", &n) != 1) return 0;
    if (scanf("%s", P) != 1) return 0;

    // 1. 計算 set(S) 的位元遮罩
    int target_mask = get_char_set_mask(S, 0, strlen(S));

    int len_P = strlen(P);
    int num_parts = len_P / n;
    int part_masks[105];

    // 2. 將字串 P 切割成若干子字串，並計算各自的位元遮罩
    for (int i = 0; i < num_parts; i++) {
        part_masks[i] = get_char_set_mask(P, i * n, n);
    }

    // 3. 雙重迴圈比較所有 (i, j) 配對，其中 i < j
    int valid_pairs = 0;
    for (int i = 0; i < num_parts; i++) {
        for (int j = i + 1; j < num_parts; j++) {
            // 位元 AND 運算代表集合交集
            if ((part_masks[i] & part_masks[j]) == target_mask) {
                valid_pairs++;
            }
        }
    }

    // 輸出答案
    printf("%d\n", valid_pairs);

    return 0;
}