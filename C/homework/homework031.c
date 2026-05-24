/*031 邏輯電路圖
請設計一個邏輯電路模擬器，模擬由各種邏輯閘（AND、OR、NOT 等）所構成的電路，根據輸入值與邏輯閘的種類計算最終的輸出值。
本題需依照下列程式架構撰寫，否則不予計分。

輸入的邏輯閘種類代號如下：
N：NOT Gate
B：BUFFER Gate
A：AND Gate
O：OR Gate
NA：NAND Gate
NO：NOR Gate

所有輸入與中間運算皆以「3 位元」為單位進行處理，任何 NOT 或邏輯運算後的結果，僅保留其最低 3 位元（0~7）。
例如：

NOT(0) = ~000 = 111 = 7

NOT(5) = ~101 = 010 = 2

程式設計規範：
解題時可針對範例的架構程式碼做修改，但需符合以下三點：
1. #define中必須定義函數指標，函數的參數可自行決定
2. 有定義struct，且當中有使用到第一點的define
3. 使用struct的函數指標進行本題的實作

#define GATEVALUE(Gate) int(*GateValue)()
typedef struct _Gate {
    int input1;
    int input2;
    GATEVALUE(Gate);
}Gate;

int GateORValue(Gate *gate) {
...
}

int GateANDValue(Gate *gate) {
...
}

int GateNOTValue(Gate *gate) {
...
}

int GateBUFFERValue(Gate *gate) {
...
}

void CreateGate(Gate *obj, char type, int input1, int input2) {
...
}


【輸入說明】
第一行：輸入三個整數，代表X1, X2, X3的數值，中間以空白隔開(範圍:0~7)
第二行：輸入字串，中間以空白隔開，說明如下：
X1 的處理方式：N 表示 NOT，B 表示 BUFFER（直接輸出）

X2 的處理方式：同上

X3 的處理方式：同上

第一組邏輯閘（對處理後的 X1 與 X2 做運算，產生中間變數 Y）

第二組邏輯閘（對 Y 與 處理後的X3 做運算，產生最終輸出）

範例說明:
Sample Input:
0 1 2 (X1, X2, X3)
N B B O A (X1 invert, X2, X3, X1 invert 與X2做OR運算得出Y, Y與X3做AND運算)

X1 = 0 → NOT → 7

X2 = 1 → BUFFER → 1

Y = 7 OR 1 = 7

X3 = 2 → BUFFER → 2

Output = 7 AND 2 = 10 (十進位 2)

【輸出說明】
輸出計算的Output binary值

Sample Output:
010

【測試資料一】
輸入：
0 1 2
N B B O A

輸出：
010

【測試資料二】
輸入：
7 4 1
B N B NO NA

輸出：
111

【測試資料三】
輸入：
4 3 1
N N N A NO

輸出：
001

【測試資料四】
輸入：
2 7 1
B N N NO A

輸出：
100
*/

#include <stdio.h>
#include <string.h>

#define GATEVALUE(Gate) int (*GateValue)(struct _Gate *gate)

typedef struct _Gate {
    int input1;
    int input2;
    GATEVALUE(Gate);
} Gate;

int GateNOTValue(Gate *gate) {
    return (~gate->input1) & 7;
}

int GateBUFFERValue(Gate *gate) {
    return (gate->input1) & 7;
}

int GateANDValue(Gate *gate) {
    return (gate->input1 & gate->input2) & 7;
}

int GateORValue(Gate *gate) {
    return (gate->input1 | gate->input2) & 7;
}

int GateNANDValue(Gate *gate) {
    return (~(gate->input1 & gate->input2)) & 7;
}

int GateNORValue(Gate *gate) {
    return (~(gate->input1 | gate->input2)) & 7;
}

void CreateGate(Gate *obj, char *type, int input1, int input2) {
    obj->input1 = input1;
    obj->input2 = input2;
    
    if (strcmp(type, "N") == 0) {
        obj->GateValue = GateNOTValue;
    } else if (strcmp(type, "B") == 0) {
        obj->GateValue = GateBUFFERValue;
    } else if (strcmp(type, "A") == 0) {
        obj->GateValue = GateANDValue;
    } else if (strcmp(type, "O") == 0) {
        obj->GateValue = GateORValue;
    } else if (strcmp(type, "NA") == 0) {
        obj->GateValue = GateNANDValue;
    } else if (strcmp(type, "NO") == 0) {
        obj->GateValue = GateNORValue;
    }
}

void printBinary3Bit(int num) {
    printf("%d%d%d\n", (num >> 2) & 1, (num >> 1) & 1, num & 1);
}

int main() {
    int x1, x2, x3;
    char opX1[5], opX2[5], opX3[5], opG1[5], opG2[5];
    
    if (scanf("%d %d %d", &x1, &x2, &x3) != 3) return 0;
    if (scanf("%s %s %s %s %s", opX1, opX2, opX3, opG1, opG2) != 5) return 0;
    
    Gate gateX1, gateX2, gateX3, gateG1, gateG2;
    
    CreateGate(&gateX1, opX1, x1, 0);
    int resX1 = gateX1.GateValue(&gateX1);
    
    CreateGate(&gateX2, opX2, x2, 0);
    int resX2 = gateX2.GateValue(&gateX2);
    
    CreateGate(&gateX3, opX3, x3, 0);
    int resX3 = gateX3.GateValue(&gateX3);
    
    CreateGate(&gateG1, opG1, resX1, resX2);
    int Y = gateG1.GateValue(&gateG1);
    
    CreateGate(&gateG2, opG2, Y, resX3);
    int finalOutput = gateG2.GateValue(&gateG2);
    
    printBinary3Bit(finalOutput);
    
    return 0;
}