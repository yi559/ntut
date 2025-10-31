def strength(data:list):
    out = []
    special_symbols = {" ","~","!","@","#","$","%","^","&","*","<",">","_","+","="}
    for i in range(len(data)):
        score = 0.0
        bigletter = 0
        number = 0
        symbols = 0.0
        point = []
        password = list(data[i])

        for j in range(len(password)):
            if 96 < ord(password[j]) < 123:
                score += 1
            elif 64 < ord(password[j]) < 91:
                bigletter += 1
            elif password[j].isdigit():
                number += 1
                point.append(j)
            elif password[j] in special_symbols:
                symbols += 1

        if number > 4 and all(b - a > 1 for a, b in zip(point, point[1:])):
            score += 10
        if len(password) > 8:
            score += len(password)-8
        if "1234" in data[i]:
            score -= 10
        score += (bigletter * 3)
        score += (number * 2)
        score += (symbols * 4.5)
            
        out.append([score,data[i]])
        
    maxpass = max(out,key=lambda x: x[0])
    minpass = min(out,key=lambda x: x[0])
    return maxpass,minpass
        
            
def main():
    N = int(input())
    data = []
    for _ in range(N):
        data.append(input())
    maxpass,minpass = strength(data)
    print(maxpass[1],maxpass[0])
    print(minpass[1],minpass[0])
main()