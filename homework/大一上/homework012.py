def change(x):
    if x ==  "A":
        return 1
    elif x ==  "J" or x ==  "Q" or x ==  "K":
        return 0.5
    else:
        return int(x)

def pas(x):
    if x > 10.5:
        return 0
    else:
        return x
    
def judge(x):
    if x == int(x):
        return int(x)
    else:
        return x

def main():
    x = [input() for _ in range(3)]
    y = [input() for _ in range(3)]

    totalX = judge(pas(sum(change(x[i]) for i in range(3))))
    totalY = judge(pas(sum(change(y[i]) for i in range(3))))

    print(totalX)
    print(totalY)

    if totalX > totalY:
        print("X Win")
    elif totalX < totalY:
        print("Y Win")
    else:
        print("Tie")

main()