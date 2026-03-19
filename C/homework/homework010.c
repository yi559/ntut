#include <stdio.h>
#include <math.h>

int trans10(int data){
    int num = 0,rem;
    int weight = 1;

    while (data > 0) {
        rem = data % 10;
        num += rem * weight;
        data /= 10;
        weight *= 2;
    }
    return num;
}

int c(int times,int m){
    if (m == 0 || m == 1) return times;
    
    times += 1;
    if (m % 2 == 0){
        return c(times, m / 2);
    }else{ 
        return c(times, (m + 1) / 2);
    }
}

int trans2(int data){
    int num = 0;
    int weight = 1;
    while (data > 0) {
        num += (data % 2) * weight;
        data /= 2;
        weight *= 10;
    }
    return num;
}

int main(void){
    while(1){
        int data = 0;
        scanf("%d", &data);
        if (data == -1) break;

        data = trans10(data);
        printf("%04d\n", trans2(c(0,data)));
    }
    return 0;
}