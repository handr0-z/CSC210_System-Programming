// -----------------------------------------------------------------------------------------------------------
// File Name: CSC210_Module7_Lab1.c
// Author: Alejandro Panotja-Zurita
// Date Created: October 10, 2025
// Class: CSC 210: System Programming
// Instructor: Tian Z. Ding
// Assignment: Module 7 - Lab 2: File I/O
// Comments: This File is part of an assignment designed to get familiar with File I/O in Linux
// -----------------------------------------------------------------------------------------------------------
// This lab was completed with the help of the sample code that was provided by the insturctor in the folders
// "FileIOs" and LinuxIOs.
// -----------------------------------------------------------------------------------------------------------

#include <stdlib.h> // Import standard library
#include <string.h> // Import string library
#include <stdio.h> // Import standard I/O library

// Function containing the program banner.
void programBanner()
{
    printf("----------------------------------------------------------------------------------------\n" );
    printf("                                Alejandro Pantoja-Zurita                                \n" );
    printf("                             (CSC 210 - System Programming)                             \n" );
    printf("                         Module 7 - Lab 2: File Input & Output                          \n" );
    printf("----------------------------------------------------------------------------------------\n" );
    printf("This program can be used to create a new text file or open an existing file to read or  \n" );
    printf("write information as requested.                                                         \n" );
    printf("----------------------------------------------------------------------------------------\n" );
}

// Function used to create a file.
void createFile(char *fileName)
{
    // pointer to a file.
    FILE *filePointer;
    
    char *file = fileName; // file name
    char text[100]; // placeholder text to add to file.

    snprintf(text, sizeof(text), "%s was created using fopen().\n", file);

    // Create file
    filePointer = fopen(file, "w");

    // if file creation fails, it prints the error
    if (filePointer == NULL)
    {
        perror("fopen() failed to create desired file.");
    }
    else 
    {
        // add text to file.
        fputs(text, filePointer);

        // close the file
        fclose(filePointer);
    }

    printf("----------------------------------------------------------------------------------------\n" );
    printf("- file: %s was successfully created! -\n", fileName);
    printf("----------------------------------------------------------------------------------------\n" );

    return;
}

// Function used to read information from a file.
void readFile(char *fileName)
{
    // pointer to a file.
    FILE *filePointer;

    char *file = fileName; // file name
    char c[100]; // buffer.
    size_t bytesRead; // variable to store number of bytes read by fread().

    // open a file and read (read mode) text from it.
    filePointer = fopen(file, "r");
    
    // check if file fails to open
    if (filePointer == NULL)
    {
        printf("fopen() failed to open desired file.\n");
        printf("----------------------------------------------------------------------------------------\n" );
    }
    else
    {
        // read contents of file 
        printf("- %s file contents -\n", file);
        printf("----------------------------------------------------------------------------------------\n" );

        // Loop used to obtain contents of file and display in terminal.
        while((bytesRead = fread(c, sizeof(char), sizeof(c) - 1, filePointer)) > 0)
        {
            c[bytesRead] = '\0'; // Null-terminate the buffer so we can print as a string

            printf("%s", c); // Display content on terminal.
        }

        printf("----------------------------------------------------------------------------------------\n" );

        // Close file 
        fclose(filePointer);
    }

	return;
}

// Function used to write information from a file.
void writeFile(char *fileName)
{
    // pointer to a file.
    FILE *filePointer;

    char text[100];

    // open a file and add (append mode) text to it.
    filePointer = fopen(fileName, "a");

    // check if file fails to open
    if (filePointer == NULL)
    {
        printf("fopen() failed to create desired file.\n");
        printf("----------------------------------------------------------------------------------------\n" );
    }
    else
    {
        // Prompt user to enter text to be added to file.
        printf("Enter text to add to file: ");
        fgets(text, sizeof(text), stdin);
        printf("----------------------------------------------------------------------------------------\n" );

        fwrite(text, sizeof(char), strlen(text), filePointer);
        printf("- text was successfully added to %s -\n", fileName);
        printf("----------------------------------------------------------------------------------------\n" );
    }

    // close the file
    fclose(filePointer);

    return;
}

int main()
{
    // Declare any variables needed for program.
    int choice;
    int choice2;
    char c;
    char c2;
    char tempName[100];
    char fileName[100];

    // Program Banner
    programBanner();

    do
    {

        printf("What would you like to do?\n");
        printf("1) Create new text file\n");
        printf("2) Open text file\n");
        printf("3) Exit program\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        scanf("%c", &c); // get rid off the enter for next read.
        printf("----------------------------------------------------------------------------------------\n" );

        switch (choice) 
        {
            case 1:
                printf("- Creating new text file -\n");
                printf("----------------------------------------------------------------------------------------\n" );
                printf("Enter file name: ");
                scanf(" %[^\n]", tempName);

                // add ".txt" to end of desired file name to create text file.
                snprintf(fileName, sizeof(fileName), "%s.txt", tempName);
                
                // Create file.
                createFile(fileName);

                break;
            case 2:
                printf("Enter file name: ");
                scanf(" %[^\n]", tempName);
                printf("----------------------------------------------------------------------------------------\n" );

                // add ".txt" to end of desired file name to create text file.
                snprintf(fileName, sizeof(fileName), "%s.txt", tempName);

                do
                {
                    // check with user what they would like to do with open file.
                    printf("What would you like to do with this file?\n");
                    printf("1) Read from file\n");
                    printf("2) Add text to file\n");
                    printf("3) Main menu\n\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice2);
                    scanf("%c", &c2); // get rid off the enter for next read.
                    printf("----------------------------------------------------------------------------------------\n" );

                    switch (choice2)
                    {
                        case 1:
                            printf("- Opening text file -\n");
                            printf("----------------------------------------------------------------------------------------\n" );
                            readFile(fileName);
                            break;
                        case 2:
                            printf("- Opening text file -\n");
                            printf("----------------------------------------------------------------------------------------\n" );
                            writeFile(fileName);
                            break;
                        case 3:
                            break;
                        default:
                            printf("Error! Invalid Input Detected.\n");
                            printf("----------------------------------------------------------------------------------------\n" );
                    }
                } while (choice2 != 3);

                break;
            case 3:
                printf("- Exiting Program -\n");
                printf("----------------------------------------------------------------------------------------\n" );
                break;
            default:
                printf("Error! Invalid Input Detected.\n");
                printf("----------------------------------------------------------------------------------------\n" );
        }
    } while (choice != 3);

    return 0;
}
