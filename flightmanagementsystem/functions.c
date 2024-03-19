#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Admin
    //Add flights

void insertflight(FILE* fp) {
    Flight flightrecord;
   
    printf("Enter flight number: ");
    scanf("%d", &flightrecord.Number);

    printf("Enter the maximum capacity:");
    scanf("%d", &flightrecord.maxcapacity);
    flightrecord.capacity = flightrecord.maxcapacity;

    printf("Enter the fare:");
    scanf("%d", &flightrecord.fare);

    // Input validation for hours
    do {
        printf("Enter the hours (00-23): ");
        scanf("%d", &flightrecord.S.hours);
    } while (flightrecord.S.hours < 0 || flightrecord.S.hours > 23);

    // Input validation for minutes
    do {
        printf("Enter the minutes (00-59): ");
        scanf("%d", &flightrecord.S.min);
    } while (flightrecord.S.min < 0 || flightrecord.S.min > 59);

    // Input validation for day
    do {
        printf("Enter the day (1-31): ");
        scanf("%d", &flightrecord.S.day);
    } while (flightrecord.S.day < 1 || flightrecord.S.day > 31);

    // Input validation for month
    do {
        printf("Enter the month (1-12): ");
        scanf("%d", &flightrecord.S.month);
    } while (flightrecord.S.month < 1 || flightrecord.S.month > 12);

    // Input validation for year
    do {
        printf("Enter the year (greater than 2023): ");
        scanf("%d", &flightrecord.S.year);
    } while (flightrecord.S.year <= 2023);

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


FILE* modifyfligth(FILE* fp, int number) {
    FILE* f1;
    f1 = fopen("temp.txt", "w");
    if (f1 == NULL) {
        printf("Error in opening temporary file\n");
        return NULL;
    }

    Flight flightrecord;
    rewind(fp);

    while (fread(&flightrecord, sizeof(Flight), 1, fp)) {
        if (flightrecord.Number != number) {
            fwrite(&flightrecord, sizeof(Flight), 1, f1);
        }
        else{
            printf("Enter the schedule of the flight:\n");    
            
            printf("Enter the new hours:");
            scanf("%d",&flightrecord.S.hours);

            printf("Enter the new Minutes:");
            scanf("%d",&flightrecord.S.min);

            printf("Enter the new day:");
            scanf("%d",&flightrecord.S.day);

            printf("Enter the new month:");
            scanf("%d",&flightrecord.S.month);

            printf("Enter the new year:");
            scanf("%d",&flightrecord.S.year);

            fwrite(&flightrecord, sizeof(Flight), 1, f1);
        }
    }

    fclose(fp);  // Close the original file pointer

    fclose(f1);

    remove("Flights.txt");

    rename("temp.txt", "Flights.txt");

    FILE* modifiedFile = fopen("Flights.txt", "a+b");
    if (modifiedFile == NULL) {
        printf("Error in opening modified file\n");
        return NULL;
    }

    return modifiedFile;
}



FILE* deleteRecord(FILE* fp, int number) {

    FILE* f1;
    f1 = fopen("temp.txt", "w");
    if (f1 == NULL) {
        printf("Error in opening temporary file\n");
        return NULL;
    }

    Flight record;
    rewind(fp);

    while (fread(&record, sizeof(Flight), 1, fp)) {
        if (record.Number != number) {
            fwrite(&record, sizeof(Flight), 1, f1);
        }
    }

    fclose(fp);
    fclose(f1);

    remove("Fligths.txt");
    
    rename("temp.txt", "Fligths.txt");

    FILE* modifiedFile = fopen("Fligths.txt", "a+b");
    if (modifiedFile == NULL) {
        printf("Error in opening modified file\n");
        return NULL;
    }

    return modifiedFile;
}



int isalreadyregistered(int number) {
    FILE *f = fopen("usernames.txt", "rb");
    if (!f) {
        printf("Error opening file for checking existing users.\n");
        exit(1); // Exit program if file cannot be opened
    }

    int found = 0;
    user temp;
    while (fread(&temp, sizeof(user), 1, f) == 1) {
        if (temp.unique_number == number) {
            fclose(f);
            return 1; // User with the given unique number is already registered
        }
    }

    fclose(f);
    return 0; // User with the given unique number is not registered
}

// Function to display user information
void displayUsernames() {
    FILE *file = fopen("usernames.txt", "rb"); // Open file in binary read mode
    if (!file) {
        printf("Error opening file for display.\n");
        return;
    }

    user currentUser;
    printf("User Information:\n");
    printf("%-20s %-15s %-10s %-10s\n", "Name", "Aadhar Number", "Password", "Balance");
    printf("--------------------------------------------\n");

    while (fread(&currentUser, sizeof(user), 1, file) == 1) {
        printf("%-20s %-15d %-10d %-10d\n", currentUser.name, currentUser.unique_number, currentUser.password, currentUser.balance);
    }

    fclose(file);
}


void registration(void) {
    FILE *f = fopen("usernames.txt", "ab"); // Open file in append binary mode
    if (!f) {
        printf("Error opening file for registration.\n");
        return;
    }

    user new;
    printf("Enter your name: ");
    scanf("%s",new.name);

    
    
    do {
        printf("Enter your Aadhar number: ");
        scanf("%d", &new.unique_number);
        getchar(); // Consume newline character left in input buffer
    } while (isalreadyregistered(new.unique_number));
    

    printf("Enter your new password: ");
    scanf("%d", &new.password);

    printf("Enter your balance: ");
    scanf("%d", &new.balance);

    fwrite(&new, sizeof(user), 1, f);

    
    fclose(f);

}


int isflightnumberthere(int number){ // checks if htat particular fight is there or not
    
    FILE *f;
    f=fopen("Flights.txt","r");
    
    if(!f){return 0;}

    int found=0;
    Flight new;
    while(fread(&new,sizeof(Flight),1,f)==1){
        
        if(new.Number==number){return 1;}

    }


    fclose(f);
    return 0;
}


void reducecapacity(int number) {
    FILE *fp = fopen("Flights.txt", "r+");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    Flight flightrecord;
    int found = 0;
    while (fread(&flightrecord, sizeof(Flight), 1, fp) == 1) {
        if (flightrecord.Number == number) {
            flightrecord.capacity -= 1;

            fseek(fp, -sizeof(Flight), SEEK_CUR);
            fwrite(&flightrecord, sizeof(Flight), 1, fp);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Flight with number %d not found.\n", number);
    }

    fclose(fp);
}




void booktickets(user person) {
    FILE *f;
    f = fopen("Flights.txt", "r");
    if (!f) {
        printf("Error opening Flights.txt\n");
        return;
    }

    int num;

    

    printf("Enter the flight number to book: ");
    scanf("%d", &num);

    if (!isflightnumberthere(num)) {
        printf("Flight doesn't exist\n");
        fclose(f);
        return;
    }

    FILE *booked;
    booked = fopen("Booked.txt", "a+b");
    if (!booked) {
        printf("Error opening Booked.txt\n");
        fclose(f);
        return;
    }

    Flight flight;
    FILE *F2 = fopen("Flights.txt", "r");
    while (fread(&flight, sizeof(Flight), 1, F2) == 1) {
        if (flight.Number == num) {
            break;
        }
    }
    fclose(F2);

    int totalnum;
    printf("How many tickets do you want? ");
    scanf("%d", &totalnum);

    if (person.balance < flight.fare * totalnum) {
        printf("Sorry, you cannot buy the flight tickets due to insufficient balance.\n");
        fclose(f);
        fclose(booked);
        return;
    }

    userbooked newone;
    getchar(); // Consume newline character left in input buffer

    for (int i = 0; i < totalnum; i++) {
        strcpy(newone.USERname, person.name);

        printf("Enter the passenger name: ");
        fgets(newone.passengername, sizeof(newone.passengername), stdin);
        strtok(newone.passengername, "\n"); // Remove newline character from the name

        printf("Enter the passenger age: ");
        scanf("%d", &newone.age);

        reducecapacity(num); // Reduces the flight capacity by 1

        fwrite(&newone, sizeof(userbooked), 1, booked);
        getchar(); // Consume newline character left in input buffer
    }

    fclose(f);
    fclose(booked);
}


void inccapacity(int number) {
    FILE *fp = fopen("Flights.txt", "r+b");  // Open in read-write mode
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    Flight flightrecord;
    int found = 0;
    while (fread(&flightrecord, sizeof(Flight), 1, fp) == 1) {
        if (flightrecord.Number == number) {
            // Increment capacity
            flightrecord.capacity += 1;

            // Move the file pointer back to the beginning of the current record
            fseek(fp, -sizeof(Flight), SEEK_CUR);

            // Write the updated record back to the file
            fwrite(&flightrecord, sizeof(Flight), 1, fp);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Flight with number %d not found.\n", number);
    }

    fclose(fp);
}







// Function to cancel tickets




void canceltickets(user person, int flightnum, int total) {
    // Variables
    FILE *b, *u, *f1;
    int value = 0, found = 0;
    
    // Open files
    b = fopen("Booked.txt", "r+b");
    u = fopen("Flights.txt", "r+b");
    f1 = fopen("temp.txt", "w");

    if (!b || !u || !f1) {
        printf("Error opening files.\n");
        return;
    }

    // Update booked passengers list
    userbooked subjecttocancel;
    while (fread(&subjecttocancel, sizeof(userbooked), 1, b) == 1) {
        if (strcmp(subjecttocancel.USERname, person.name) != 0) {
            fwrite(&subjecttocancel, sizeof(userbooked), 1, f1);
        }
    }
    fclose(b);
    fclose(f1);
    remove("Booked.txt");
    rename("temp.txt", "Booked.txt");

    // Update flight capacity and fare
    f1 = fopen("temp.txt", "w");
    Flight new_flight;
    while (fread(&new_flight, sizeof(Flight), 1, u) == 1) {
        if (new_flight.Number != flightnum) {
            fwrite(&new_flight, sizeof(Flight), 1, f1);
        } else {
            inccapacity(flightnum);        
            fwrite(&new_flight, sizeof(Flight), 1, f1);
            found = 1;
            value = new_flight.fare * 90 / 100;
        }
    }
    fclose(u);
    fclose(f1);
    remove("Flights.txt");
    rename("temp.txt", "Flights.txt");

    // Add balance
    if (found) {
        addbalance(person, value);
        printf("Balance added.\n");
    }

}




void addbalance(user person,int value) { 
    user newone;
    FILE *fp;
    fp=fopen("usernames.txt","r+");
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


void mystatus(user person, int flightnum){
    FILE *u = fopen("Flights.txt", "r+b");
    if (!u) {
        printf("Error opening files.\n");
        return;
    }



    Flight flight;
    int found = 0;

    while (fread(&flight, sizeof(Flight), 1, u) == 1) {
        if (flight.Number == flightnum) {
            printf("Plane is sceduled:\n");
            printf("Flight %d Scheduled at %d:%d on %d of %d month of year %d:\n", flight.Number,flight.S.min, flight.S.hours, flight.S.day
            ,flight.S.month, flight.S.year);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Flight %d is either canceled or not scheduled.\n", flightnum);
    }

    fclose(u);
}



void adminaccess(void) {
    FILE *fp;
    fp=fopen("Flights.txt","a+b");
    if(!fp){return;}

    int admin_choice;
    int flight_number;
    int flight_to_delete;
    while (1) {
        printf("\n Admin Menu:\n");
        printf("1. Insert Flight\n");
        printf("2. Display Flights\n");
        printf("3. Modify Schedule\n");
        printf("4. Delete Flight\n");
        printf("5. Display users.txt\n");
        printf("6. Display booked passengers\n");
        printf("7. Back to Access Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &admin_choice);
        
        switch (admin_choice) {
            case 1:
                insertflight(fp);
                break;
            case 2:
                displayflights(fp);
                break;
            case 3:
                
                
                printf("Enter the flight number to modify schedule: ");
                scanf("%d", &flight_number);
                fp=modifyfligth(fp, flight_number);
                break;
            case 4:
                
                printf("Enter the flight number to delete: ");
                scanf("%d", &flight_to_delete);
                fp=deleteRecord(fp, flight_to_delete);
                break;
                
            case 5:
                printf("Printing the User details.\n");
                displayUsernames();
                break;
            case 6:
                printf("Printing the booked details.\n");
                displayBooked();
            case 7:
                return;
            default:
                printf("Invalid choice\n");
        }
    }
}

void useraccess(void) {
    FILE *fl;
    fl = fopen("Flights.txt", "ab+");
    if (!fl) {
        printf("Error opening file.\n");
        return;
    }
    int uni;
    user person;
    int value; // value of money
    int user_choice;
    int flightnum,total;
    int pass;
    int flight_number;
    printf("Please register if you didn't:\n");
    while (1) {
        printf("\n User Menu:\n");
        printf("1. Display Flights\n");
        printf("2. New Register\n");
        printf("3. Book Tickets\n");
        printf("4. Cancel Tickets\n");
        printf("5. Add Balance\n");

        
        printf("6. Print Status of flights\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &user_choice);
        
        switch (user_choice) {
            case 1:
                displayflights(fl);
                break;
            case 2:
                registration();
                break;
            case 3:
                printf("Please Enter your Unique number:");
                scanf("%d",&uni);
                if(!isalreadyregistered(uni)){
                    printf("Number not found please register:");
                    break;}
                person=getUserByNumber(uni);

                booktickets(person);
                break;
            case 4:
                printf("Please Enter your Unique number:");
                scanf("%d",&uni);
                if(!isalreadyregistered(uni)){
                    printf("Number not found please register:");
                    break;}
                person=getUserByNumber(uni);


                printf("Enter your password:");
                scanf("%d",&pass);
                if(pass==person.password){
                    
                    canceltickets(person,flightnum,total);
                    
                    printf("cancelled succesfully");
                }
                else{printf("Wrong password");}

                
                break;
            case 5:
                printf("Please Enter your Unique number:");
                scanf("%d",&uni);

                person=getUserByNumber(uni);
                printf("Enter How much do you want to add?");
                scanf("%d",&value);
                printf("Enter your password:");
                scanf("%d",&pass);
                if(pass==person.password){
                    addbalance(person,value);
                    printf("Added succesfully");
                }
                else{printf("Wrong password");}

                break;

            case 6:
                printf("Please Enter your Unique number:");
                scanf("%d",&uni);

                person=getUserByNumber(uni);
                
                printf("Enter the flight number");
                
                scanf("%d",&flight_number);

                mystatus(person,flight_number);   
                break;         
            case 7:
                fclose(fl); // Close the file before returning
                return;
            default:
                printf("Invalid choice\n");
        }
    }
}


user getUserByNumber(int number) {
    FILE *f = fopen("usernames.txt", "rb");
    if (!f) {
        printf("Error opening file for reading users.\n");
        exit(1); // Exit program if file cannot be opened
    }

    user temp;
    while (fread(&temp, sizeof(user), 1, f) == 1) {
        if (temp.unique_number == number) {
            fclose(f);
            return temp; // Return the user if found
        }
    }

    fclose(f);
    // If no user with the given unique number is found, return a user with all fields set to zero
    user emptyUser = { "", 0, 0, 0 };
    return emptyUser;
}

void displayBooked() {
    FILE *bookedFile = fopen("Booked.txt", "rb");
    if (!bookedFile) {
        printf("Error opening Booked.txt file.\n");
        return;
    }

    printf("Booked Tickets:\n");
    printf("%-20s %-20s %-10s\n", "Username", "Passenger Name", "Age");
    printf("---------------------------------------------\n");

    userbooked ticket;
    while (fread(&ticket, sizeof(userbooked), 1, bookedFile)) {
        printf("%-20s %-20s %-10d\n", ticket.USERname, ticket.passengername, ticket.age);
    }

    fclose(bookedFile);
}


