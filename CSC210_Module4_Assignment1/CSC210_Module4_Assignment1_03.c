// -----------------------------------------------------------------------------------------------------------
// File Name: CSC210_Module4_Assignment1_03
// Author: Alejandro Panotja-Zurita
// Date Created: September 22, 2025
// Class: CSC 210: System Programming
// Instructor: Tian Z. Ding
// Assignment: Module 4 - Assignment 1: C Programming with Raspberry Pi
// Comments: This File is part of an assignment designed to get familiar with C programming in Linux
// -----------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>

int main(void)
{

    // Declare any variables needed to run program.
    int strSize = 50;
    int bigStrSize = 100;
    char str[strSize];
    char bigStr[bigStrSize];

    // Program Banner
    printf("                                Alejandro Pantoja-Zurita                                \n" );
    printf("----------------------------------------------------------------------------------------\n" );
    printf("                             (CSC 210 - System Programming)                             \n" );
    printf("                Module 4 - Assignment 1: C Programming with Raspberry Pi                \n" );
    printf("----------------------------------------------------------------------------------------\n" );
    printf("This program prompts user to provide text to store until user types 'quit' or if storage\n" );
    printf("overflows upon receiving next user input.\n");
    printf("----------------------------------------------------------------------------------------\n\n" );

    // Loop created to continue recieving user input.
    do
    {
        // Prompt user to input text to store.
        printf("[%d/%d] Enter desired text to store (type 'quit' to stop): ", strlen(bigStr), bigStrSize);
        fgets(str, strSize, stdin); // fgets takes user input - including spaces.
        printf("\n");

        // Check if user would like to finish inputing text to store.
        if (strcmp(str, "quit\n") == 0) 
        {
            printf("----------------------------------------------------------------------------------------\n\n" );
            printf("Received 'quit' text from user input.\n\n");
            printf("Terminating user input requests.\n\n");
            break;
        }
        
        // Check if user input will cause bigStr to overflow.
        // + 2 at the end of argument is to store additional breakline '\n' in between  user inputs.
        if (strlen(str) + strlen(bigStr) + 2 > bigStrSize)
        {
            printf("----------------------------------------------------------------------------------------\n\n" );
            printf("ERROR! Unable to store incoming text due to overflow...\n\n");
            break;
        }

        // store user input inside bigStr variable.
        strcat(bigStr, str);
        strcat(bigStr, "\n"); // add new line between each input stored.

    } while (strlen(bigStr) < bigStrSize);
    printf("----------------------------------------------------------------------------------------\n\n" );

    // Print text stored inside bigStr for user.
    printf("STORED USER TEXT:\n\n");
    printf("%s", bigStr);
}