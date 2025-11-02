def compute(card:list):
    point = {"A":1,"J":11,"Q":12,"K":13}
    number = []
    for x in card:
        if x[:-1] in point:
            number.append(point[x[:-1]])
        else:
            number.append(int(x[:-1]))
    return number

def ispairs(card:list)-> int:
    number = compute(card)
    pair = []
    for x in number:
        pair.append(number.count(x))
    
    return pair.count(2)//2

def isthreekind(card:list):
    number = compute(card)
    for x in number:
        if number.count(x) >= 3:
            return True
    return False

def isstraight(card:list):
    number = compute(card)
    number.sort()
    
    if all(b-a==1 or b-a==9 for a,b in zip(number,number[1:])):
        return True
    return False

def isflush(card:list):
    color = [card[i][-1] for i in range(5)]
    if len(set(color)) == 1:
        return True
    return False

def isfourkind(card:list):
    number = compute(card)
    for x in number:
        if number.count(x) == 4:
            return True
    return False
def main():
    point = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"}
    suit = {"S","H","D","C"}

    errorinput = False
    duplicate = False
    card = input().split()
    for x in card:
        if x[:-1] not in point or x[-1] not in suit:
            errorinput = True

    for i in range(5):
        for j in range(i+1,5):
            if card[i] == card[j]:
                duplicate = True

    if errorinput:
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