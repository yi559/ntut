def convert(n:int,angle:chr,matrix:list):
    conmatrix = [[0]*n for _ in range(n)]
    if angle == "R":
        for i in range(n):
            for j in range(n):
                conmatrix[i][j] = matrix[n-j-1][i]
        return conmatrix
    else:
        for i in range(n):
            for j in range(n):
                conmatrix[i][j] = matrix[j][n-i-1]
        return conmatrix
    

def main():
    n = int(input())
    flip = list(input())
    matrix = []
    
    for _ in range(n):
        matrix.append([])
    
    k = 1
    for i in range(n):
        for _ in range(n):
            matrix[i].append(k)
            k += 1

    #print(matrix)
    conmatrix = matrix
    for X in flip:
        conmatrix = convert(n,X,conmatrix)

    for i in range(n):
        for j in range(n):
            print(conmatrix[i][j],end=' ')
        print()

main()