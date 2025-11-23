def main():
    people = int(input())#總共人口
    day = int(input())#模擬天數
    first_confirmed = int(input())#第一天感染人數
    infect = float(input())#確診者一天感染人數
    rehabilitation = int(input())#康復天數
    immunity = float(input())#免疫率

    toltoInfectPeople = 0 #總共確診人數
    nowRehabilitationPeople = int(people * immunity) #目前免疫人數
    startRehabilitationPeople = int(people * immunity) #剛開始免疫人數

    data = [[0 for _ in range(3)] for _ in range(day+1)] #總確診人數,新增確診人數,康復人數
    data[1] = [first_confirmed,first_confirmed,0] #初始化第一天
    toltoInfectPeople += first_confirmed #新增總確診人數
    
    for i in range(2,day+1):
        nowInfect = int(((infect / rehabilitation) * (1-immunity))*data[i-1][0]) #計算今天確診人數

        if toltoInfectPeople+startRehabilitationPeople+nowInfect > people: #如果超過人數，就全部剪掉剩下
            nowInfect = people-toltoInfectPeople-startRehabilitationPeople

        data[i][1] = nowInfect #儲存每天新增確診人數

        if i-rehabilitation > 0: #如果天數大於康復天數，開始康復
            data[i][2] = data[i-rehabilitation][1] #儲存每天新增康復人數
            nowRehabilitationPeople += data[i][2] #儲存目前免疫人數

        immunity = nowRehabilitationPeople/people #計算免疫率
        data[i][0] = data[i-1][0] - data[i][2] + data[i][1] #儲存至今確診人數
        toltoInfectPeople += data[i][1] #儲存總確診人數
    
    for i in range(1,day+1):
        print(f"{i} {data[i][0]:.0f} {data[i][1]:.0f} {data[i][2]:.0f}")
    print(int(toltoInfectPeople))
main()