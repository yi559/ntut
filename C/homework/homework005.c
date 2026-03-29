/*
005. 最佳資費選擇
輸入每月網內、網外、市話、通話時間(秒)及網內、網外簡訊則數，求花費最少的資費類型。

費率如下表：
資費類型 183型 383型 983型
月租費 183元 383元 983元

免費額度
通話時間
(秒) 網內 500 600 700
(秒) 網外 400 500 600
(秒) 市話 300 400 500
簡訊數量
(則) 網內 10 20 30
(則) 網外 15 25 35

語音費率 網內 0.08 0.07 0.06
(元/秒) 網外 0.1393 0.1304 0.1087
(元/秒) 市話 0.1349 0.1217 0.1018

簡訊費率 網內 1.1287 1.1127 0.9572
(元/則) 網外 1.4803 1.2458 1.1243

優惠內容
1. 每個資費方案都有各自的「免費通話時間」和「免費簡訊數量」額度：
當用戶的通話時間或簡訊數量超過免費額度時，則超過的額度按費率進行收費。
例如：
選擇183型，使用網內語音1800秒，以超過額度計算金額：(1800-500) * 0.08。
2. 月租費可抵等額通信費 :
若總通信費(包含通話時間、簡訊數量)高於該資費類型的費用，則以原費用進行收費，若低於該資費類型的費用，則以該資費類型的費用進行收費。
例如:
選擇183型，總通信費為200元，則應繳金額為200元
若總通信費為150元，則應繳金額為183元。

【輸入說明】
第一行，輸入網內語音(秒, Integer)、網外語音(秒, Integer)、輸入市話(秒, Integer)、輸入內簡訊數(則, Integer)、輸入網外簡訊數(則, Integer)
每個數字以空格作區隔

範例輸入說明:
Sample Input:
500 120 130 20 50


【輸出說明】
第一行，輸出最佳費用(無條件捨去至Integer)
第二行，輸出最佳資費類型，(183, 383, 983)

範例輸出說明:
Sample Output:
183
183

【測試資料一】
輸入：
900 600 500 70 30

輸出：
183
183

【測試資料二】
輸入：
1500 2200 980 60 80

輸出：
468
383

【測試資料三】
輸入：
1000 1800 500 80 100

輸出：
383
383

【測試資料四】
輸入：
2190 3785 1850 100 180

輸出：
983
983

【測試資料五】
輸入：
5000 4500 300 200 200

輸出：
1030
983

【測試資料六】
輸入：
500 500 500 10 10

輸出：
183
183
*/

#include <stdio.h>

int main(void){
    int type[3] = {183,383,983};
    int price[3] = {183,383,983};
    int fvin[3] = {500,600,700}; //free_voice_in_network
    int fvon[3] = {400,500,600}; //free_voice_out_network
    int fvlp[3] = {300,400,500}; //free_voice_local_phone
    int fmin[3] = {10,20,30}; //free_mes_in_network
    int fmon[3] = {15,25,35}; //free_mes_out_network
    float vpin[3] = {0.08,0.07,0.06}; //voice_price_in_network
    float vpon[3] = {0.1393,0.1304,0.1087}; //voice_price_out_network
    float vplp[3] = {0.1349,0.1217,0.1018}; //voice_price_local_phonep
    float mpin[3] = {1.1287,1.1127,0.9572}; //mes_price_in_network
    float mpon[3] = {1.4803,1.2458,1.1243}; //mes_price_out_network

    int data[5] = {0,0,0,0,0}; //in_network_voice,out_network_voice,local_phone,in_mes,out_mes
    for (int i=0 ; i<5 ; i++){
        scanf("%d", &data[i]);
    }
    
    float total_price[3] = {0,0,0};
    for (int i=0 ; i<3 ; i++){
        float ovpin = 0; //over_voice_price_in_network
        float ovpon = 0; //over_voice_price_out_network
        float ovplp = 0; //over_voice_price_local_phone
        float ompin = 0; //over_mes_price_in_network
        float ompon = 0; //over_mes_price_out_network

        if (data[0] > fvin[i]) ovpin = (data[0] - fvin[i]) * vpin[i];
        if (data[1] > fvon[i]) ovpon = (data[1] - fvon[i]) * vpon[i];
        if (data[2] > fvlp[i]) ovplp = (data[2] - fvlp[i]) * vplp[i];
        if (data[3] > fmin[i]) ompin = (data[3] - fmin[i]) * mpin[i];
        if (data[4] > fmon[i]) ompon = (data[4] - fmon[i]) * mpon[i];

        total_price[i] = ovpin+ovpon+ovplp+ompin+ompon;
        if (total_price[i] < price[i]){
            total_price[i] = price[i];
        }
    }
    int min = total_price[0];
    int tag = 0;
    for (int i=1; i<3 ; i++){
        if (total_price[i] < min){
            min = total_price[i];
            tag = i;
        }
    }

    printf("%d\n", min);
    printf("%d", type[tag]);
    return 0;
}