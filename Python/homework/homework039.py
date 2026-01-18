def enter(cur, data, m, total_weight, total_value, visited):
    if cur == "0" or cur in visited:
        return total_value

    value, weight, y, z = data[cur]

    if total_weight + weight > m:
        return total_value

    total_weight += weight
    total_value += value
    visited.add(cur)

    v1 = enter(y, data, m, total_weight, total_value, visited.copy())
    v2 = enter(z, data, m, total_weight, total_value, visited.copy())

    return max(v1, v2)

def main():
    n, first = input().split()
    m = int(input())

    data = {}
    for _ in range(int(n)):
        idx, v, w, y, z = input().split()
        data[idx] = (int(v), int(w), y, z)

    print(enter(first, data, m, 0, 0, set()))

main()