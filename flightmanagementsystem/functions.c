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

void deleteRecord(FILE* fp, int number) {
    Flight record;
    FILE* tmpFile = tmpfile();
    rewind(fp);
    while (fread(&record, sizeof(Flight), 1, fp)) {
        if (record.Number != number) {
            fwrite(&record, sizeof(Flight), 1, tmpFile);
        }
    }
    fclose(fp);
    remove("Flights.txt");
    rename("tmpFile", "Flights.txt");
    fp = fopen("Flights.txt", "rb+");
    fclose(tmpFile);
}

void registration(void ){
    FILE *f;
    f=fopen("user.names","a+b");
    
    if(!f){return ;}
    user new;
    printf("Enter your name:");
    fgets(new.name,100,stdin);

    printf("Enter your Adhaar:");
    scanf("%d",&new.unique_number);
    
    printf("Enter your new password:");
    scanf("%d",&new.password);

    printf("Enter your balance:");
    scanf("%d",&new.balance);


    fwrite(&new, sizeof(user), 1, f);


    fclose(f);
}

int isalreadyregistered(int number){
    
    FILE *f;
    f=fopen("user.names","r");
    
    if(!f){return 0;}

    int found=0;
    user new;
    while(fread(&new,sizeof(user),1,f)==1){
        
        if(new.unique_number=number){return 1;}

    }


    fclose(f);
    return 0;
}

int isflightnumberthere(int number){ // checks if htat particular fight is there or not
    
    FILE *f;
    f=fopen("Flights.txt","r");
    
    if(!f){return 0;}

    int found=0;
    Flight new;
    while(fread(&new,sizeof(user),1,f)==1){
        
        if(new.Number=number){return 1;}

    }


    fclose(f);
    return 0;
}



void booktickets(user person){

    FILE *f;
    f=fopen("Fligth.txt","r");
    if(!f){return;}
    int num;
    displayflights();
    
    FILE *booked;
    booked=fopen("Booked.txt","a+b");
    FILE *F2=fopen("Flights.txt","r");

    Flight flight;
    int totalnum;
    printf("Enter the flight number:");
    
    scanf("%d",&num);
    
    if(!isflightnumberthere(num)){printf("Fligt Doesn't exist");}

    else{

        while(fread(&flight,sizeof(Flight),1,F2)==1){
            if(flight.Number==num){break;}
        }

        printf("How many tickets do you want?");
        scanf("%d",&totalnum);

        if(person.balance<flight.fare*totalnum){
            printf("Sorry you cannot buy the fligth tickets due to isufficient balance:");
            return;
        }
        


    }

    fclose(f);
}