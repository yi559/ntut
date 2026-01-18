def main():    
    data = {}
    for _ in range(3):
        c = int(input())
        t1 = int(input())
        t2 = int(input())
        data[c] = [t1,t2] #儲存成 1001:[59,25]的形式
    
    id = sorted(data.keys()) #把課程編號排序 輸出就會從最小編號開始
    check = False
    for i in range(3): #i 0 1 2
        for j in range(i+1,3): #(i 0)1 2、(i 1) 2
            id1,id2 = id[i],id[j] #0 1、0 2、1 2
            time = sorted(set(data[id1]) & set(data[id2])) #把兩課程的時間取交集 然後從小排序
            for x in time:
                print("%d and %d conflict on %d" %(id1,id2,x)) #因為課程代號已經排序 所以可以直接輸出(會從小的開始) 再來輸出相同時間(也因為已經排序 所以會從小的)
                check = True

    if not check:
        print("correct")

main()