/*028 成績排名
計算一個班級中 N 位同學在 M 門課的平均成績，並印出前三名的 ID 與平均分數。
評分制度設定：每一門課可設定為「等第評分 (G)」或「百分制評分 (S)」
- 等第評分 (G)：包含 A+, A, A-, B+, B, B-, C+, C, C-, F, X
- 百分制評分 (S)：0-100 分
根據分數對照表將所有成績轉換為「百分制對照值」以計算平均 (平均成績需四捨五入到整數)，最後輸出前三名同學的 ID 與平均成績。

| 等第 | 百分制區間 | 百分制對照值 (用於計算) |
| --- | --- | --- |
| A+ | 90-100 | 95 |
| A | 85-89 | 87 |
| A- | 80-84 | 82 |
| B+ | 77-79 | 78 |
| B | 73-76 | 75 |
| B- | 70-72 | 70 |
| C+ | 67-69 | 68 |
| C | 63-66 | 65 |
| C- | 60-62 | 60 |
| F | 59以下 | 50 |
| X | 0 | 0 |

實作要求：
1.必須使用 enum 定義評分制型別（如 scoreType_t）與等第型別（如 grade_t）
2.必須使用 union 定義分數資料型別（如 score_t），可選擇儲存 int score 或 grade_t grade

參考程式碼：
```
typedef enum scoreType_s {G, S} scoreType_t;
typedef enum grade_s{A, B, C} grade_t;
typedef union score_s{
int score;
grade_t grade;
} score_t; // 兩種評分選一種
```


【輸入說明】
依序輸入計算參數：
第一行輸入整數 N (人數) 與 M (科目數)。
第二行輸入 M 個整數，代表每門課的評分制（0 為等第制 G，1 為百分制 S）。
接下來 N 行，每行先輸入學生 ID，後接 M 個成績（若為等第制則輸入字母，百分制則輸入數字）

【輸出說明】
1.輸出計算結果，格式為 “ID - 平均分數”，答案四捨五入到整數

【測試資料一】
輸入:
3 2
0 1
001 A+ 95
002 A 87
003 A- 82

輸出:
001 - 95
002 - 87
003 - 82

【測試資料二】
輸入:
3 2
0 1
001 A+ 90
002 A 85
003 A- 80

輸出:
001 - 95
002 - 87
003 - 82

【測試資料三】
輸入:
5 2
0 1
001 A+ 0
002 A 55
003 A- 61
004 B+ 71
005 B 68

輸出:
004 - 74
005 - 72
003 - 71

【測試資料四】
輸入:
3 3
0 1 1
001 A+ 90 70
002 A 85 0
003 A- 80 55

輸出:
001 - 87
003 - 71
002 - 58
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef enum gradingMode_e { MODE_LETTER, MODE_NUMERIC } gradingMode_t;

typedef enum letterRank_e {
    RANK_AP,
    RANK_A,
    RANK_AM,
    RANK_BP,
    RANK_B,
    RANK_BM,
    RANK_CP,
    RANK_C,
    RANK_CM,
    RANK_F,
    RANK_X
} letterRank_t;

typedef union marks_u {
    int raw_points;
    letterRank_t rank_code;
} marks_t;

typedef struct {
    char serial_num[50];
    int final_rating;
    int arrival_index;
} Learner;

letterRank_t convert_to_rank(const char *input_str) {
    if (strcmp(input_str, "A+") == 0) return RANK_AP;
    if (strcmp(input_str, "A") == 0)  return RANK_A;
    if (strcmp(input_str, "A-") == 0) return RANK_AM;
    if (strcmp(input_str, "B+") == 0) return RANK_BP;
    if (strcmp(input_str, "B") == 0)  return RANK_B;
    if (strcmp(input_str, "B-") == 0) return RANK_BM;
    if (strcmp(input_str, "C+") == 0) return RANK_CP;
    if (strcmp(input_str, "C") == 0)  return RANK_C;
    if (strcmp(input_str, "C-") == 0) return RANK_CM;
    if (strcmp(input_str, "F") == 0)  return RANK_F;
    return RANK_X;
}

int map_rank_to_weight(letterRank_t r) {
    switch (r) {
        case RANK_AP: return 95;
        case RANK_A:  return 87;
        case RANK_AM: return 82;
        case RANK_BP: return 78;
        case RANK_B:  return 75;
        case RANK_BM: return 70;
        case RANK_CP: return 68;
        case RANK_C:  return 65;
        case RANK_CM: return 60;
        case RANK_F:  return 50;
        case RANK_X:  return 0;
    }
    return 0;
}

int map_points_to_weight(int pts) {
    if (pts >= 90 && pts <= 100) return 95;
    if (pts >= 85 && pts <= 89)  return 87;
    if (pts >= 80 && pts <= 84)  return 82;
    if (pts >= 77 && pts <= 79)  return 78;
    if (pts >= 73 && pts <= 76)  return 75;
    if (pts >= 70 && pts <= 72)  return 70;
    if (pts >= 67 && pts <= 69)  return 68;
    if (pts >= 63 && pts <= 66)  return 65;
    if (pts >= 60 && pts <= 62)  return 60;
    if (pts > 0 && pts <= 59)    return 50;
    return 0;
}

int sort_by_performance(const void *p1, const void *p2) {
    Learner *l1 = (Learner *)p1;
    Learner *l2 = (Learner *)p2;
    if (l2->final_rating != l1->final_rating) {
        return l2->final_rating - l1->final_rating;
    }
    return l1->arrival_index - l2->arrival_index;
}

int main() {
    int total_recints, total_subjects;
    if (scanf("%d %d", &total_recints, &total_subjects) != 2) return 0;

    gradingMode_t *subject_modes = (gradingMode_t *)malloc(total_subjects * sizeof(gradingMode_t));
    for (int idx = 0; idx < total_subjects; idx++) {
        int temp_mode;
        scanf("%d", &temp_mode);
        subject_modes[idx] = (gradingMode_t)temp_mode;
    }

    Learner *roster = (Learner *)malloc(total_recints * sizeof(Learner));

    for (int i = 0; i < total_recints; i++) {
        scanf("%s", roster[i].serial_num);
        roster[i].arrival_index = i;
        int accumulated_weights = 0;

        for (int j = 0; j < total_subjects; j++) {
            marks_t current_mark;
            if (subject_modes[j] == MODE_LETTER) {
                char text_buffer[10];
                scanf("%s", text_buffer);
                current_mark.rank_code = convert_to_rank(text_buffer);
                accumulated_weights += map_rank_to_weight(current_mark.rank_code);
            } else {
                int numeric_val;
                scanf("%d", &numeric_val);
                current_mark.raw_points = numeric_val;
                accumulated_weights += map_points_to_weight(current_mark.raw_points);
            }
        }
        double calculated_avg = (double)accumulated_weights / total_subjects;
        roster[i].final_rating = (int)(calculated_avg + 0.5);
    }

    qsort(roster, total_recints, sizeof(Learner), sort_by_performance);

    int display_count = (total_recints < 3) ? total_recints : 3;
    for (int i = 0; i < display_count; i++) {
        printf("%s - %d\n", roster[i].serial_num, roster[i].final_rating);
    }

    free(subject_modes);
    free(roster);

    return 0;
}