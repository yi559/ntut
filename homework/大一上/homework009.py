"""def main():
    data = [int(input()) for _ in range(6)]
    start = data[0]
    end = data[1]
    for i in range(2,6):
        if start <= data[i] <= end:
            data[i] = end

    total = (data[1]-data[0])+(data[3]-data[2])+(data[5]-data[4])
    print(total)
main()"""


def main():
    data = [[int(input()), int(input())] for _ in range(3)]
    merged = []
    merged.append(data[0])

    if data[1][0] < merged[-1][1]: # merged[-1][1]代表最後一個list裡面的最後一個值   這個判斷式代表兩線段重疊所以直接找end的最大值
        merged[-1][1] = max(merged[-1][1], data[1][1])
    else:
        merged.append(data[1]) #如果沒重和 就直接在merged後面插入新的list
    if data[2][0] < merged[-1][1]:
        merged[-1][1] = max(merged[-1][1], data[2][1])
    else:
        merged.append(data[2])
    
    total = 0
    for seg in merged: 
        total += seg[1] - seg[0]
    print(total)
main()  