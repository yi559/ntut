import math

a = int(input())
b = int(input())
c = int(input())

d =  b*b-4*a*c
real = -b/(2*a)
nombre = abs(math.sqrt(abs(d))/(2*a))

if (d < 0):
    print('%.1f'%real + '+%.1f'%nombre + 'i')
    print('%.1f'%real + '-%.1f'%nombre + 'i')
else:
    x1 = ((-b) + math.sqrt(b*b-4*a*c)) / (2*a)
    x2 = ((-b) - math.sqrt(b*b-4*a*c)) / (2*a)
    if x1 == x2:
        print('%.1f'%x1)
    else:
        print('%.1f'%x1)
        print('%.1f'%x2)

