InsideVoice = int(input())
OutsideVoice = int(input())
LocalCall = int(input())
InsideMes = int(input())
OutsideMes = int(input())

VoiceRatesInside = [0.08 , 0.07 , 0.06]
VoiceRatesOutside = [0.1393 , 0.1304 , 0.1087]
VoiceRatesLocalcall = [0.1349 , 0.1217 , 0.1018]
MesRatesInside = [1.1287 , 1.1127 , 0.9572]
MesRatesOutside = [1.4803 , 1.2458 , 1.1243]

CommunicationPrice = [0,0,0]

for i in range(3):
    CommunicationPrice[i] = InsideVoice * VoiceRatesInside[i] + OutsideVoice * VoiceRatesOutside[i] + LocalCall * VoiceRatesLocalcall[i] + InsideMes * MesRatesInside[i] + OutsideMes * MesRatesOutside[i]

if CommunicationPrice[0] < 183:
    print("183")
    print("183")
else:
    if CommunicationPrice[1] < 383:
        if CommunicationPrice[1] < 383 and CommunicationPrice[0] < 383:
            print(int(CommunicationPrice[0]))
            print("183")
        else:
            print("383")
            print("383")
    else:
        if CommunicationPrice[2] < 983 and CommunicationPrice[1] < 983:
            print(int(CommunicationPrice[1]))
            print("383")
        elif CommunicationPrice[2] < 983:
            print("983")
            print("983")
        else:
            print(int(CommunicationPrice[2]))
            print("983")