def main():
    M = int(input())
    N = int(input())

    if N < 3 or N > 50:
        print("Row Error")
        return
    
    if M == 1:
        for i in range(N):
            for j in range(1, i+2):
                print(j,end="")
            for j in range(i,0,-1):
                print(j,end="")
            print()

    if M == 2:
        for i in range(N):
            for j in range(i,N-1):
                print("_",end="")
            for j in range(1, i+2):
                print(j,end="")
            for j in range(i,0,-1):
                print(j,end="")
            for j in range(i,N-1):
                print("_",end="")
            print()

    if M == 3:
        for i in range(N):
            for j in range(0,i):
                print("_",end="")
            for j in range(1,N-i+1):
                print(j,end="")
            for j in range(N-i-1,0,-1):
                print(j,end="")
            for j in range(0,i):
                print("_",end="")
            print()
main()