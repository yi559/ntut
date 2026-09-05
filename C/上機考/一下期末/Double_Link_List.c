/*Final_Exam8
Double Link List (雙向鏈結串列)

本題必須使用Double Link List實作，否則不予計分。

Double Link List結構:
typedef struct dnode_s {
int data;
struct dnode_s * front;
struct dnode_s * back;
} node_t;
typedef node_t * nodep_t;

8種Double Link List操作：
除了remove n 以外，執行其餘任一操作(含 empty )時，如果串列是空的則輸出"Double link list is empty"。
addFront：將資料放入串列前端，不進行輸出。
addBack：將資料放入串列尾端，不進行輸出。
removeFront：將最前端的節點刪除，不進行輸出。
removeBack : 將最尾端端的節點刪除，不進行輸出。
empty：將串列中所有節點刪除，不進行輸出。
insert n : 在第n個節點後插入新的資料，最前端節點為1，不進行輸出。假如串列長度小於n則輸出"Invalid command"，其餘情況不進行輸出。
remove n : 刪除第n個節點，最前端節點為1。假如串列長度小於n則輸出"Invalid command"，其餘情況不進行輸出。
print：將串列中所有節點資料從前端到尾端依序輸出data。

【輸入說明】
第一行，輸入一整數 N ( 1 <= N <= 20 )，代表有N個操作。
第二行~第2+N行，輸入操作的種類
addFront操作:addFront data，addFront為字串，data為整數(0<=data<=100)，中間以空白隔開
addBack操做:addBack data，addBack為字串，data為整數(0<=data<=100)，中間以空白隔開
removeFront操作:removeFront，removeFront為字串
removeBack操作:removeBack，removeBack為字串
empty操作:empty，empty為字串
insert n操作：insert n data，insert為字串，n為整數(1<=n<=20)，data為整數(0<=data<=100)，中間以空白隔開
remove n操作：remove n，remove為字串，n為整數(1<=n<=20)，中間以空白隔開
print操作：print，print為字串

範例輸入說明:
13 (N為13，代表有13個操作)
addFront 13(在串列前端加入13)
addBack 12(在串列尾端加入12)
addFront 10(在串列前端加入10)
insert 2 20(在第2個節點後加入20)
insert 5 100(在第5個節點後加入100)
remove 2(移除第2個節點)
print(由前端到尾端輸出所有節點)
remove 5(移除第5個節點)
removeBack(刪除最尾端的節點)
removeFront(刪除最前端的節點)
print(由前端到尾端輸出所有節點)
empty(刪除串列所有節點)
empty(刪除串列所有節點)


【輸出說明】
第一行~第N行，根據操作輸出對應的data

範例輸出說明:
Invalid command(根據輸入的操作1、2、3、4，串列長度為4，由於5超過串列長度，故指令失效)
10(根據輸入的操作6，串列長度為3，第一個節點的data為10)
20(根據輸入的操作6，串列長度為3，第二個節點的data為20)
12(根據輸入的操作6，串列長度為3，第三個節點的data為12)
Invalid command(目前串列長度為3，由於5超過串列長度，故指令失效)
20(根據輸入操作9、10，串列長度為1，第一個節點的data為20)
Double link list is empty (在操作12時，已將Stack中所有節點刪除，故為空)

【測試資料一】
輸入：
8
print
removeFront
removeBack
empty
insert 1 50
addFront 10
print
remove 1

輸出：
Double link list is empty
Double link list is empty
Double link list is empty
Double link list is empty
Invalid command
10

【測試資料二】
輸入：
10
addBack 66
addFront 55
print
removeBack
print
addBack 77
addBack 88
print
empty
print

輸出：
55
66
55
55
77
88
Double link list is empty

【測試資料三】
輸入：
11
addFront 12
insert 1 23
insert 2 34
print
insert 5 99
removeFront
print
insert 2 45
print
removeBack
print

輸出：
12
23
34
Invalid command
23
34
23
34
45
23
34

【測試資料四】
輸入：
11
addFront 90
addFront 80
addFront 70
print
remove 2
print
insert 2 60
print
remove 1
print
remove 3

輸出：
70
80
90
70
90
70
90
60
90
60
Invalid command

【測試資料五】
輸入：
16
addFront 15
addBack 25
insert 1 20
print
remove 2
print
insert 4 99
empty
print
addFront 35
insert 1 45
remove 1
print
removeBack
print
removeFront

輸出：
15
20
25
15
25
Invalid command
Double link list is empty
45
Double link list is empty
Double link list is empty
*/