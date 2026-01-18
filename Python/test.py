class Solution:
    def isValid(self, s: str) -> bool:
        stack = []
        for c in s:
            if c in "{[(":
                stack.append(c)

        for c in s:
            if c in "}])":
                if c == "}":
                    if stack[-1] == "{":
                        return True
                elif c == "]":
                    if stack[-1] == "[":
                        return True
                elif c == ")":
                    if stack[-1] == "(":
                        return True
                else:
                    return False