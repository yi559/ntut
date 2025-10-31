def main():    
    data = {}
    cheak = True
    classtime = {'1','2','3','4','5','6','7','8','9','a','b','c'}

    N = int(input())
    if N < 2 or N > 10:
        print(-1)
        return
    
    for _ in range(N):
        number = input()
        H = int(input())
        if H < 1 or H > 3:
            print(-1)
            return
        
        data[number] = [input() for _ in range(H)]

    for key, times in data.items():
        for t in times:
            if len(t) != 2 or t[0] not in "12345" or t[1] not in classtime:
                print(-1)
                return
            
    id = list(data.keys())
    data_time = list(data.values())
    for i in range(N):
        for j in range(i+1,N):
            time = set(data_time[i]) & set(data_time[j])
            
            for x in time:
                cheak = False
                print(f"{id[i]},{id[j]},{x}")

    if cheak:
        print("correct")
main()