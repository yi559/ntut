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