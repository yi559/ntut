def main():
    card = {"A":1,"Q":0.5,"J":0.5,"K":0.5}
    N = int(input())
    betamount = list(map(int, input().split()))
    amount = [0]*(N+1)
    firstcard = list(input().split())
    point = [0.0]*(N+1)

    for i in range(N+1): #計算第一張牌的點數
        if firstcard[i] in card:                                        
            point[i] += card[firstcard[i]]
        else:
            point[i] += float(firstcard[i])
    
    for i in range(1,N+1):#玩家要牌
        while True:
            playerinput = input().split()#第一個玩家要牌
            if playerinput[0] == "N":#如果輸入N就跳出換下一個
                break
            else:
                if playerinput[1] in card:
                    point[i] += card[playerinput[1]]
                else:
                    point[i] += float(playerinput[1])

                if point[i] > 10.5:
                    amount[0] += betamount[i-1]
                    amount[i] -= betamount[i-1]
                    break
                elif point[i] == 10.5:
                    amount[i] += betamount[i-1]
                    amount[0] -= betamount[i-1]
                    break

    if all(point[i] >= 10.5 for i in range(1,N+1)):#所有玩家都已有結果（皆爆掉或是總點數為10.5），則遊戲結束，否則換電腦要牌
        for i in range(1,N+1):
            if amount[i] > 0:
                print(f"Player{i} +{amount[i]}")
            else:
                print(f"Player{i} {amount[i]}")
        if amount[0] > 0:
                print(f"Computer +{amount[0]}")
        else:
            print(f"Computer {amount[0]}")
    else:
        nonboom = []
        for i in range(1,N+1):#未爆掉的玩家點數
            if point[i] < 10.5:
                nonboom.append(point[i])
        
        if point[0] <= min(nonboom):#電腦總點數小於未爆掉的玩家中的最小點數，則持續要牌
            while True:
                computerinput = input()#電腦要牌
                if computerinput == "N":#如果輸入N就跳出結束遊戲
                    break
                else:
                    if computerinput in card:
                        point[0] += card[computerinput]
                    else:
                        point[0] += float(computerinput)

                    if point[0] == 10.5:
                        for i in range(1,N+1):
                            if point[i] < 10.5:
                                amount[0] += betamount[i-1]
                                amount[i] -= betamount[i-1]
                        break
                    elif point[0] > 10.5:
                        for i in range(1,N+1):
                            if point[i] < 10.5:
                                amount[i] += betamount[i-1]
                                amount[0] -= betamount[i-1]
                        break
                    
                    if point[0] > min(nonboom):
                        for i in range(1,N+1):
                            if point[i] < 10.5:
                                if point[0] >= point[i]:
                                    amount[0] += betamount[i-1]
                                    amount[i] -= betamount[i-1]
                                else:
                                    amount[i] += betamount[i-1]
                                    amount[0] -= betamount[i-1]
                        break
        else:
            if point[0] > min(nonboom):
                for i in range(1,N+1):
                    if point[i] < 10.5:
                        if point[0] >= point[i]:
                            amount[0] += betamount[i-1]
                            amount[i] -= betamount[i-1]
                        else:
                            amount[i] += betamount[i-1]
                            amount[0] -= betamount[i-1]

        for i in range(1,N+1):
            if amount[i] > 0:
                print(f"Player{i} +{amount[i]}")
            else:
                print(f"Player{i} {amount[i]}")
        if amount[0] > 0:
                print(f"Computer +{amount[0]}")
        else:
            print(f"Computer {amount[0]}")
        
main()