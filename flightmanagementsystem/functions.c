#include "header.h"

#include <stdio.h>

//Admin
    //Add flights

void insertflight(FILE* fp) {
    
    Flight flightrecord;
   
    printf("Enter flight number: ");
    scanf("%d", &flightrecord.Number);

    printf("Enter the maximum capacity:");
    scanf("%d",&flightrecord.capacity);

    printf("Enter the fare:");
    scanf("%d",&flightrecord.fare);


    printf("Enter the schedule of the flight:\n");    
    
    printf("Enter the hours:");
    scanf("%d",&flightrecord.S.hours);

    printf("Enter the Minutes:");
    scanf("%d",&flightrecord.S.min);

    printf("Enter the day:");
    scanf("%d",&flightrecord.S.day);

    printf("Enter the month:");
    scanf("%d",&flightrecord.S.month);

    printf("Enter the year:");
    scanf("%d",&flightrecord.S.year);



    fseek(fp, 0, SEEK_END);
    fwrite(&flightrecord, sizeof(Flight), 1, fp);
}

void displayflights(FILE* fp) {
    Flight record;
    rewind(fp);
    while (fread(&record, sizeof(Flight), 1, fp)) {
        printf("Flight Number: %d\ncapacity: %d\nFare: %d\nScheduled at %d:%d.00 on %d of %d month of the year %d\n", record.Number, record.capacity, record.fare,
                                record.S.hours,record.S.min,record.S.day,record.S.month,record.S.year
        );
    }
}

void modifyschedule(FILE* fp, int number) {
    Flight flightrecord;
    int found = 0;
    rewind(fp);
    while (fread(&flightrecord, sizeof(Flight), 1, fp)) {
        if (flightrecord.Number == number) {
            printf("Enter the schedule of the flight:\n");    
            
            printf("Enter the hours:");
            scanf("%d",&flightrecord.S.hours);

            printf("Enter the Minutes:");
            scanf("%d",&flightrecord.S.min);

            printf("Enter the day:");
            scanf("%d",&flightrecord.S.day);

            printf("Enter the month:");
            scanf("%d",&flightrecord.S.month);

            printf("Enter the year:");
            scanf("%d",&flightrecord.S.year);


            fseek(fp, -sizeof(Flight), SEEK_CUR);
            fwrite(&flightrecord, sizeof(Flight), 1, fp);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Record with Flight number %d not found\n", number);
    }
}