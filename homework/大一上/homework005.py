def main():
    h = float(input())
    w = int(input())

    bmi = w / (h ** 2)

    if bmi < 18:
        print('Underweight')
    elif 18 <= bmi < 24:
        print('Normal')
    elif 24 <= bmi < 27:
        print('Overweight')
    elif 27 <= bmi < 30:
        print('Mild obesity')
    elif 30 <= bmi < 35:
        print('Moderate obesity')
    else:
        print('Severe obesity')

main()