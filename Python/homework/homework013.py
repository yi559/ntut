def year(x:int):
    if (x%4 == 0 and x%100 != 0) or x%400 == 0:
        print('Leap Year')
    else:
        print('Common Year')

def main():
    a = int(input())
    b = int(input())

    year(a)
    year(b)
main()