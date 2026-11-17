#include <stdio.h>
#include <math.h>
#include<string>
#define READING_COUNT 5

double calculateAverage(double readings[], int count) {
    double total = 0;
    for (int i = 0; i < count; i++) total += readings[i];
    return total / count;
}
void displayReadings(double readings[], int count) {
    printf("Temperature Readings:\n");
    for (int i = 0; i < count; i++) printf("%.1f F\n", readings[i]);
}
int isOutOfRange(double temperature) {
    return (temperature > 76 || temperature < 68) ? 1 : 0;
}
void checkReadings(double readings[], int count) {
    printf("\nReadings requiring attention:\n");
    for (int i = 0; i < count; i++) {
    if (isOutOfRange(readings[i])) printf("%.1f F\n", readings[i]);
}
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
    
    unsigned int num;
    fgets(num, sizeof(num), stdin);

    displayReadings(readings, READING_COUNT);
    printf("\nAverage temperature: %.1f F\n",
    calculateAverage(readings, READING_COUNT));
    checkReadings(readings, READING_COUNT);

    return 0;
}