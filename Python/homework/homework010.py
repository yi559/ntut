import math
def quantity(qty, rates):
    if 0<qty<11:
        return 1
    elif 10<qty<21:
        return rates[0]/100
    elif 20<qty<31:
        return rates[1]/100
    else:
        return rates[2]/100

def main():
    data = [list(map(int,input().split())) for _ in range(3)]
    total = []
    price = [380,1200,180]

    for i in range(3):
        qty = data[i][0]
        rates = data[i][1:]
        discount = quantity(qty,rates)

        total.append([math.ceil(qty * price[i] * discount)])
        total[i].append(chr(i+65))
    
    total.sort()

    print('%c: %d' %(total[2][1], total[2][0]))
    print('%c: %d' %(total[0][1], total[0][0]))
    all = sum(x[0] for x in total)
    print(all)
main()