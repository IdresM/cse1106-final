#include <stdio.h>
#include <math.h>
#include<stdlib.h>
#include <unistd.h>
#include <pigpio.h>
#define PIN 17

int minimumTemp = 68;
int maximumTemp = 76;

void ledWarning(){
   
    gpioWrite(PIN, 1);
    getchar();
    gpioWrite(PIN,0);
}
int isOutOfRange(int temperature) {
    return (temperature > maximumTemp || temperature < minimumTemp) ? 1 : 0;
}
int calculateAverage(int* readings, int count) {
    double total = 0;
    for (int i = 0; i < count; i++) {
        total += readings[i];
    }
    return total / count;
}

void displayReadings(int* readings, int count) {
    printf("Temperature System Status Warning LED\n");
    for (int i = 0; i < count; i++) {
        printf("%9d F", readings[i]);
        if(isOutOfRange(readings[i])){
            printf(" WARNING       ");
        }
        else{
            printf(" NORMAL        ");
       }
       if(isOutOfRange(readings[i])) { printf("ON\n"); ledWarning();}
       else{printf("OFF\n");}
    }
}

void user_input(int n, int a[]) {

    for(int i = 0; i < n; i++){
        printf("Enter the %d temperature: ", i+1);
        scanf("%d", &a[i]);
    }
    
    return;
}


void storedata(int* temp, int count){
    FILE* fp = fopen("temp_data.txt", "a");
    for(int i = 0; i < count; i++){
        fprintf( fp, "%d F ", temp[i]);
        if(isOutOfRange(temp[i])){ fprintf(fp, "%s\n", "WARNING");}
        else{fprintf(fp, "%s\n", "NORMAL");}
    }
    fclose(fp);
}

void changeAcceptedRange(){
    int a;
    int b;
    scanf("Enter the new minimum temperature: %d\n", &a);
    scanf("Enter the new maximum temperature: %d\n", &b);
    minimumTemp = a;
    maximumTemp = b;
}

/*void test_T1_normalTemperature(void) {
    double temperature = 75.0;
    recordTest("T1 - 75 F is within the acceptable range",
    isOutOfRange(temperature) == 0);
}

void test_T2_belowMinimum(void) {
    double temperature = 64.0;
    recordTest("T2 - 64 F requires attention",
    isOutOfRange(temperature) == 1);
}

void test_T3_aboveMaximum(void) {
    double temperature = 76.0;
    recordTest("T3 - 76 F requires attention",
    isOutOfRange(temperature) == 1);
}*/

int main(void) {
    printf("========================================\n");
    printf("SMART CLASSROOM COMFORT MONITOR\n");
    printf("========================================\n\n");
    printf("How many temperature readings you want to enter?\n");
    gpioInitialise();
    gpioSetMode(PIN, PI_OUTPUT);
    
    int num;
    scanf("%d", &num);
    int a[num];

    user_input(num, a);

    displayReadings(a, num);
    printf("\nAverage temperature: %d F\n", calculateAverage(a, num));
    storedata(a, num);
    changeAcceptedRange();

    return 0;
}
