import itertools

def T(data):
    out = []
    upper_chars = set("ABCD")
    special_chars = set("@#$!_")
    allowed_chars = set("ABCDabcd0123456789@#$!_")

    for x in data:
        if not (3 <= len(x) <= 5):
            out.append("F")
            continue
        
        if any(c not in allowed_chars for c in x):
            out.append("F")
            continue

        if len(set(x)) != len(x):
            out.append("F")
            continue

        has_upper = any(c in upper_chars for c in x)
        has_special = any(c in special_chars for c in x)
        
        if has_upper and has_special:
            out.append("T")
        else:
            out.append("F")
            
    return "".join(out) 

def S(data):
    out = []
    for x in data:
        A = 0
        B = 0
        for i in range(len(x[0])):
            if x[0][i] == x[1][i]:
                A += 1
            elif x[0][i] in x[1]:
                B += 1
        out.append(f"{A}A{B}B")
    return "\n".join(out)

def G(data):
    # 定義排序順序與規則字元集
    order_str = "ABCDabcd0123456789@#$!_"
    upper_chars = set("ABCD")
    special_chars = set("@#$!_")
    
    # 將輸入的線索依照密碼長度分組
    # 格式: clues[長度] = [(猜測字串, A, B), ...]
    clues = {}
    
    for line in data:
        parts = line.strip().split()
        if not parts: continue
        guess_str = parts[0]
        result_str = parts[1]
        
        # 解析 A 和 B 的數值
        idx_a = result_str.find('A')
        idx_b = result_str.find('B')
        val_a = int(result_str[:idx_a])
        val_b = int(result_str[idx_a+1:idx_b])
        
        length = len(guess_str)
        if length not in clues:
            clues[length] = []
        clues[length].append((guess_str, val_a, val_b))
    
    # 依照密碼長度由小到大 (3, 4, 5) 處理
    for length in sorted(clues.keys()):
        current_clues = clues[length]
        
        # 產生該長度的所有排列組合 (itertools.permutations 會依照 order_str 的順序產生，符合題目要求的輸出順序)
        for p in itertools.permutations(order_str, length):
            candidate = "".join(p)
            
            # 檢查規則 3: 至少含一個特殊字元、一個大寫字元
            # (規則 1, 2, 4 已由 permutations 和 range 控制)
            has_u = any(c in upper_chars for c in candidate)
            has_s = any(c in special_chars for c in candidate)
            
            if not (has_u and has_s):
                continue
            
            # 檢查此候選密碼是否符合所有線索
            is_valid = True
            for guess, target_a, target_b in current_clues:
                # 計算 candidate 對上 guess 的幾A幾B
                curr_a = 0
                curr_b = 0
                
                # 題目保證無重複字元，故計算邏輯較簡單
                for i in range(length):
                    if candidate[i] == guess[i]:
                        curr_a += 1
                    elif candidate[i] in guess:
                        curr_b += 1
                
                if curr_a != target_a or curr_b != target_b:
                    is_valid = False
                    break
            
            if is_valid:
                print(candidate,end=" ")
        print()

def main():
    func = input().strip()
    N = int(input())
    if func == "T":
        data = []
        for _ in range(N):
            data.append(input().strip())
        print(T(data))
    elif func == "S":
        data = []
        for _ in range(N):
            # 這裡必須加 .split()，否則 S 函式無法區分兩個字串
            data.append(input().strip().split())
        print(S(data))
    elif func == "G":
        data = []
        for _ in range(N):
            data.append(input().strip())
        G(data)
main()