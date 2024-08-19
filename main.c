#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100
#define PASSWORD "1111"

struct User {
    char firstName[MAX_LENGTH];
    char lastName[MAX_LENGTH];
    char email[MAX_LENGTH];
    char phoneNumber[MAX_LENGTH];
    char password[MAX_LENGTH];
};

int isValidEmail(const char* email) {
    return (strstr(email, "@") != NULL);
}

void registerUser() {
    struct User newUser;
    printf("Enter first name: ");
    scanf("%s", newUser.firstName);
    printf("Enter last name: ");
    scanf("%s", newUser.lastName);
    do {
        printf("Enter email: ");
        scanf("%s", newUser.email);
        if (!isValidEmail(newUser.email)) {
            printf("Invalid email address!\n");
        }
    } while (!isValidEmail(newUser.email));
    printf("Enter phone number: ");
    scanf("%s", newUser.phoneNumber);
    printf("Enter password: ");
    scanf("%s", newUser.password);

    FILE* outFile = fopen("users.txt", "a");
    if (outFile == NULL) {
        fprintf(stderr, "Error: Couldn't open file for writing.\n");
        return;
    }

    fprintf(outFile, "%s %s %s %s %s\n", newUser.firstName, newUser.lastName,
        newUser.email, newUser.phoneNumber, newUser.password);
    printf("Registration successful!\n");
    fclose(outFile);
}

void loginUser() {
    char email[MAX_LENGTH];
    char password[MAX_LENGTH];
    printf("Enter email: ");
    scanf("%s", email);
    printf("Enter password: ");
    scanf("%s", password);

    if (strcmp(password, PASSWORD) != 0) {
        printf("Invalid password!\n");
        return;
    }

    FILE* inFile = fopen("users.txt", "r");
    if (inFile == NULL) {
        fprintf(stderr, "Error: Couldn't open file for reading.\n");
        return;
    }

    struct User user;
    while (fscanf(inFile, "%s %s %s %s %s", user.firstName, user.lastName,
        user.email, user.phoneNumber, user.password) != EOF) {
        printf("%s %s %s %s %s\n", user.firstName, user.lastName,
            user.email, user.phoneNumber, user.password);
    }
    fclose(inFile);
}

int main() {
    int choice;
    printf("Choose an option:\n");
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. View database\n");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        registerUser();
        break;
    case 2:
        loginUser();
        break;
    case 3:
        printf("Enter password to view database: ");
        char password[MAX_LENGTH];
        scanf("%s", password);
        if (strcmp(password, PASSWORD) == 0) {
            loginUser();
        }
        else {
            printf("Invalid password!\n");
        }
        break;
    default:
        printf("Invalid choice!\n");
    }

    return 0;
}
