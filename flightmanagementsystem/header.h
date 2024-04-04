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

typedef struct{
    char name[50];
    int unique_number;
    int password;
    int balance; 
}user; // For users

typedef struct{
    char USERname[50];
    int unique_number;
    int age;
    char passengername[50];
    int flightnum;
}userbooked;


void inccapacity(int number); // Utility function to increase the capcity of the flight. 
void insertflight(FILE* fp);  // To insert a new flight record
void displayflights(FILE* fp); // to display the flight records
FILE* modifyflight(FILE* fp, int number); // to modify the flight record



void registration(void); // to register a user
void mystatus(user person, int flightnum); // to know the status of the flight that you have booked

void adminaccess();
void useraccess(void);


void displayBooked(); // to display booked flight users
void displayUsernames(); // to display registered users
FILE* deleteRecord(FILE* fp, int number); // to delete a record
void canceltickets(user person, int flightnum); // to cancel tickets
int isalreadyregistered(int number); // utility function to avoid the same registration number
int isflightnumberthere(int number); // utility function to check whether a particular flight number is there or not. 
void booktickets(user person); // function to book tickets
user getUserByName(char Name[]); // to return a user by Name
user getUserByNumber(int number);// to return a user by Number

void addbalance(user person,int value); // a utilty function to add balance to the user. When he choose to add or he cancels his flight trip or his flight is canceled
void checkmybalance(int uid); // a utilty function to check his balance
int countOccurrences(const char *name,int flightNum); // a utility function to count the number of times the name is repeated with a flight number   
// void modifyCapacityByFlightNumber(int flightNumber, int additionalCapacity);
// void increasecapacity(int number,int total);


void deductbalance(user person,int value); // utility function to deduct the balance.
void addcapacity(int total,int flightnumber); // utility functiont to add capacity of the flight
void deleteRecords(const char *userName, int flightNum); // to delete the records of the flight

void addrefund(int flightNum); // if the flight is cancelled add the refund to the users
void deletebookedusers(int flightnum);// deletes the records in booked users.