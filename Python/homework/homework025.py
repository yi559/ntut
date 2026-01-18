def compute(card:list):
    numbers = {"A":1,"J":11,"Q":12,"K":13}
    point = []
    for x in card:
        if x[:-1] in numbers:
            point.append(numbers[x[:-1]])
        else:
            point.append(int(x[:-1]))
    return point

def ispairs(card:list)->int:
    point = compute(card)
    data = [point.count(i) for i in point]
    return data.count(2)//2

def isthreekind(card:list)->bool:
    point = compute(card)
    data = [point.count(i) for i in point]
    return any(data[i] == 3 for i in range(5))
    
def isstraight(card:list)->bool:
    point = compute(card)
    point.sort()
    if all(b-a==1 or b-a==9 for a,b in zip(point,point[1:])):
        return True
    return False
    
def isflush(card:list)->bool:
    data = []
    for x in card:
        data.append(x[-1])

    if len(set(data)) == 1:
        return True
    return False

def isfourkind(card:list)->bool:
    point = compute(card)
    if any(point.count(x) == 4 for x in point):
        return True
    return False

def main():
    cards = ["A","2","3","4","5","6","7","8","9","10","J","Q","K"]
    color = ["S","H","D","C"]
    card = input().split()

    errorinput = False
    duplicate = False
    for x in card:
        rank = x[:-1]
        suit = x[-1]
        if rank not in cards or suit not in color:
            errorinput = True
    for i in range(5):
        for j in range(i+1,5):
            if card[i] == card[j]:
                duplicate = True

    if errorinput or len(card) != 5:
        print("Error input")
    elif duplicate:
        print("Duplicate deal")
    else:
        if isstraight(card):
            if isflush(card):
                print(9)
            else:
                print(5)
        elif isfourkind(card):
            print(8)
        elif isthreekind(card):
            if ispairs(card) == 1:
                print(7)
            else:
                print(4)
        elif isflush(card):
            print(6)
        else:
            print(ispairs(card)+1)

main()