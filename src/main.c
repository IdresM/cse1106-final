#include <stdio.h>
#include <math.h>
#include<stdlib.h>

int minimumTemp = 68;
int maximumTemp = 76;

int calculateAverage(int* readings, int count) {
    double total = 0;
    for (int i = 0; i < count; i++) {
        total += readings[i];
    }
    return total / count;
}

void displayReadings(int readings[], int count) {
    printf("Temperature System Status Warning LED\n");
    for (int i = 0; i < count; i++) {
        printf("%9d F", readings[i]);
        if(isOutOfRange(readings[i])){
            printf(" WARNING       ");
        }
        else{
            printf(" NORMAL        ");
       }
       if(isOutOfRange(readings[i])) { printf("ON\n");}
       else{printf("OFF\n");}
    }
}

int* user_input(unsigned int n) {
    int* input_ptr = (int*) calloc(n, sizeof(int));
    if (input_ptr == NULL) {
        return NULL;
    }

    for(int i = 0; i < n; i++){
        scanf("%d", input_ptr + i);
    }
    return input_ptr;
}
int isOutOfRange(int temperature) {
    return (temperature > maximumTemp || temperature < minimumTemp) ? 1 : 0;
}

void test_T1_normalTemperature(void) {
    double temperature = 75.0;
    recordTest("T1 - 75 F is within the acceptable range",
    isOutOfRange(temperature) == 0);
}
/* T2: 64 F is below the minimum and should require attention. */
void test_T2_belowMinimum(void) {
    double temperature = 64.0;
    recordTest("T2 - 64 F requires attention",
    isOutOfRange(temperature) == 1);
}
/* T3: 78.5 F is above the maximum and should require attention. */
void test_T3_aboveMaximum(void) {
    double temperature = 76.0;
    recordTest("T3 - 76 F requires attention",
    isOutOfRange(temperature) == 1);
}
int main(void) {
    printf("========================================\n");
    printf("SMART CLASSROOM COMFORT MONITOR\n");
    printf("========================================\n\n");
    printf("How many temperature readings you want to enter?\n");
    
    
    int num;
    scanf("%d", &num);

    int* tempInput = user_input(num);

    displayReadings(user_input, num);
    printf("\nAverage temperature: %d F\n", calculateAverage(tempInput, num));
    checkReadings(readings, READING_COUNT);

    free(tempInput);
    return 0;
}