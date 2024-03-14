#include "functions.c"
#include <stdio.h>

int main() {
    FILE* fp;
    fp = fopen("Flights.txt", "ab+");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    int choice;
    
    while (1) {
        printf("\n Access Menu:\n");
        printf("1. Admin Access\n");
        printf("2. User Access\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                adminaccess(fp);
                break;
            case 2:
                useraccess();
                break;
            case 3:
                fclose(fp);
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}