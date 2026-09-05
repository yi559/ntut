/*036 互補單字

給定一個字串S，以及數個待比對字串Si, 1<=i<=n，輸出這些字串Si【互補對】的個數。

此題字串的定義：
(1) 英文字的集合，英文字重複出現只算一個，不考慮排列順序。例如 "Happy Happy Day" 與 "Day Happy Day" 是相同的字串。

兩個字串S1, S2為【互補對】的定義：
(1) S1, S2 沒有出現相同的字。
(2) S內的字，會全部出現在 S1 + S2內。

【輸入說明】
第1行，字串S。1<=英文字長度<=10，1<=英文字個數<=10，英文字以一個空白間隔，
第2行，整數 n，待比對字串Si 數量，2<=n<=10
第3~n+3行，字串Si，1<=英文字數量<=10，英文字以一個空白間隔，1<=每個英文字長度<=10

範例輸入說明:
happy birthday to you(字串S)
4(n，待比對字串數量)
happy to you(字串S1)
birthday birthday(字串S2)
to you(字串S3)
happy birthday(字串S4)

【輸出說明】
輸出【互補對】個數(整數)


範例輸出說明:
2
互補字串個數計算:
S1(happy to you) 跟 S2(birthday birthday)，S1跟S2的英文字沒有重複，且字串S內的字恰好都被S1, S2所包含，因此為互補字串。
S1(happy to you) 跟 S3(to you)，因為英文字 to 和 you 重複，不是互補字串 。
S1(happy to you) 跟 S4(happy birthday)，因為英文字 happy 重複，不是互補字串。
S2(birthday birthday) 跟 S3(to you)，S1跟S2的字雖然沒重複，但字串S中的英文字happy沒有出現在S1或S2中，因此不是互補字串。
S2(birthday birthday) 跟 S4(happy birthday)，因為英文字 birthday 重複，不是互補字串。
S3(to you) 跟 S4(happy birthday)，S1跟S2的英文字沒有重複，且字串S內的字恰好都被S1, S2所包含，因此為互補字串。
根據上述互補字串個數計算，總共有兩個互補字串，答案為2。)

【測試資料一】
輸入:
I like to eat banana
4
like banana
I to eat
I like eat
to banana

輸出:
2

【測試資料二】
輸入 :
the raven is never backward
3
raven backward never
the backward raven
is never

輸出:
1


【測試資料三】
輸入 :
father mother son children friend parent
5
father mother
mother son children
children friend parent
father son friend
mother children

輸出：
0

【測試資料四】
輸入 :
MONDAY TUESDAY TUESDAY SATURDAY FRIDAY
4
MONDAY MONDAY
TUESDAY TUESDAY SATURDAY FRIDAY
TUESDAY SATURDAY FRIDAY
MONDAY SATURDAY

輸出：
2

【測試資料五】
輸入 :
the teacher teach the math to the student
4
the teacher to the student
teach math
teacher math
the teach to student

輸出：
2

【測試資料六】
輸入 :
he likes to eat dinner by himself
6
he likes to eat
dinner himself
by dinner
he likes eat himself
he eat himself
likes by dinner

輸出：
0
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORDS 15
#define MAX_WORD_LEN 15
#define MAX_N 15
#define MAX_LINE_LEN 200

// 儲存主字串 S 的單字字典
char dict[MAX_WORDS][MAX_WORD_LEN];
int dict_size = 0;

// 尋找單字在字典中的編號，若不存在則加入字典
int get_word_id(char *word, bool add_if_not_exist) {
    for (int i = 0; i < dict_size; i++) {
        if (strcmp(dict[i], word) == 0) {
            return i;
        }
    }
    if (add_if_not_exist && dict_size < MAX_WORDS) {
        strcpy(dict[dict_size], word);
        return dict_size++;
    }
    return -1; // 不在主字串中的無效單字
}

// 將一行包含多個單字的字串，轉換為位元遮罩
int get_line_mask(char *line, bool is_main_string) {
    int mask = 0;
    char *word = strtok(line, " \n\r");
    
    while (word != NULL) {
        int id = get_word_id(word, is_main_string);
        if (id != -1) {
            mask |= (1 << id);
        } else {
            // 如果待比對字串包含了主字串 S 所沒有的單字，
            // 設置一個特殊位元（例如第 30 位），讓它永遠無法匹配成功
            mask |= (1 << 30);
        }
        word = strtok(NULL, " \n\r");
    }
    return mask;
}

int main() {
    char line[MAX_LINE_LEN];
    int n;
    
    // 1. 讀取主字串 S 
    if (fgets(line, sizeof(line), stdin) == NULL) return 0;
    dict_size = 0; // 初始化字典
    int target_mask = get_line_mask(line, true);
    
    // 2. 讀取待比對字串數量 n
    if (fgets(line, sizeof(line), stdin) == NULL) return 0;
    sscanf(line, "%d", &n);
    
    // 3. 讀取 n 個待比對字串並轉換成 mask
    int masks[MAX_N];
    for (int i = 0; i < n; i++) {
        if (fgets(line, sizeof(line), stdin) != NULL) {
            masks[i] = get_line_mask(line, false);
        } else {
            masks[i] = 0;
        }
    }
    
    // 4. 雙重迴圈配對檢查
    int complement_pairs = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // 條件 1: 兩者交集為空 (沒有重複單字)
            // 條件 2: 兩者聯集剛好等於主字串 S 的單字集合
            if ((masks[i] & masks[j]) == 0 && (masks[i] | masks[j]) == target_mask) {
                complement_pairs++;
            }
        }
    }
    
    // 輸出結果
    printf("%d\n", complement_pairs);
    
    return 0;
}