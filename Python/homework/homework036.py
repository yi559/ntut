def dfs(s, idx, path, lrem, rrem, balance, results):
    # s: 原字串
    # idx: 現在處理到哪個字元
    # path: 建構中的合法字串
    # lrem, rrem: 還能刪多少左/右括號（最低刪除數量）
    # balance: 當前括號平衡計數，不能<0

    # 1. 結束條件
    if idx == len(s):
        if lrem == 0 and rrem == 0 and balance == 0:
            results.add(path)
        return

    c = s[idx]

    # 2. 選項一：如果是括號，可以選擇刪除
    if c == '(' and lrem > 0:
        dfs(s, idx+1, path, lrem-1, rrem, balance, results)

    if c == ')' and rrem > 0:
        dfs(s, idx+1, path, lrem, rrem-1, balance, results)

    # 3. 選項二：保留 c
    if c not in "()":
        # 字母直接保留
        dfs(s, idx+1, path + c, lrem, rrem, balance, results)
    else:
        # 括號
        if c == '(':
            dfs(s, idx+1, path + '(', lrem, rrem, balance + 1, results)
        else:  # c == ')'
            if balance > 0:  # 不能變負
                dfs(s, idx+1, path + ')', lrem, rrem, balance - 1, results)

def calc_removal(s):
    lrem = rrem = 0
    balance = 0

    for c in s:
        if c == '(':
            balance += 1
        elif c == ')':
            if balance == 0:
                rrem += 1  # 多的右括號
            else:
                balance -= 1

    lrem = balance
    return lrem, rrem

def main():
    s = input().strip()

    lrem, rrem = calc_removal(s)
    results = set()
    dfs(s, 0, "", lrem, rrem, 0, results)

    # 輸出最少刪除數
    print(lrem + rrem)

    # 結果依字典序輸出
    ans = sorted(results)
    print(" ".join(ans))
main()