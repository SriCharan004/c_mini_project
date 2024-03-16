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
    int maxcapacity;
    int capacity;
    int fare;

    schedule S;

}Flight;


void insertflight(FILE* fp);
void displayflights(FILE* fp);

FILE* modifyfligth(FILE* fp, int number);

void registration(void);

typedef struct{
    char name[50];
    int unique_number;
    int password;
    int balance; 
}user;

typedef struct{
    char USERname[50];
    int age;
    char passengername[50];


}userbooked;


FILE* deleteRecord(FILE* fp, int number);
void addbalance(user person,int value);
void canceltickets(user person,int flightnum,int total);

int isalreadyregistered(int number);
int isflightnumberthere(int number);
void booktickets(user person);


void adminaccess();

void useraccess(void);