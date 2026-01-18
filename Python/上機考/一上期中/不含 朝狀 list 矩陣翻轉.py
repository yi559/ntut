def front(n:int):
    x,y=0,0
    while x < n:
        if y < n:
            print(n*x+y+1,end=' ')
            y += 1
        else:
            print()
            y = 0
            x += 1
    return

def right(n:int):
    x,y=0,0
    while x < n:
        if y < n:
            print(x+n*(n-y-1)+1,end=' ')
            y += 1
        else:
            print()
            y = 0
            x += 1
    return

def left(n:int):
    x,y=0,0
    while x < n:
        if y < n:
            print(n*(y+1)-x,end=' ')
            y += 1
        else:
            print()
            y = 0
            x += 1
    return

def reverse(n:int):
    x,y=0,0
    while x < n:
        if y < n:
            print(n*(n-x-1)+n-y,end=' ')
            y += 1
        else:
            print()
            y = 0
            x += 1
    return

def main():
    n = int(input())
    flip = input()
    angle = 0
    
    for x in flip:
        if x == "R":
            angle +=1
        else:
            angle -=1

    angle = angle % 4

    match angle:
        case 0:
            front(n)
        case 1 | -3:
            right(n)
        case 2 | -2:
            reverse(n)
        case 3 | -1:
            left(n)

main()