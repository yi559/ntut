def main():
    N = int(input())
    for i in range(N):
        balanced = []
        violation = []
        data = input()
        stack = []
        output = []
        b = m = n = -1
        for i in range(len(data)):
            if data[i] in "{[(":
                stack.append(i)
            elif data[i] in ")]}":
                if len(stack) == 0:
                    balanced.append(False)
                    break
                elif data[stack[-1]] == "{" and data[i] == "}":
                    stack.pop()
                    b = i
                elif data[stack[-1]] == "[" and data[i] == "]":
                    if stack[-1] <= b <= i:
                        violation.append(False)
                        break
                    stack.pop()
                    m = i
                elif data[stack[-1]] == "(" and data[i] == ")":
                    if stack[-1] <= b <= i or stack[-1] <= m <= i:
                        violation.append(False)
                        break
                    stack.pop()
                    n = i
                else:
                    balanced.append(False)
        
        if not balanced:
            continue
        elif not violation:
            continue
        else:
            output.append()
main()