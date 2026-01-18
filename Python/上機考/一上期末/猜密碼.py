def T(data):
    out = []
    capital = set("ABCD")
    special = set("@#$!_")
    allowed_chars = set("ABCDabcd0123456789@#$!_")
    for s in data:
        if not (3 <= len(s) <= 5):
            out.append("F")
            continue
        if any(c not in allowed_chars for c in s):
            out.append("F")
            continue
        
        if len(set(s)) != len(s):
            out.append("F")
            continue

        has_upper = any(c in capital for c in s)
        has_special = any(c in special for c in s)
        if has_upper and has_special:
            out.append("T")
        else:
            out.append("F")

    return "".join(out)

def S(data):
    out = []
    for s in data:
        left = s[0]
        right = s[1]
        A = 0
        B = 0
        for i in range(len(left)):
            if left[i] == right[i]:
                A += 1
            elif left[i] in right:
                B += 1
        out.append(f"{A}A{B}B")

    return "\n".join(out)

def G():

    return

def main():
    x = input()
    n = int(input())
    
    if x == "T":
        data = []
        for _ in range(n):
            data.append(input())
        print(T(data))
    elif x == "S":
        data = []
        for _ in range(n):
            data.append(input().split())
        print(S(data))
    elif x == "G":
        data = []
        for _ in range(n):
            data.append(input().split())
        print(G(data))
main()