def count_bingo_lines(matrix, selected, N):
    selected = set(selected)
    lines = 0

    mark = [[matrix[i][j] in selected for j in range(N)] for i in range(N)]

    for i in range(N):
        if all(mark[i]):
            lines += 1

    for j in range(N):
        if all(mark[i][j] for i in range(N)):
            lines += 1

    main_diag = all(mark[i][i] for i in range(N))
    if main_diag:
        lines += 1

    anti_diag = all(mark[i][N - 1 - i] for i in range(N))
    if anti_diag:
        lines += 1
    if main_diag and anti_diag:
        lines += 1

    first_col = all(mark[j][0] for j in range(N))
    last_row = all(mark[N - 1][i] for i in range(N))
    if first_col and last_row:
        lines += 1

    return lines


def main():
    N = int(input().strip())
    M = int(input().strip())

    A_nums = list(map(int, input().split()))
    B_nums = list(map(int, input().split()))
    selected = list(map(int, input().split()))

    A = [A_nums[i * N:(i + 1) * N] for i in range(N)]
    B = [B_nums[i * N:(i + 1) * N] for i in range(N)]

    A_lines = count_bingo_lines(A, selected, N)
    B_lines = count_bingo_lines(B, selected, N)
    if A_lines > B_lines:
        print("A Win")
    elif B_lines > A_lines:
        print("B Win")
    else:
        print("Tie")
main()