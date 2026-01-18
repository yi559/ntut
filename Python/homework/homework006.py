import math

a = int(input())
b = int(input())
c = int(input())
total = 0

def number(x):
    if 1<= x <=10:
        return [1,1,1]
    elif 11<= x <=20:
        return [0.9,0.95,0.85]
    elif 21<= x <=30:
        return [0.85,0.85,0.8]
    else:
        return [0.8,0.8,0.7]


h = number(a)
total = total + 380*h[0]*a
h = number(b)
total = total + 1200*h[1]*b
h = number(c)
total = total + 180*h[2]*c

print(math.ceil(total))