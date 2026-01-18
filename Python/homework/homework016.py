def main():
    data = list(input().split())
    total = 0.0
    while "*" in data or "/" in data:
        for i in range(1,len(data),2):
            if data[i] == "*":
                total = float(data[i-1]) * float(data[i+1])
                data = data[:i-1] + [total] + data[i+2:]
                break
            if data[i] == "/":
                total = float(data[i-1]) / float(data[i+1])
                data = data[:i-1] + [total] + data[i+2:]
                break
        
    while "+" in data or "-" in data:
        for i in range(1,len(data),2):
            if data[i] == "+":
                total = float(data[i-1]) + float(data[i+1])
                data = data[:i-1] + [total] + data[i+2:]
                break
            if data[i] == "-":
                total = float(data[i-1]) - float(data[i+1])
                data = data[:i-1] + [total] + data[i+2:]
                break
    
    ans = float(data[0])
    print(f"{ans:.2f}")
main()