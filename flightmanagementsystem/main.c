#include "header.h"
#include <stdio.h>
#include <string.h>

#define ADMIN_PASSWORD "Dmaths@99#$"

int main() {
    
    char password[20];
    int choice;
    
    while (1) {
        printf("\nAccess Menu:\n");
        printf("1. Admin Access\n");
        printf("2. User Access\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter the admin password: ");
                scanf("%s", password);

                if (strcmp(password, ADMIN_PASSWORD) == 0) {
                    printf("Admin access granted!\n");
                    adminaccess();
                } else {
                printf("Incorrect password. Access denied!\nYour actions will be reported to Vamsi");
                }
                
                break;
            case 2:
                useraccess();
                break;
            case 3:
                
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}