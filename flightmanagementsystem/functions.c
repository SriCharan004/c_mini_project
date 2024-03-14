#include "header.h"

#include <stdio.h>
#include <string.h>

//Admin
    //Add flights

void insertflight(FILE* fp) {
    
    Flight flightrecord;
   
    printf("Enter flight number: ");
    scanf("%d", &flightrecord.Number);

    printf("Enter the maximum capacity:");
    scanf("%d",&flightrecord.maxcapacity);

    flightrecord.capacity=flightrecord.maxcapacity;

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


void reducecapacity(int number) {
    Flight flightrecord;
    FILE *fp;
    fp=fopen("Flights.txt","r+");
    while (fread(&flightrecord, sizeof(Flight), 1, fp)) {
        if (flightrecord.Number == number) {
            
            
            flightrecord.capacity=flightrecord.capacity-1;            
            

            fseek(fp, -sizeof(Flight), SEEK_CUR);
            fwrite(&flightrecord, sizeof(Flight), 1, fp);
            
            break;
        }
    }
    fclose(fp);
 }



void booktickets(user person){

    FILE *f;
    f=fopen("Fligth.txt","r");
    if(!f){return;}
    int num;
    displayflights(f);
    
    FILE *booked;
    booked=fopen("Booked.txt","a+b");//
    FILE *F2=fopen("Flights.txt","r");

    Flight flight;
    int totalnum;
    printf("Enter the flight number:");
    
    
    scanf("%d",&num);
    
    userbooked newone;
    

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
        
        int i=0;

        while(i<totalnum){
            
            strcpy(newone.USERname, person.name);
            printf("Enter the passenger name");
            fgets(newone.passengername,100,stdin);
            printf("Enter the passenger age");
            scanf("%d",&newone.age);  

            reducecapacity(num);//reduces the flight capacity by 1

            fwrite(&newone,sizeof(userbooked),1,booked);

            

        }


    }

    fclose(f);
}


void inccapacity(int number,int total) { // number is fligth number, total means total number of tickets
    Flight flightrecord;
    FILE *fp;
    fp=fopen("Flights.txt","r+");
    while (fread(&flightrecord, sizeof(Flight), 1, fp)) {
        if (flightrecord.Number == number) {
            
            
            flightrecord.capacity=flightrecord.capacity+total;            
            

            fseek(fp, -sizeof(Flight), SEEK_CUR);
            fwrite(&flightrecord, sizeof(Flight), 1, fp);
            
            break;
        }
    }
    fclose(fp);
 }





 void canceltickets(user person,int flightnum,int total){
    // Add the capacity
    // delete the names from booked;
    // add the %fare back;

    Flight usrecancel;

    FILE* tmpFile = tmpfile();

    userbooked subjecttocancel;

    FILE *b;
    FILE *u;
    b=fopen("Booked.txt","a+b");
    u=fopen("Flights.txt","r+b");
    fseek(b, 0, 0);
    int value;
    while(fread(&subjecttocancel,sizeof(userbooked),1,b)==1){
        if (subjecttocancel.USERname != person.name) {
            fwrite(&subjecttocancel, sizeof(subjecttocancel), 1, tmpFile);
        }
    }

    while(fread(&usrecancel,sizeof(Flight),1,u)==1){
        if (usrecancel.Number == flightnum) {
            value=usrecancel.fare*90/100;
            break;
        }
    }


    inccapacity(flightnum,total);
    addbalance(person,value);


    remove("Booked.txt");
    rename("tmpFile", "Booked.txt");
    fclose(tmpFile);
    fclose(b);
    fclose(u);

}


void addbalance(user person,int value) { 
    user newone;
    FILE *fp;
    fp=fopen("user.names","r+");
    while (fread(&newone, sizeof(user), 1, fp)) {
        if (newone.unique_number == person.unique_number) {
            
            
            newone.balance=newone.balance+value;            
            

            fseek(fp, -sizeof(user), SEEK_CUR);
            fwrite(&newone, sizeof(person), 1, fp);
            
            break;
        }
    }
    fclose(fp);
 }
