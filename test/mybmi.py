def computeBMI(weight,hight):
    if weight < 3 or weight > 200 :
        print("ERROR INPUT")
        return -1
    if hight < 0.5 or hight > 2.5:
        print("ERROR INPUT")
        return -1
        
    BMI = round(weight/(hight*hight),2)
        
    if BMI < 18.50:
        print("Underweight")
    elif 18.50 <= BMI < 24:
        print("Normal")
    elif 24.00 <= BMI < 27:
        print("Overweight")
    else:
        print("Obesity")
        
    return BMI
