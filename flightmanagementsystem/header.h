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

    char from[100];
    char destination[100];

}Flight;

void inccapacity(int number);
void insertflight(FILE* fp);
void displayflights(FILE* fp);

FILE* modifyflight(FILE* fp, int number);

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
    int unique_number;
    int age;
    char passengername[50];
    int flightnum;

}userbooked;

void displayBooked();
void displayUsernames();

FILE* deleteRecord(FILE* fp, int number);
void canceltickets(user person, int flightnum);
int isalreadyregistered(int number);
int isflightnumberthere(int number);
void booktickets(user person);
user getUserByName(char Name[]);

void adminaccess();
user getUserByNumber(int number);
void addbalance(user person,int value);

void useraccess(void);

int countOccurrences(const char *name,int flightNum);
void modifyCapacityByFlightNumber(int flightNumber, int additionalCapacity);
void increasecapacity(int number,int total);


void deductbalance(user person,int value);

void addcapacity(int total,int flightnumber);


void deleteRecords(const char *userName, int flightNum);

void addrefund(int flightNum); // if the flight is cancelled add the refund to the users