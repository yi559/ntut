#include <stdio.h>

int main(void) {
    int type[3] = {183, 383, 983};
    
    int free_quotas[3][5] = {
        {500, 400, 300, 10, 15},
        {600, 500, 400, 20, 25},
        {700, 600, 500, 30, 35}
    };
    
    float rates[3][5] = {
        {0.08, 0.1393, 0.1349, 1.1287, 1.4803},
        {0.07, 0.1304, 0.1217, 1.1127, 1.2458},
        {0.06, 0.1087, 0.1018, 0.9572, 1.1243}
    };

    int data[5];
    for (int i = 0; i < 5; i++) scanf("%d", &data[i]);

    float min_cost = 1e9;
    int best_type = 0;

    for (int i = 0; i < 3; i++) {
        float current_over_fee = 0;
        
        for (int j = 0; j < 5; j++) {
            if (data[j] > free_quotas[i][j]) {
                current_over_fee += (data[j] - free_quotas[i][j]) * rates[i][j];
            }
        }

        float final_price = (current_over_fee < type[i]) ? type[i] : current_over_fee;

        if (final_price < min_cost) {
            min_cost = final_price;
            best_type = type[i];
        }
    }

    printf("%d\n%d\n", (int)min_cost, best_type);
    return 0;
}