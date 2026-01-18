def myprint(c,times):
    for _ in range(times):
        print(c,end='')

def numberprint(start,end,direction):
    if direction == 0:
        for i in range(1,end+2):
            print(i,end='')
    else:
        for i in range(start,end,-1):
            print(i,end='')

def main():
    N = int(input())
    L = int(input())

    if((1<=N<=4)&(3<=L<=11)&(L%2!=0)):
        if N == 1:
            for i in range(L):
                myprint("*",L-i-1)
                myprint("-",1)
                myprint("*",i)
                print()
        elif N == 2:
            for i in range(L):
                numberprint(1,i,0)
                myprint("*",L-i-1)
                myprint("*",L-i-1)
                numberprint(i+1,0,1)
                print()
        elif N == 3:
            i = 0
            step = 1
            while i >=0:
                myprint("#",i)
                myprint("_", (L//2)-i+1)
                myprint("_",(L//2)-i)
                myprint("#",1)
                myprint("_",i)
                myprint("_",i-1)
                if i != 0 and i != L-1:
                    myprint("#",1)
                myprint("_", (L//2)-i+1)
                myprint("_",(L//2)-i)
                myprint("#",i)
                print()
                i += step
                if i == L//2:
                    step = -1 
        elif N == 4:
            for i in range(L//2):
                myprint("*",i+1)
                myprint("_",L-2-(2*i))
                myprint("*",i+1)
                print()
            print("*"*L)
            for i in range(L//2):
                myprint("_",i+1)
                myprint("*",L-2-(2*i))
                myprint("_",i+1)
                print()
    else:
        print("error")
main()