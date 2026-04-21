// -----------------------------------------------------------------------------------------------------------
// File Name: CSC210_Module6_Assignment1
// Author: Alejandro Panotja-Zurita
// Date Created: September 30, 2025
// Class: CSC 210: System Programming
// Instructor: Tian Z. Ding
// Assignemnt: Module 6 - Assignment 1: Directory & Address Strucutres
// Comments: This File is part of an assignment designed to get familiar with structures in C programming
// -----------------------------------------------------------------------------------------------------------
// The following is a list of referenes used while working on this assignment for help on structures.
// https://www.youtube.com/watch?v=qqtmtuedaBM
// https://www.youtube.com/watch?v=R0qIYWo8igs
// The following was used to understand how to omit the \n from user input.
// https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
// -----------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Declare any structures needed for program purposes.
struct MailingAddress
{
    char address1[50];
    char address2[50];
    char city[50];
    char state[50];
    char country[50];
};
struct Person
{
    char firstName[50];
    char lastName[50];
    char phoneNumber[20];
    struct MailingAddress mailingAddress;
};

// Declare prototypes for function
void userInput( const char *prompt, char *userInput, int size);

int main(void)
{
    // Declare any variables needed to run program.
    int MAX = 100;
    int i = 0;

    // Program Banner
    printf("                                Alejandro Pantoja-Zurita                                \n" );
    printf("----------------------------------------------------------------------------------------\n" );
    printf("                             (CSC 210 - System Programming)                             \n" );
    printf("                 Module 6 - Assignment 1: Directory & Address Structures                \n" );
    printf("----------------------------------------------------------------------------------------\n" );
    printf("This program can be used to store the contact information of people within a strucutre  \n" );
    printf("that can be reuse as needed.                                                            \n" );
    printf("----------------------------------------------------------------------------------------\n" );

    // Prompt user to confirm the # of contacts to store
    printf("How many contacts would you like to store? " );
    scanf("%d", &MAX);
    while (getchar() != '\n'); // Code used to avoid [Enter] (\n) being used as first name input.
    printf("----------------------------------------------------------------------------------------\n" );

    // Create array list to store information for people.
    struct Person* people = malloc(sizeof(struct Person) * MAX);

    // For loop created to obtain information from user.
    for (i = 0; i < MAX; i++)
    {   
        // Obtain last name from user.
        printf("[%d/%d] ", i+1, MAX);
        userInput("Enter first name: ", people[i].firstName, sizeof(people[i].firstName));

        // Obtain first name from user.
        printf("[%d/%d] ", i+1, MAX);
        userInput("Enter last name: ", people[i].lastName, sizeof(people[i].lastName));
        printf("----------------------------------------------------------------------------------------\n" );

        // Obtain phone number from user.
        userInput("Enter phone number: ", people[i].phoneNumber, sizeof(people[i].phoneNumber));
        printf("----------------------------------------------------------------------------------------\n" );

        // obtain mailing address from user
        printf("[%d/%d] ", i+1, MAX);
        userInput("Address Line 1: ", people[i].mailingAddress.address1, sizeof(people[i].mailingAddress.address1));
        userInput("Address Line 2 (Optional): ", people[i].mailingAddress.address2, sizeof(people[i].mailingAddress.address2));
        userInput("City: ", people[i].mailingAddress.city, sizeof(people[i].mailingAddress.city));
        userInput("State: ", people[i].mailingAddress.state, sizeof(people[i].mailingAddress.state));
        userInput("Country: ", people[i].mailingAddress.country, sizeof(people[i].mailingAddress.country));
        printf("----------------------------------------------------------------------------------------\n" );
    }

    printf("\nPrinting Contanct Information for verification\n\n" );
    printf("----------------------------------------------------------------------------------------\n" );

    // For loop created to display information stored.
    for (i = 0; i < MAX; i++)
    {
        printf("NAME: %s %s\n", people[i].firstName, people[i].lastName);
        printf("PHONE #: %s\n\n", people[i].phoneNumber);

        printf("MAILING ADDRESS\n");
        printf("%s\n", people[i].mailingAddress.address1);

        // Check if address line 2 contains information.
        if (people[i].mailingAddress.address2[0] != '\0'){printf("%s\n", people[i].mailingAddress.address2);}
        
        printf("%s, %s\n", people[i].mailingAddress.city, people[i].mailingAddress.state);
        printf("%s\n", people[i].mailingAddress.country);
        printf("----------------------------------------------------------------------------------------\n" );
    }

    free(people);

    return 0;
}

// Function to obtain user input.
void userInput( const char *prompt, char *userInput, int size)
{
    printf("%s", prompt);
    fgets(userInput, size, stdin); // fgets takes user input - including spaces.

    // Remove the newline (\n) from user input if necessary
    // Code obtained from https://stackoverflow.com/questions/2693776/removing-trailing-newline-character-from-fgets-input
    userInput[strcspn(userInput, "\n")] = '\0';
}