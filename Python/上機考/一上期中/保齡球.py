def main():
    onefirstpoint = int(input())
    onesecpoint = 0
    if onefirstpoint != 10:
        onesecpoint = int(input())
        
    twofirstpoint = int(input())
    twosecpoint = 0
    if twofirstpoint != 10:
        twosecpoint = int(input())

    threefirstpoint = int(input())
    threesecpoint = 0
    if threefirstpoint != 10:
        threesecpoint = int(input())
    if threefirstpoint+threesecpoint == 10:
        oneexpoint = int(input())
    if threefirstpoint == 10:
        twoexpoint = int(input())
    
    #one
    onepoint = 0
    if onefirstpoint == 10:
        if twofirstpoint == 10:
            onepoint += onefirstpoint + twofirstpoint + threefirstpoint
        else:
            onepoint += onefirstpoint + twofirstpoint + twosecpoint
    elif onefirstpoint + onesecpoint == 10:
        onepoint += 10 + twofirstpoint
    else:
        onepoint += onefirstpoint +onesecpoint
    #two
    twopoint = 0
    if twofirstpoint == 10:
        if threefirstpoint == 10:
            twopoint += twofirstpoint + threefirstpoint + oneexpoint
        else:
            twopoint += twofirstpoint + threefirstpoint + threesecpoint
    elif twofirstpoint + twosecpoint == 10:
        twopoint += 10 + threefirstpoint
    else:
        twopoint += twofirstpoint + twosecpoint
    #three
    threepoint = 0
    if threefirstpoint == 10:
        threepoint += threefirstpoint + oneexpoint + twoexpoint
    elif threefirstpoint + threesecpoint == 10:
        threepoint += 10 + oneexpoint
    else:
        threepoint += threefirstpoint + threesecpoint
    print(onepoint+twopoint+threepoint)

main()