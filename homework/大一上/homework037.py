def main():
    n = int(input())
    data = {}
    infomation = []
    order = []

    for _ in range(n):
        name = list(input().split())
        data[name[0]] = name[1:]
        order.append(name[0])

    m = int(input())
    for _ in range(m):
        infomation.append(list(input().split(" + ")))
    b = int(input())

    for info in infomation:
        infodata = [x.split() for x in info]
        coincidence = {key: 0 for key in data}

        if b == 0:
            for key, vals in data.items():
                count_group = 0
                for group in infodata:
                    ok = True
                    for item in group:
                        if item not in vals:
                            ok = False
                            break
                    if ok:
                        count_group += 1
                coincidence[key] = count_group

            max_count = max(coincidence.values())
            for name in order:
                if coincidence[name] == max_count:
                    print(name, end=" ")
            print()

        else:
            required = set()
            for group in infodata:
                for item in group:
                    required.add(item)

            for key, vals in data.items():
                cnt = 0
                for attr in required:
                    if attr in vals:
                        cnt += 1
                coincidence[key] = cnt
            entries = []
            for idx, name in enumerate(order):
                c = coincidence[name]
                if c > 0:
                    entries.append((name, c, idx))

            entries.sort(key=lambda x: (-x[1], x[2]))

            if entries:
                print(" ".join(x[0] for x in entries))
            else:
                print()

main()
