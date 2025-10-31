def pick(one:list,two:list,card:str):
    if card not in two:
        print("Error")
        exit()
    two.remove(card)
    one.append(card)

    return one,two

def tidy(card:list):
    nocard = []
    for i in range(len(card)-1):
        for j in range(i+1,len(card)):
            x1 = list(card[i])
            x2 = list(card[j])
            if x1[-1] == x2[-1]:
                nocard.append(card[i])
                nocard.append(card[j])
    for x in nocard:
        card.remove(x)
    return card

def out(data:list):
    for x in data:
        print(x,end=" ")
    print()

def main():
    card = {"H2","H3","H4","H5","H6","H7","H8","C2","C3","C4","C5","C6","C7","C8","Joker"}
    pl1 = list(input().split())
    pl2 = list(input().split())
    com = list(input().split())
    draw12 = input()
    draw2c = input()
    drawc1 = input()


    for group in [pl1, pl2, com]:
        for x in group:
            if x not in card:
                print("Error")
                return
    
    pl1 = tidy(pl1)
    pl2 = tidy(pl2)
    com = tidy(com)

    pl1,pl2 = pick(pl1,pl2,draw12)
    pl1 = tidy(pl1)
    pl2 = tidy(pl2)
    pl2,com = pick(pl2,com,draw2c)
    pl2 = tidy(pl2)
    com = tidy(com)
    com,pl1 = pick(com,pl1,drawc1)
    com = tidy(com)
    pl1 = tidy(pl1)
    
    out(pl1)
    out(pl2)
    out(com)
main()