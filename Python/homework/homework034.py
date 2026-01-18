def distribute(data, carnumber, goodstotal) -> bool:
    data = [ord(d) - 64 for d in data]
    totalwaight = sum(data)

    if totalwaight % carnumber != 0:
        return False

    avg = totalwaight / carnumber # 每節車廂總重
    nowwaight = [0] * carnumber # 每節車廂目前重量
    goodscount = [0] * carnumber # 每節車廂目前放幾個貨物

    return put(data, 0, carnumber, avg, goodscount, nowwaight, goodstotal)

def put(data, idx, carnumber, avg, goodscount, nowwaight, goodstotal):
    if idx == len(data):
        return True

    for c in range(carnumber):
        if nowwaight[c] + data[idx] <= avg and goodscount[c] + 1 <= goodstotal:
            nowwaight[c] += data[idx]
            goodscount[c] += 1

            if put(data, idx + 1, carnumber, avg, goodscount, nowwaight, goodstotal):
                return True

            nowwaight[c] -= data[idx]
            goodscount[c] -= 1

    return False

def main():
    dataS = input()
    carnumber = int(input())
    goodstotal = int(input())

    if (1 <= len(dataS) <= 10) and (1 <= carnumber <= 5) and (1 <= goodstotal <= 10) and (all('A' <= ch <= 'Z' for ch in dataS)):
        if distribute(dataS, carnumber, goodstotal) and len(dataS) <= carnumber * goodstotal:
            print("ok")
        else:
            print("fail")
    else: 
        print("error")
    
main()