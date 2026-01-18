a = int(input())
b = int(input())
c = int(input())

data = [a,b,c]
data.sort()

if a+b<c or c+b<a or a+c<b or a<0 or b<0 or c<0 :
    print("Not Triangle")
else:
    if a==b==c:
        print("Equilateral Triangle")
    if a==b or b==c or c==a:
        print("Isosceles Triangle")
    if data[2]**2 > data[0]**2 + data[1]**2:
        print("Obtuse Triangle")
    if data[2]**2 < data[0]**2 + data[1]**2:
        print("Acute Triangle")
    if data[2]**2 == data[0]**2 + data[1]**2:
        print("Right Triangle") 