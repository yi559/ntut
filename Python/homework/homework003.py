
name = str(input())
number = int(input())
ch = int(input())
ct = int(input())
cp = int(input())
total = ch+ct+cp
av = int(total/3)

str='Name:{NAME}\n' \
    'Id:{ID}\n' \
    'Total:{TOTAL}\n' \
    'Average:{AV}'.format(
    NAME = name,
    ID = number,
    TOTAL = total,
    AV = av

)
print(str)