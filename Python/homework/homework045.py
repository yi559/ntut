def is_safe(board, row, col, num):
    """
    檢查將數字 num 填入 (row, col) 是否符合數獨規則
    """
    # 1. 檢查橫列 (Row)
    for x in range(4):
        if board[row][x] == num:
            return False
            
    # 2. 檢查直欄 (Column)
    for x in range(4):
        if board[x][col] == num:
            return False
            
    # 3. 檢查 2x2 區塊 (Block)
    start_row = (row // 2) * 2
    start_col = (col // 2) * 2
    for i in range(2):
        for j in range(2):
            if board[i + start_row][j + start_col] == num:
                return False
                
    return True

def solve_sudoku(board):
    """
    使用回溯法 (Backtracking) 遞迴求解
    """
    for row in range(4):
        for col in range(4):
            # 尋找空白處 (0)
            if board[row][col] == 0:
                # 嘗試填入 1 到 4
                for num in range(1, 5):
                    if is_safe(board, row, col, num):
                        board[row][col] = num # 試著填入
                        
                        if solve_sudoku(board): # 遞迴呼叫下一層
                            return True
                        
                        board[row][col] = 0 # 失敗則回溯 (Backtrack)，重置為 0
                return False # 1-4 都無法填入，此路徑無解
    return True # 沒有空白了，表示解完了

def main():
    board = []
    
    # 讀取 4 行輸入
    try:
        for _ in range(4):
            # 讀取一行並轉換成整數列表
            line = list(map(int, input().split()))
            board.append(line)
    except (EOFError, ValueError):
        # 防止輸入格式錯誤或空輸入導致崩潰
        return

    # 執行求解並輸出
    if len(board) == 4 and solve_sudoku(board):
        for row in board:
            # 將列表中的數字轉字串後用空白連接印出
            print(" ".join(map(str, row)))
    else:
        # 若題目保證有解，通常不會執行到這裡
        print("No solution")

if __name__ == "__main__":
    main()