def get_value(name, vardata):
    for item in vardata:
        if item[0] == name:
            return item[1]
    return ""

def set_value(name, value, vardata):
    found = False
    for item in vardata:
        if item[0] == name:
            item[1] = value
            found = True
            break
    if not found:
        vardata.append([name, value])

def printwhat(ins, vardata):
    is_print = True
    for i in range(5):
        if i >= len(ins) or ins[i] != "print"[i]:
            is_print = False
            break

    if is_print:
        start = 0
        end = 0
        for i in range(len(ins)):
            if ins[i] == "(":
                start = i
            if ins[i] == ")":
                end = i
        content = ""
        for i in range(start+1, end):
            content += ins[i]

        has_slice = False
        slice_start = 0
        slice_end = 0
        for i in range(len(content)):
            if content[i] == "[":
                has_slice = True
                slice_start = i
            if content[i] == "]":
                slice_end = i

        if has_slice:
            varname = ""
            for i in range(slice_start):
                varname += content[i]
            varname = varname.strip()
            value = get_value(varname, vardata)
            slice_part = ""
            for i in range(slice_start+1, slice_end):
                slice_part += content[i]
            parts = []
            temp = ""
            for c in slice_part:
                if c != ":":
                    temp += c
                else:
                    parts.append(temp)
                    temp = ""
            parts.append(temp)
            s = int(parts[0]) if parts[0] != "" else None
            e = int(parts[1]) if len(parts) > 1 and parts[1] != "" else None
            step = int(parts[2]) if len(parts) > 2 and parts[2] != "" else None
            print(value[s:e:step])
        else:
            varname = content.strip()
            print(get_value(varname, vardata))
    else:
        eq_pos = -1
        for i in range(len(ins)):
            if ins[i] == "=":
                eq_pos = i
                break
        left = ""
        right = ""
        for i in range(eq_pos):
            left += ins[i]
        for i in range(eq_pos+1, len(ins)):
            right += ins[i]
        left = left.strip()
        right = right.strip()

        plus_pos = -1
        for i in range(len(right)):
            if right[i] == "+":
                plus_pos = i
                break
        if plus_pos != -1:
            a_name = ""
            b_name = ""
            for i in range(plus_pos):
                a_name += right[i]
            for i in range(plus_pos+1, len(right)):
                b_name += right[i]
            a_name = a_name.strip()
            b_name = b_name.strip()
            newvalue = get_value(a_name, vardata) + get_value(b_name, vardata)
        else:
            if len(right) >= 2 and right[0] == "'" and right[-1] == "'":
                right = right[1:-1]
            elif right.isalpha() and len(right) >= 1:
                right = get_value(right, vardata)
            newvalue = right

        set_value(left, newvalue, vardata)

def main():
    M, N = map(int, input().split())
    vardata = []
    instructions = []

    for _ in range(M):
        ins = input()
        eq_pos = -1
        for i in range(len(ins)):
            if ins[i] == "=":
                eq_pos = i
                break
        left = ""
        right = ""
        for i in range(eq_pos):
            left += ins[i]
        for i in range(eq_pos+1, len(ins)):
            right += ins[i]
        left = left.strip()
        right = right.strip()

        vars_index = []
        start = 0
        for i in range(len(left)):
            if left[i] == ",":
                vars_index.append([start, i])
                start = i + 1
        vars_index.append([start, len(left)])

        value_index = []
        for i in range(len(right)):
            if right[i] == "'":
                value_index.append(i)

        k = 0
        for j in range(0, len(value_index), 2):
            s = vars_index[k][0]
            e = vars_index[k][1]
            name = left[s:e].strip()
            val = right[value_index[j]+1:value_index[j+1]]
            set_value(name, val, vardata)
            k += 1

    for _ in range(N):
        ins = input()
        instructions.append(ins)

    for ins in instructions:
        printwhat(ins, vardata)

main()
