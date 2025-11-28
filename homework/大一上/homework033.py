def gen(chars,length):
    if length == 1:
        return [c for c in chars]
    result = []
    smaller = gen(chars, length - 1)
    for ch in chars:
        for s in smaller:
            result.append(ch + s)
    return result

def main():
    data = input()
    n = int(input())
    m = int(input())
    condition = int(input())
    c = input()

    times = 0
    data = gen(data,n)
    for ch in data:
        ok = True
        for i in range(n - m + 1):
            if ch[i:i+m].count(c) < condition:
                ok = False
                break
        if ok:
            times += 1
    print(times)
main()