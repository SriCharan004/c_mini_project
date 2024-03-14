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

void registration(void);

void deleteRecord(FILE* fp, int number);

typedef struct{
    char name[50];
    int unique_number;
    int password;
    int balance; 
}user;

int isalreadyregistered(int number);
int isflightnumberthere(int number);
void booktickets(user person);