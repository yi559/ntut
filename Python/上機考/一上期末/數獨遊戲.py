def is_safe(board, row, col, num):
    # Row
    if num in board[row]:
        return False

    # Column
    for r in range(4):
        if board[r][col] == num:
            return False

    # 2x2 Block
    start_row = (row // 2) * 2
    start_col = (col // 2) * 2
    for r in range(start_row, start_row + 2):
        for c in range(start_col, start_col + 2):
            if board[r][c] == num:
                return False

    return True

def solve(board):
    for row in range(4):
        for col in range(4):
            if board[row][col] == 0:
                for num in range(1, 5):
                    if is_safe(board, row, col, num):
                        board[row][col] = num
                        if solve(board):
                            return True
                        board[row][col] = 0
                return False
    return True

def main():
    board = []
    for _ in range(4):
        board.append(list(map(int, input().split())))

    if solve(board):
        for row in board:
            print(" ".join(map(str, row)))

main()