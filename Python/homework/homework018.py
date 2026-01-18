def checker(player_data:list,computer_data:list):
    checkerboard = [0,0,0,0,0,0,0,0,0]
    for i in player_data:
        checkerboard[i-1] = 1 #因為player_data是從1開始輸入，但是list要從0所以要-1
    for i in computer_data:
        checkerboard[i-1] = 2

    return checkerboard

def winner(checkerboard):
    win_lines = [[0,1,2],[3,4,5],[6,7,8],[0,3,6],[1,4,7],[2,5,8],[0,4,8],[2,4,6]] #列出所有贏的組合

    for line in win_lines:
        if all(checkerboard[i] == 1 for i in line): #先把組合帶入line，再把line裡面的元素值帶入cheakerbord裡判斷
            return "Player win"
        if all(checkerboard[i] == 2 for i in line):
            return "Computer win"
    return "Undecided"

def main():
    m = int(input())
    data = list(map(int,input().split()))
    player_data = []
    computer_data = []
    checkerboard = []

      
    if m == 1:
        player_data = data[0::2]#切片data，從0開始到最後，每次跳2
        computer_data = data[1::2]
        checkerboard = checker(player_data,computer_data)
    else:
        computer_data = data[0::2]
        player_data = data[1::2]
        checkerboard = checker(player_data,computer_data)
    
    for i in range(9):
        print(f"{checkerboard[i]} ",end="")
        if (i+1) % 3 == 0 and i !=0: #因為如果再3才分行會出現一行有4個，所以要+1在第三個印出來後就換行
            print()

    print(winner(checkerboard))
    
main()