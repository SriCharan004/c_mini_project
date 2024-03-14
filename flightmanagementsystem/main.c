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
                insertflight(fp);
                break;
            case 2:
                
                displayflights(fp);
                break;
            case 3:
                // printf("Enter registration number of student to modify GPA: ");
                // scanf("%d", &regdNo);
                // printf("Enter new GPA: ");
                // scanf("%f", &gpa);
                // modifyRecord(fp, regdNo, gpa);
                break;
            case 4:
                // printf("Enter registration number of student to delete record: ");
                // scanf("%d", &regdNo);
                // deleteRecord(fp, regdNo);
                break;
            case 5:
                fclose(fp);
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}
