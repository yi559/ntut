def expand(expr):
    expr = expr.strip()
    if not expr:
        return ""

    def expand_part(part):
        part = part.strip()
        if "*" in part:
            pieces = part.split("*")
            if len(pieces) != 2:
                return None
            left, right = pieces[0].strip(), pieces[1].strip()

            # left 為數字，right 為字串
            if left.isdigit() and right != "":
                return right * int(left)
            # right 為數字，left 為字串
            if right.isdigit() and left != "":
                return left * int(right)
            return None  # 無法解析成合法的乘法
        else:
            return part  # 沒有 *，視為純字串片段

    # 先以 + 分割（支援多段 a+b+c）
    parts = expr.split("+")
    expanded_parts = []
    for p in parts:
        ep = expand_part(p)
        if ep is None:
            # 若有任一段無法被解析，則整個小括號保留原樣（題目規格也許要這樣）
            return expr
        expanded_parts.append(ep)

    return "".join(expanded_parts)


def bracket_check_and_eval(s):
    pairs = {')': '(', ']': '[', '}': '{'}
    level = {'(': 1, '[': 2, '{': 3}  # 小括號最內層 1 < 2 < 3

    stack = []            # 存開括號字元
    content_stack = []    # 和 stack 對應，存各層累積的內容字串
    hierarchy_violation = False
    unbalanced = False

    for ch in s:
        if ch in "({[":
            # 若已在某層，檢查層級：若新開的層級比上一層更大，表示較外層的括號被小括號包住 -> 違規
            if stack:
                if level[ch] > level[stack[-1]]:
                    hierarchy_violation = True

            stack.append(ch)
            content_stack.append("")

        elif ch in ")}]":
            if not stack:
                unbalanced = True
                break

            if stack[-1] != pairs[ch]:
                unbalanced = True
                break

            open_br = stack.pop()
            content = content_stack.pop()

            # 只有小括號需要做字串運算
            if open_br == "(":
                content = expand(content)

            # 合併回上一層（若沒有上一層就放回頂層）
            if content_stack:
                content_stack[-1] += content
            else:
                content_stack.append(content)

        else:
            # 普通字元放入當前層（若還沒任何層，就當作 top-level string）
            if not content_stack:
                content_stack.append("")
            content_stack[-1] += ch

    # 若還有未關閉的開括號 -> Unbalanced
    if stack:
        unbalanced = True

    # 優先輸出 Unbalanced（若同時有兩種錯）
    if unbalanced:
        return "Unbalanced"
    if hierarchy_violation:
        return "Hierarchy Violation"

    return content_stack[0] if content_stack else ""


def main():
    N = int(input().strip())
    outputs = []

    for _ in range(N):
        s = input()
        outputs.append(bracket_check_and_eval(s))

    for res in outputs:
        print(res)

if __name__ == "__main__":
    main()
