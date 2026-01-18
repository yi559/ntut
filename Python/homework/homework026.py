def myprint(c,start,end,steap):
    for _ in range(start,end,steap):
        print(c,end='')

def myprintnumber(start,end,d):
    if d == 0:
        for i in range(start,end,1):
            print(i,end='')
    else:
        for i in range(start,end,-1):
            print(i,end='')

def main():
    n = int(input())
    m = int(input())
    c = int(input())

    if c == 1:
        if m%2 == 0:
            for i in range(n):
                myprint("*",i+1,0,-1)
                myprint("_",n-1-i,0,-1)
                myprint("_",n-1-i,0,-1)
                myprint("*",i+1,0,-1)
                myprint("*",0,i,1)
                myprint("_",n-1-i,0,-1)
                print()
            for i in range(n-1):
                myprint("*",n-1-i,0,-1)
                myprint("_",0,i+1,1)
                myprint("_",0,i+1,1)
                myprint("*",n-1-i,0,-1)
                myprint("*",n-2-i,0,-1)
                myprint("_",0,i+1,1)
                print()
        else:
            for i in range(n):
                myprint("_",n-1-i,0,-1)
                myprint("*",0,i,1)
                myprint("*",i+1,0,-1)
                myprint("_",n-1-i,0,-1)
                myprint("_",n-1-i,0,-1)
                myprint("*",i+1,0,-1)
                print()
            for i in range(n-1):
                myprint("_",0,i+1,1)
                myprint("*",n-2-i,0,-1)
                myprint("*",n-1-i,0,-1)
                myprint("_",0,i+1,1)
                myprint("_",0,i+1,1)
                myprint("*",n-1-i,0,-1)
                print()
    else:
        if m%2 == 0:
            for i in range(n):
                myprint("_",0,i,1)
                myprintnumber(n-i,0,1)
                myprintnumber(2,n-i+1,0)
                myprint("_",0,i,1)
                print()
        else:
            for i in range(n):
                myprint("_",n-1-i,0,-1)
                myprintnumber(i+1,0,1)
                myprintnumber(2,i+2,0)
                myprint("_",n-1-i,0,-1)
                print()

main()