def main():
    course = {}
    check = True
    week = ["1","2","3","4","5"]
    time = ["1","2","3","4","5","6","7","8","9","a","b","c"]
    
    N = int(input())
    if N < 2 or N > 10:
        print(-1)
        return
    
    for _ in range(N):
        classname = input()
        H = int(input())
        if H < 1 or H > 3:
            print(-1)
            return

        course[classname] = {input() for _ in range(H)}

    for key,item in course.items():
        for x in item:
            if len(x) !=2 or x[0] not in week or x[1] not in time:
                print(-1)
                return

    id = list(course.keys())
    data = list(course.values())
    for i in range(N):
        for j in range(i+1,N):
            chongtang = set(data[i]) & set(data[j])

            for x in chongtang:
                check = False
                print(f"{id[i]},{id[j]},{x}")

    if check:
        print("correct")
main()