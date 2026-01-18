def act(suit:list):
    counts = {"Spade": suit.count("S"),"Heart": suit.count("H"),"Diamond": suit.count("D"),"Club": suit.count("C")}
    max_count = max(counts.values())
    x = ["Spade", "Heart", "Diamond", "Club"]
    for suit_name in x:
        if counts[suit_name] == max_count:
            return suit_name
        
def number(suit:list):
    s = str(suit.count("S"))
    h = str(suit.count("H"))
    d = str(suit.count("D"))
    c = str(suit.count("C"))
    ans = s + "-" + h +"-" + d + "-" + c
    return ans

def stopper(suit:list,face:list):
    data = {"S":[],"H":[],"D":[],"C":[]}
    for card,f in zip(suit,face):
        if card in data:
            data[card].append(f)

    x = ["S", "H", "D", "C"]
    stopped = []
    for s in x:
        cards = data[s]
        count = len(cards)
        if "A" in cards or ("K" in cards and count > 1) or ("Q" in cards and count > 2):
            stopped.append(s)
    return stopped

def decide(suit:list):
    if len(set(suit)) == 1:
        return 2
    else:
        return 0

def calculate_hcp(face:list):
    data = {"A":4,"K":3,"Q":2,"J":1}
    total = 0
    for card in face:
        if card in data:
            total += data[card]
    
    return total

def main():
    hcp = 0
    length_point = 0
    total_point = 0
    suit = list(map(str,input().split()))
    face = list(map(str,input().split()))
    
    hcp = calculate_hcp(face)
    length_point = decide(suit)
    total_point = hcp + length_point
    
    print(f"HCP: {hcp}")
    print(f"Total Points: {total_point}")
    print(f"Distribution (S-H-D-C): {number(suit)}")
    print(f"Stopped Suits: {stopper(suit,face)}")
    print("Opening Bid:", end = "")
    if total_point < 8:
        print(" Pass")
    elif total_point >= 15:
        print(" Strong Open")
    else:
        print(f" Open {act(suit)}")
main()