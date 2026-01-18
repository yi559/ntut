import math
def myfuntion(x:int,a:int,b:int):
    pi = math.pi
    if x == 1:
        return(4*a)
    elif x == 2:
        return(2*pi*a)
    elif x == 3:
        return(2*(a+b))
    
def main():
    x = int(input("請輸入要計算的圖形  square:1 OR circle:2 OR rectangle:3 =>"))
    a = int(input("請輸入長或是半徑"))
    b = int(input("請輸入寬"))
    ans = myfuntion(x,a,b)
    print(f"{ans:.2f}")
main()