def solve(data: str, idx: int):
    if idx == len(data):
        return [data[idx-1]]  # 回傳最後一個數字

    ops = ["+", "-", "*", ""]
    results = []
    for op in ops:
        if op == "":
            if data[idx-1] == "0":
                continue

        part = data[idx-1] + op
        tails = solve(data, idx+1)

        for t in tails:
            results.append(part + t)

    return results

def main():
    data = input()
    target = int(input())
    results = solve(data,1)
    times = 0

    for res in results:
        ans = eval(res)
        if ans == target:
            times += 1

    print(times)
main()