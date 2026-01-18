def convert10(m:int):
    number = 0
    for i in range(8):
        num = m % 10
        number += num * (2**i)
        m = m // 10
    
    return number

def convert3(m:int):
    number = 0
    for i in range(6):
        number += (m%3) * (10 ** i)
        m = m // 3

    return number

def c(m:int,times = 0):
    if m == 0 or m == 1:
        return 0
    elif m%2 == 0:
        return times + 1 + c(m//2,times) 
    elif m%2 == 1:
        return times + 2 + c((m+1)//2)+c((m-1)//2,times)

def main():
    data = int(input())
    out = []
    out.append(c(convert10(data)))

    while True:
        data = int(input())
        if data == -1:
            break
        out.append(c(convert10(data)))
    
    for i in range(len(out)):
        print(f"{convert3(out[i]):06d}")
main()