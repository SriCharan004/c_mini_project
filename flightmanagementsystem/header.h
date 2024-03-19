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

void inccapacity(int number);
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



void mystatus(user person, int flightnum);

typedef struct{
    char USERname[50];
    int age;
    char passengername[50];


}userbooked;

void displayBooked();
void displayUsernames();

FILE* deleteRecord(FILE* fp, int number);
void addbalance(user person,int value);
void canceltickets(user person, int flightnum);
int isalreadyregistered(int number);
int isflightnumberthere(int number);
void booktickets(user person);


void adminaccess();
user getUserByNumber(int number);
void useraccess(void);

int countOccurrences(const char *name);
void modifyCapacityByFlightNumber(int flightNumber, int additionalCapacity);