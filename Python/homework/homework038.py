def match_with_question(pattern, text):
    for p, t in zip(pattern, text):
        if p != '?' and p != t:
            return False
    return True


def is_prime(n):
    if n < 2:
        return False
    for i in range(2, int(n ** 0.5) + 1):
        if n % i == 0:
            return False
    return True


def main():
    s = input().strip()
    E = input().split()
    l = input().strip()

    # ===== 找前面序列位置（支援 ?）=====
    s_positions = []
    for i in range(len(l) - len(s) + 1):
        if match_with_question(s, l[i:i+len(s)]):
            s_positions.append(i)

    # ===== 找後面序列位置 =====
    end_positions = []
    for e in E:
        for i in range(len(l) - len(e) + 1):
            if l[i:i+len(e)] == e:
                end_positions.append((i, e))

    genes = []

    # ===== 擷取基因 =====
    for s_idx in s_positions:
        gene_start = s_idx + len(s)

        for e_idx, e in sorted(end_positions):
            if e_idx <= gene_start:
                continue

            # 中間不能再出現另一個前面序列
            if any(s2 > s_idx and s2 < e_idx for s2 in s_positions):
                continue

            gene = l[gene_start:e_idx]

            # ===== 判斷條件 =====
            if not gene:
                continue

            if not all(c in "ATCG" for c in gene):
                continue

            if not is_prime(len(gene)):
                continue

            genes.append(gene)
            break

    # ===== 輸出 =====
    if not genes:
        print("No gene")
    else:
        genes.sort(key=lambda x: (len(x), x))
        for g in genes:
            print(g)

main()