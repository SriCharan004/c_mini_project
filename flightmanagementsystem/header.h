#include <stdio.h>

typedef struct{
    
    int hours;
    int min;
    int day;
    int month;
    int year;

}schedule;

typedef struct {
    int Number;
    int capacity;
    int fare;

    schedule S;

}Flight;


void insertflight(FILE* fp);
void displayflights(FILE* fp);

void modifyschedule(FILE* fp, int number);