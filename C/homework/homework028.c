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

typedef enum scoreType_s {G,S} scoreType_t;

typedef enum grade_s {
    GRADE_AP,
    GRADE_A,
    GRADE_AM,
    GRADE_BP,
    GRADE_B,
    GRADE_BM,
    GRADE_CP,
    GRADE_C,
    GRADE_CM,
    GRADE_F,
    GRADE_X
} grade_t;

typedef union score_s {
    int score;
    grade_t grade;
} score_t;

typedef struct {
    char id[50];
    int avg_score;
    int input_order;
} Student;

grade_t parse_grade(const char *str) {
    if (strcmp(str, "A+") == 0) return GRADE_AP;
    if (strcmp(str, "A") == 0)  return GRADE_A;
    if (strcmp(str, "A-") == 0) return GRADE_AM;
    if (strcmp(str, "B+") == 0) return GRADE_BP;
    if (strcmp(str, "B") == 0)  return GRADE_B;
    if (strcmp(str, "B-") == 0) return GRADE_BM;
    if (strcmp(str, "C+") == 0) return GRADE_CP;
    if (strcmp(str, "C") == 0)  return GRADE_C;
    if (strcmp(str, "C-") == 0) return GRADE_CM;
    if (strcmp(str, "F") == 0)  return GRADE_F;
    return GRADE_X;
}

int grade_to_value(grade_t g) {
    switch (g) {
        case GRADE_AP: return 95;
        case GRADE_A:  return 87;
        case GRADE_AM: return 82;
        case GRADE_BP: return 78;
        case GRADE_B:  return 75;
        case GRADE_BM: return 70;
        case GRADE_CP: return 68;
        case GRADE_C:  return 65;
        case GRADE_CM: return 60;
        case GRADE_F:  return 50;
        case GRADE_X:  return 0;
    }
    return 0;
}

int score_to_value(int score) {
    if (score >= 90 && score <= 100) return 95;
    if (score >= 85 && score <= 89)  return 87;
    if (score >= 80 && score <= 84)  return 82;
    if (score >= 77 && score <= 79)  return 78;
    if (score >= 73 && score <= 76)  return 75;
    if (score >= 70 && score <= 72)  return 70;
    if (score >= 67 && score <= 69)  return 68;
    if (score >= 63 && score <= 66)  return 65;
    if (score >= 60 && score <= 62)  return 60;
    if (score > 0 && score <= 59)    return 50;
    return 0;
}

int compare_students(const void *a, const void *b) {
    Student *s1 = (Student *)a;
    Student *s2 = (Student *)b;
    if (s2->avg_score != s1->avg_score) {
        return s2->avg_score - s1->avg_score;
    }
    return s1->input_order - s2->input_order;
}

int main() {
    int N, M;
    if (scanf("%d %d", &N, &M) != 2) return 0;

    scoreType_t *course_types = (scoreType_t *)malloc(M * sizeof(scoreType_t));
    for (int i = 0; i < M; i++) {
        int type;
        scanf("%d", &type);
        course_types[i] = (scoreType_t)type;
    }

    Student *students = (Student *)malloc(N * sizeof(Student));

    for (int i = 0; i < N; i++) {
        scanf("%s", students[i].id);
        students[i].input_order = i;
        int converted_sum = 0;

        for (int j = 0; j < M; j++) {
            score_t current_score;
            if (course_types[j] == G) {
                char grade_str[10];
                scanf("%s", grade_str);
                current_score.grade = parse_grade(grade_str);
                converted_sum += grade_to_value(current_score.grade);
            } else {
                int raw_score;
                scanf("%d", &raw_score);
                current_score.score = raw_score;
                converted_sum += score_to_value(current_score.score);
            }
        }
        double avg = (double)converted_sum / M;
        students[i].avg_score = (int)(avg + 0.5);
    }

    qsort(students, N, sizeof(Student), compare_students);

    int top_k = (N < 3) ? N : 3;
    for (int i = 0; i < top_k; i++) {
        printf("%s - %d\n", students[i].id, students[i].avg_score);
    }

    free(course_types);
    free(students);

    return 0;
}