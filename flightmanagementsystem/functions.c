#include "header.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



void insertflight(FILE* fp) {     //Add flights

    Flight flightrecord;
    do{
    printf("Enter flight number: ");
    scanf("%d", &flightrecord.Number);
    }while(isflightnumberthere(flightrecord.Number));
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

    printf("Enter the starting location : ");
    scanf("%s",flightrecord.from);

    do{
    printf("Enter the destination : ");
    scanf("%s",flightrecord.destination);
    }while(strcmp(flightrecord.destination,flightrecord.from)==0);
    fseek(fp, 0, SEEK_END);
    fwrite(&flightrecord, sizeof(Flight), 1, fp);
}


void displayflights(FILE* fp) { // to display flights
    Flight record;
    rewind(fp);
    while (fread(&record, sizeof(Flight), 1, fp)) {
        printf("Flight Number: %d\ncapacity: %d\nFare: %d\nScheduled at %d:%d.00 on %d of %d month of the year %d from %s to %s\n", record.Number, record.capacity, record.fare,
                                record.S.hours,record.S.min,record.S.day,record.S.month,record.S.year,record.from,record.destination
        );
    }
}


FILE* modifyflight(FILE* fp, int number) { // to modify the time of the flight
    FILE* f1;
    f1 = fopen("temp.txt", "w");
    if (f1 == NULL) {
        printf("Error in opening temporary file\n");
        return NULL;
    }

    Flight flightrecord;
    rewind(fp);
    int found=0;
    while (fread(&flightrecord, sizeof(Flight), 1, fp)) {
        if (flightrecord.Number != number) {
            fwrite(&flightrecord, sizeof(Flight), 1, f1);
        }
        else {
            found=1;
            printf("Enter the schedule of the flight:\n");

            do {
                printf("Enter the new hours:");
                scanf("%d", &flightrecord.S.hours);
            } while (!(flightrecord.S.hours >= 0 && flightrecord.S.hours <= 23));

            do {
                printf("Enter the new Minutes:");
                scanf("%d", &flightrecord.S.min);
            } while (!(flightrecord.S.min >= 0 && flightrecord.S.min <= 59));

            do {
                printf("Enter the new day:");
                scanf("%d", &flightrecord.S.day);
            } while (!(flightrecord.S.day >= 0 && flightrecord.S.day <= 31));

            do {
                printf("Enter the new month:");
                scanf("%d", &flightrecord.S.month);
            } while (!(flightrecord.S.month >= 1 && flightrecord.S.month <= 12));

            do {
                printf("Enter the new year:");
                scanf("%d", &flightrecord.S.year);
            } while (!(flightrecord.S.year > 2023));

            fwrite(&flightrecord, sizeof(Flight), 1, f1);
        }
        if(found!=1){printf("Coudn't find the flight\n");}
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




FILE* deleteRecord(FILE* fp, int number) { // to delete the flight record

    FILE* f1;
    f1 = fopen("temp.txt", "w");
    if (f1 == NULL) {
        printf("Error in opening temporary file\n");
        return NULL;
    }

    Flight record;
    rewind(fp);
    int found=0;
    while (fread(&record, sizeof(Flight), 1, fp)) {
        if (record.Number != number) {
            fwrite(&record, sizeof(Flight), 1, f1);
        }
        else{
            if(record.Number == number){
                found=1;
                printf("Flight record deleted Successfully!!!\n");
            }
        }

    }
    if(found==0){
        printf("Flight is not found\n");
        }
    fclose(fp);
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



int isalreadyregistered(int number) {   // to check whether the person is already registered
    FILE *f = fopen("usernames.txt", "rb+");
    if (!f) {
        printf("Error opening file for checking existing users or the number is invalid.\n");
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
    printf("%-20s %-15s %-10s %-10s\n", "Name", "Unique Number", "Password", "Balance");
    printf("---------------------------------------------------------\n");

    while (fread(&currentUser, sizeof(user), 1, file) == 1) {
        printf("%-20s %-15d %-10d %-10d\n", currentUser.name, currentUser.unique_number, currentUser.password, currentUser.balance);
    }

    fclose(file);
}

// function to register the users
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
        printf("Enter a Unique number of your choice: ");
        scanf("%d", &new.unique_number);
        getchar(); // Consume newline character left in input buffer
    } while (isalreadyregistered(new.unique_number));
    

    printf("Enter your password: ");
    scanf("%d", &new.password);

    printf("Enter your balance: ");
    scanf("%d", &new.balance);

    fwrite(&new, sizeof(user), 1, f);

    
    fclose(f);

}

// to make sure that we are not adding flight numbers with the same number
int isflightnumberthere(int number){ // checks if that particular fight is there or not
    
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

// 
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


// void increasecapacity(int number,int total) {
//     FILE *fp = fopen("Flights.txt", "r+");
//     if (!fp) {
//         printf("Error opening file.\n");
//         return;
//     }

//     Flight flightrecord;
//     int found = 0;
//     while (fread(&flightrecord, sizeof(Flight), 1, fp) == 1) {
//         if (flightrecord.Number == number) {
//             flightrecord.capacity += total;

//             fseek(fp, -sizeof(Flight), SEEK_CUR);
//             fwrite(&flightrecord, sizeof(Flight), 1, fp);
//             found = 1;
//             break;
//         }
//     }

//     if (!found) {
//         printf("Flight with number %d not found.\n", number);
//     }

//     fclose(fp);
// }


void booktickets(user person) { // to book tickets
   
    FILE *f;
    f = fopen("Flights.txt", "r+");
    if (!f) {
        printf("Error opening Flights.txt\n");
        return;
    }

    int num;

    

    printf("Enter the flight number to book: ");
    scanf("%d", &num);

    if (!isflightnumberthere(num)) { // if that flight number does't exits
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


    int totalnum;
    printf("How many tickets do you want? ");
    scanf("%d", &totalnum);

    Flight flight;
    FILE *F2 = fopen("Flights.txt", "r");
    while (fread(&flight, sizeof(Flight), 1, F2) == 1) {
        if (flight.Number == num) {
            break;
        }
    }
    fclose(F2);


    if ((person.balance < flight.fare * totalnum) && (flight.capacity > totalnum)) { // logical test
        printf("Sorry, you cannot buy the flight tickets due to insufficient balance (or) insufficiency of avaliable tickets .\n");
        fclose(f);
        fclose(booked);
        return;
    }
    int value=flight.fare * totalnum;
    deductbalance(person,value);

    userbooked newone;
    getchar(); // Consume newline character left in input buffer

    for (int i = 0; i < totalnum; i++) {
        strcpy(newone.USERname, person.name);
        
        newone.unique_number = person.unique_number;

        printf("Enter the passenger name %d: ",i+1);
        fgets(newone.passengername, sizeof(newone.passengername), stdin);
        strtok(newone.passengername, "\n"); // Remove newline character from the name

        printf("Enter the passenger age: ");
        scanf("%d", &newone.age);

        newone.flightnum = num;


        reducecapacity(num); // Reduces the flight capacity by 1

        fwrite(&newone, sizeof(userbooked), 1, booked);
        getchar(); // Consume newline character left in input buffer
    }
    
    fclose(f);
    fclose(booked);
}


void inccapacity(int number) {
    FILE *fp = fopen("Flights.txt", "r+b");  // Open in read and then write mode
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






void deleteRecords(const char *userName, int flightNum) {
    // Open the input file for reading
    FILE *inputFile = fopen("Booked.txt", "r");
    if (!inputFile) {
        printf("Error opening input file.\n");
        return;
    }

    // Open a temporary file for writing
    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        printf("Error opening temporary file.\n");
        fclose(inputFile);
        return;
    }

    // Read records from the input file
    userbooked record;
    int recordsDeleted = 0;
    while (fread(&record, sizeof(userbooked), 1, inputFile) == 1) {
        // Check if the record matches the specified criteria
        if (strcmp(record.USERname, userName) == 0 && record.flightnum == flightNum) {
            recordsDeleted++;
        } else {
            // Write records that don't match to the temporary file
            fwrite(&record, sizeof(userbooked), 1, tempFile);
        }
    }

    // Close the files
    fclose(inputFile);
    fclose(tempFile);

    // Replace the original file with the temporary file
    remove("Booked.txt");
    rename("temp.txt", "Booked.txt");

    printf("Deleted %d records.\n", recordsDeleted);
}



void canceltickets(user person,int flightnumber) {
   
    FILE *f;
    f = fopen("Flights.txt", "r+");
    if (!f) {
        printf("Error opening Flights.txt\n");
        return;
    }

    int refund;

    Flight flight;
    while (fread(&flight, sizeof(Flight), 1, f) == 1) {
        if (flight.Number == flightnumber) {
            refund=flight.fare*9/10*countOccurrences(person.name,flightnumber); // we add only 90% of the flight fare
            break;
        }
    }

    addbalance(person,refund); // add the balance
    deleteRecords(person.name,flightnumber); // delete that record
    fclose(f);
}








void addbalance(user person,int value) {  // to add balance
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

void addcapacity(int total, int flightnumber) {  // to add capacity after canceling the fight tickets
    Flight flight;

    FILE *fp;
    fp = fopen("Flights.txt", "r+");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&flight, sizeof(Flight), 1, fp) == 1) {
        if (flight.Number == flightnumber) {
            flight.capacity += total;            

            fseek(fp, -sizeof(Flight), SEEK_CUR);
            fwrite(&flight, sizeof(Flight), 1, fp);
            
            break;
        }
    }
    
    fclose(fp);
}


void deductbalance(user person,int value) {  // to deduce the user balance  after buying the tickets
    user newone;
    FILE *fp;
    fp=fopen("usernames.txt","r+");
    while (fread(&newone, sizeof(user), 1, fp)) {
        if (newone.unique_number == person.unique_number) {
            
            
            newone.balance=newone.balance-value;            
            

            fseek(fp, -sizeof(user), SEEK_CUR);
            fwrite(&newone, sizeof(person), 1, fp);
            
            break;
        }
    }
    fclose(fp);
 }

void mystatus(user person, int flightnum){ // to print the status of his booked flight
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
            printf("Flight %d Scheduled at %d:%d on %d of %d month of year %d from %s to %s:\n", flight.Number,flight.S.min, flight.S.hours, flight.S.day
            ,flight.S.month, flight.S.year,flight.from,flight.destination);
            
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Flight %d is either cancelled or not scheduled, if cancelled the refund is already added\nOr either you have not booked the flight\n", flightnum);
    }

    fclose(u);
}


int countOccurrences(const char *name,int flightNum){ // to count how many times a name is repeated uder a particular flight number
    FILE *file = fopen("Booked.txt", "rb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return -1; // Error opening file
    }

    userbooked record;
    int count = 0;
    while (fread(&record, sizeof(userbooked), 1, file) == 1) {
        if ((strcmp(record.USERname, name) == 0) && record.flightnum==flightNum) {
            count++;
        }
    }

    fclose(file);
    return count;
}


void deletebookedusers(int flight_number){ // to delete the booked users after flight gets canceled
    FILE *fp,*temp;

    fp=fopen("Booked.txt","r");
    temp=fopen("temp.txt","w");

    if(!(fp && temp)){
        return;
    }

    userbooked record;



    while((fread(&record,sizeof(userbooked),1,fp)==1)){
        if(record.flightnum != flight_number){
            fwrite(&record,sizeof(userbooked),1,temp);
        }

    }
    remove("Booked.txt");
    rename("temp.txt", "Booked.txt");

    fclose(fp);
    fclose(temp);



}



user getUserByNumber(int number) { // to get user by number
    FILE *f = fopen("usernames.txt", "r+b");
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
    printf("Returning Empty user as the user-id is not found\n");
    return emptyUser;
}

void displayBooked() { // to display the booked passengers
    FILE *bookedFile = fopen("Booked.txt", "rb");
    if (!bookedFile) {
        printf("Error opening Booked.txt file.\n");
        return;
    }

    printf("Booked Tickets:\n");
    printf("%-20s %-20s %-20s %-10s %-10s\n", "Username", "unique id", "Passenger Name", "Age", "Flight Number");
    printf("-------------------------------------------------------------------------------------\n");


    userbooked ticket;
    while (fread(&ticket, sizeof(userbooked), 1, bookedFile)) {
        printf("%-20s %-20d %-20s %-10d %-10d\n", ticket.USERname,ticket.unique_number, ticket.passengername, ticket.age ,ticket.flightnum);
    }

    fclose(bookedFile);
}


user getUserByName(char Name[]) { // a utility function to get user by his name
    FILE *f = fopen("usernames.txt", "rb");
    if (!f) {
        printf("Error opening file for reading users.\n");
        exit(1); // Exit program if file cannot be opened
    }

    user temp;
    while (fread(&temp, sizeof(user), 1, f) == 1) {
        if (temp.name == Name) {
            fclose(f);
            return temp; // Return the user if found
        }
    }

    fclose(f);
    // If no user with the given unique number is found, return a user with all fields set to zero
    user emptyUser = { "", 0, 0, 0 };
    return emptyUser;
}

void checkmybalance(int uid){ // a utility function to check the balance of user buy taking his user id
    
    FILE *f1=fopen("usernames.txt","rb");
    
    if(!f1){printf("Could't open\n");
    return;
    }
    
    int id=uid,pass;
    user person = getUserByNumber(uid);

    while(fread(&person,sizeof(user),1,f1)==1){
        
        if(person.unique_number==id){
            printf("Enter your password:");
            scanf("%d",&pass);
                if(pass==person.password){
                    printf("\nYour current balance is %d\n",person.balance);
                    return;
                }
                else{
                    printf("Wrong user id or password\n");
                    return;
                }
            }
        } 
    printf("User not found\n");
}
    



void addrefund(int flightNum){ // to add refund if the flight gets cancled

    FILE *booked;
    booked=fopen("Booked.txt", "rb");
    if (!booked) {
        printf("Error opening Booked.txt file.\n");
        return;
    }
    int price=0;
    
    userbooked record;
    user person;
    
    Flight flight;
    FILE *f;
    f=fopen("Flights.txt","rb");
    if(!f){
        return;
    }
    
    while(fread(&flight,sizeof(Flight),1,f)==1){
        
        if(flight.Number==flightNum){
            price=flight.fare;
            break;
        }

    }

    int freq;

    while(fread(&record,sizeof(userbooked),1,booked)==1){
        
        if(record.flightnum==flightNum){
               
               person = getUserByNumber(record.unique_number);
               addbalance(person,price+100);
               printf("Refund Added successfully\n");
        }

    }


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
                fp=modifyflight(fp, flight_number);
                break;
            case 4:
                
                printf("Enter the flight number to delete: ");
                scanf("%d", &flight_to_delete);
                addrefund(flight_to_delete);// adds the refund to users
                fp=deleteRecord(fp, flight_to_delete);
                deletebookedusers(flight_to_delete); // deletes the record in the Booked.txt
                break;
                
            case 5:
                printf("Printing the User details.\n");
                displayUsernames();
                break;
            case 6:
                printf("Printing the booked details.\n");
                
                displayBooked();
                break;
            case 7:
                return;
            default:
                printf("\n Invalid choice\n");
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
    int freq;
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
        printf("7. Check your balance\n");
        printf("8. Back to Access Menu\n");
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

                printf("Enter your password:");
                scanf("%d",&pass);

                if(!(person.password==pass)){
                    printf("Wrong Password or not registered\n");
                    break;
                }        
                booktickets(person);
                break;
            case 4:
                printf("Please Enter your Unique number:");
                scanf("%d",&uni);
                if(!isalreadyregistered(uni)){
                    printf("Number not found please register:");
                    break;
                    }
                
                person=getUserByNumber(uni);
                
                printf("Enter the flight number:");
                scanf("%d",&flightnum);
                
                if(!isflightnumberthere(flightnum)){
                    printf("Flight doesn't exist.\n");
                    break;
                }
                freq=countOccurrences(person.name,flightnum);
                

                printf("Enter your password:");
                scanf("%d",&pass);
                if(pass==person.password){
                    
                    canceltickets(person,flightnum);
                    addcapacity(freq,flightnum);
                   
                    
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
                    printf("Amount Added succesfully");
                }
                else{printf("Wrong password or wrong user id");}

                break;

            case 6:
                printf("Please Enter your Unique number:");
                scanf("%d",&uni);

                person=getUserByNumber(uni);

                printf("Enter your password:");
                scanf("%d",&pass);
                if(!(pass==person.password)){
                    printf("Wrong Password");
                    break;
                }
                
                printf("Enter the flight number : ");
                
                scanf("%d",&flight_number);

                mystatus(person,flight_number);   
                break;         
            case 7:
                printf("Please Enter your Unique number:");
                scanf("%d",&uni);

                if(isalreadyregistered(uni)){
                    checkmybalance(uni);
                    }
                else{
                    printf("Not registered");
                    }                
                break;         


            case 8:
                fclose(fl); // Closing the file before returning
                return;
            default:
                printf("\n Invalid choice\n");
        }
    }
}