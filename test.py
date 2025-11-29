def gen(chars, length):
    # 1. 基本情況：
    if length == 1:
        return [c for c in chars]

    # 2. 遞迴呼叫：先求長度 length-1 的所有組合
    smaller = gen(chars, length - 1)

    result = []

    # 3. 組合結果：把每個字元加到 smaller 前面
    for ch in chars:
        for s in smaller:
            result.append(ch + s)

    return result

print(gen("abc",2))