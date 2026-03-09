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