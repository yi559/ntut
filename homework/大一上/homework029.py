def processing(instruction:list,article:list):
    ins = instruction[0]
    match ins:
        case "awf":
            i = int(instruction[1])-1
            n = int(instruction[2])-1
            article[i].insert(n,instruction[3])
            return article
            
        case "awa":
            i = int(instruction[1])-1
            n = int(instruction[2])
            article[i].insert(n,instruction[3])
            return article
        
        case "asf":
            i = int(instruction[1])-1
            string = instruction[2:]
            new_string = string[::-1]
            for x in new_string:
                article[i].insert(0,x)
            return article
        
        case "asa":
            i = int(instruction[1])-1
            string = instruction[2:]
            for x in string:
                article[i].append(x)
            return article
        
        case "if":
            for i in range(len(article)):
                new_line = []
                for w in article[i]:
                    if w == instruction[1]:
                        new_line.append(instruction[2])
                        new_line.append(w)
                    else:
                        new_line.append(w)
                article[i] = new_line
            return article
        
        case "ia":
            for i in range(len(article)):
                new_line = []
                for w in article[i]:
                    if w == instruction[1]:
                        new_line.append(w)
                        new_line.append(instruction[2])
                    else:
                        new_line.append(w)
                article[i] = new_line
            return article

        case "dw":
            i = int(instruction[1])-1
            n = int(instruction[2])-1
            del article[i][n]
            return article
        
        case "dl":
            i = int(instruction[1])-1
            del article[i]
            return article
        
        case "rp":
            for i in range(len(article)):
                new_line = []
                for w in article[i]:
                    if w == instruction[1]:
                        new_line.append(instruction[2])
                    else:
                        new_line.append(w)
                    article[i] = new_line
            return article

        case "c":
            num = 0
            for i in range(len(article)):
                num += len(article[i])
            print(num)
            return article
        
def main():
    M,N = map(int,input().split())
    article = []
    instruction = []
    
    article = [input().split() for _ in range(M)]
    for _ in range(N):
        instruction.append(list(input().split()))

    
    for ins in instruction:
        article = processing(ins,article)
        #print(article)

    for i in range(len(article)):
        for j in range(len(article[i])):
            print(article[i][j],end=" ")
        print()
    
main()