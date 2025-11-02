def main():
    days = int(input())
    data = [list(input().split()) for _ in range(5)]
    
    for _ in range(days):#有幾天執行幾次
        new_data = [row[:] for row in data]
        change = [[False]*5 for _ in range(5)]

        for i in range(5):
            for j in range(5):
                if change[i][j]:
                    continue
                
                if data[i][j] == "Ai":
                    column = [data[r][j] for r in range(5)]
                    if column.count("__") < 4:
                            new_data[i][j] = "Cn"
                            change[i][j] = True

                elif data[i][j] == "Cn":
                    if i != 0 and data[i-1][j] != "__":
                        new_data[i][j] = "Hy"
                        change[i][j] = True

                elif data[i][j] == "Hy":
                    direction = [(-1,0), (1,0), (0,-1), (0,1)]
                    neighber = 0
                    space = []

                    for dx,dy in direction:
                        nx,ny = i+dx,j+dy
                        if 0 <= nx < 5 and 0 <= ny < 5:
                            if data[nx][ny] != "__":
                                neighber += 1
                            else:
                                space.append((nx,ny))
                    if neighber >= 2:
                        for nx,ny in space:
                            new_data[nx][ny] = "Na"
                            change[nx][ny] = True
                        change[i][j] = True
                        
                elif data[i][j] == "Na":
                    if j != 4 and data[i][j+1] == "__":
                        new_data[i][j+1] = "Qx"
                        change[i][j+1] = True
                        
                    if j != 0:
                        new_data[i][j-1] = "Hy"
                        change[i][j-1] = True
                    change[i][j] = True
                
                elif data[i][j] == "Qx":
                    for kind in set(data[i]):
                        if kind != "__" and data[i].count(kind) >= 3:
                            for r in range(5):
                                if data[i][r] == kind:#--------------
                                    new_data[i][r] = "Ai"
                                    change[i][r] = True
                    change[i][j] = True
                data = [row[:] for row in new_data]
                
    print()
    for i in range(5):
        for j in range(5):
            print(data[i][j] ,end=' ')
        print()
main()