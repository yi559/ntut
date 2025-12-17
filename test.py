name = input("請輸入姓名:")
hight = int(input("請輸入身高:")) / 100
waight = int(input("請輸入體重:"))

bmi = waight / (hight * hight)

if bmi < 18.5:
    print(f"您的姓名{name}，您的BMI: {bmi:.2f}，體重過輕，請注意健康")
elif 18.5 <= bmi < 24:
    print(f"您的姓名{name}，您的BMI: {bmi:.2f}，體重正常")
elif 24 <= bmi < 27:
    print(f"您的姓名{name}，您的BMI: {bmi:.2f}，體重過重，請注意健康")
elif 27 <= bmi < 30:
    print(f"您的姓名{name}，您的BMI: {bmi:.2f}，輕度肥胖，請注意健康")
elif 30 <= bmi < 35:
    print(f"您的姓名{name}，您的BMI: {bmi:.2f}，中度肥胖，請注意健康")
elif bmi >= 35:
    print(f"您的姓名{name}，您的BMI: {bmi:.2f}，重度肥胖，請注意健康")