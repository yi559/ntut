def main():
    first,second,third = [],[],[]
    first.append(int(input()))
    if first[0] == 10:
        first.append(0)
        first.append("strike")
    else:
        first.append(int(input()))
        if first[0]+first[1] == 10:
            first.append("spare")
        else:
            first.append("open")

    second.append(int(input()))
    if second[0] == 10:
        second.append(0)
        second.append("strike")
    else:
        second.append(int(input()))
        if second[0]+second[1] == 10:
            second.append("spare")
        else:
            second.append("open")

    third.append(int(input()))
    if third[0] == 10:
        third.append(0)
        third.append("strike")
        third.append(int(input()))
        third.append(int(input()))
    else:
        third.append(int(input()))
        if third[0]+third[1] == 10:
            third.append("spare")
            third.append(int(input()))
            third.append(0)
        else:
            third.append("open")
            third.append(0)
            third.append(0)
#---------------------------------------------------
    if first[2] == 'strike':
        total1 = 10
        if second[2] == 'strike':
            total1 += 10 + third[0]
        else:
            total1 += second[0]+second[1]
    elif first[2] == 'spare':
        total1 = 10 + second[0]
    else:
        total1 = first[0]+first[1]

    if second[2] == 'strike':
        total2 = 10
        if third[2] == 'strike':
            total2 += 10 + third[3]
        else:
            total2 += third[0]+third[1]
    elif second[2] == 'spare':
        total2 = 10 + third[0]
    else:
        total2 = second[0]+second[1]

    if third[2] == 'strike':
        total3 = 10 + third[3] + third[4]
    elif third[2] == 'spare':
        total3 = 10 + third[3]
    else:
        total3 = third[0]+third[1]

    print(total1+total2+total3)
main()