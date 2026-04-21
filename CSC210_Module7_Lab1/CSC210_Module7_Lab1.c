// -----------------------------------------------------------------------------------------------------------
// File Name: CSC210_Module7_Lab1.c
// Author: Alejandro Panotja-Zurita
// Date Created: October 7, 2025
// Class: CSC 210: System Programming
// Instructor: Tian Z. Ding
// Assignment: Module 7 - Lab 1: File I/O
// Comments: This File is part of an assignment designed to get familiar with File I/O in Linux
// -----------------------------------------------------------------------------------------------------------
// This lab was completed with the help of the sample code that was provided by the insturctor in the folders
// "FileIOs" and LinuxIOs.
// -----------------------------------------------------------------------------------------------------------

#define _POSIX_SOURCE // Define POSIX features

#include <fcntl.h> // Import file control library
#include <sys/types.h> // Import library to communicate with low-level operations.
#include <sys/stat.h> // Import file status library
#include <unistd.h> // Import low-level I/O library
#include <stdio.h> // Import standard I/O library
#include <string.h> // Import string library
#include <stdlib.h> // Import standard library
#include<errno.h> // Declares errno, a global variable set when a system call fails.

#undef _POSIX_SOURCE // Undefine POSIX features

// Function containing the program banner.
void programBanner()
{
    printf("----------------------------------------------------------------------------------------\n" );
    printf("                                Alejandro Pantoja-Zurita                                \n" );
    printf("                             (CSC 210 - System Programming)                             \n" );
    printf("                         Module 7 - Lab 1: File Input & Output                          \n" );
    printf("----------------------------------------------------------------------------------------\n" );
    printf("This program can be used to create a new text file or open an existing file to read or  \n" );
    printf("write information as requested.                                                         \n" );
    printf("----------------------------------------------------------------------------------------\n" );
}

// Function used to create a file.
void createFile(char *fileName)
{
    
    char *file = fileName; // file name
    char text[100]; // placeholder text to add to file.
    int fd; // file descriptor

    snprintf(text, sizeof(text), "%s was created using creat().\n", file);

    // if file creation fails, it prints the error
    if ((fd = creat(file, S_IRUSR | S_IWUSR)) < 0)
    {
        perror("creat() error");
    }
    else 
    {
        // add text to file.
        write(fd, text, strlen(text));

        // close the file
        close(fd);
    }

    printf("----------------------------------------------------------------------------------------\n" );
    printf("- file: %s was successfully created! -\n", fileName);
    printf("----------------------------------------------------------------------------------------\n" );

    return;
}

// Function used to open a file.
int openFile(char *fileName)
{
    char *file = fileName; // file name

    // open file and assign it a descriptor
    // Permissions set to 0644 (rw-r--r--)
	int fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	
    // checks if file was able to be opened successfully
	if (fd == -1)
	{
		// prints the numeric error code.
		printf("Error Number %d\n\n", errno);
		
		// print program detail "Success or failure"
		// "Program: ..." (information here is obtained based on error code.)
		perror("Program");
        printf("Error! file: %s was unable to be opened.\n", file);
        printf("----------------------------------------------------------------------------------------\n" );
        return fd;
	}
    else 
    {
        printf("- file: %s was successfully opened! (fd = %d) -\n", file, fd);
        printf("----------------------------------------------------------------------------------------\n" );
    }

	return fd;
}

// Function used to read information from a file.
void readFile(int fd, char *file)
{
	int sz; // number of bytes read.
	char c[100]; // buffer.

	// read contents of file 
    printf("- %s file contents -\n", file);
    printf("----------------------------------------------------------------------------------------\n" );

    // reset descriptor position to beginning if necessary.
    lseek(fd, 0, SEEK_SET);


    while ((sz = read(fd, c, sizeof(c)-1)) > 0)
    {
        c[sz] = '\0'; // Null terminate buffer.
        printf("%s", c); // print out file contents onto terminal.
    }
    printf("----------------------------------------------------------------------------------------\n" );

    // check if there was issue reading file.
	if (sz < 0) 
	{
        printf("Error reading file: %s\n", file);
        perror("Program");
        printf("----------------------------------------------------------------------------------------\n" );
        return;
    }

	return;
}

// Function used to write information from a file.
void writeFile(int fd, char *file)
{
    int sz;
    char text[100];

    // Prompt user to enter text to be added to file.
    printf("Enter text to add to file: ");
    scanf(" %[^\n]", text);
    printf("----------------------------------------------------------------------------------------\n" );

    // Append newline to text being added to file.
    strncat(text, "\n", sizeof(text) - strlen(text) - 1);


    // Write the string to the file
    sz = write(fd, text, strlen(text));
    
    // check to make sure text was properly added to file.
    if (sz < 0) 
    {
        perror("Write error");
        printf("\n----------------------------------------------------------------------------------------\n" );
    }
    else
    {
        printf("- text was successfully added to %s -\n", file);
        printf("----------------------------------------------------------------------------------------\n" );
    }

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
    int fd;

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
                printf("- Opening text file -\n");
                printf("----------------------------------------------------------------------------------------\n" );
                printf("Enter file name: ");
                scanf(" %[^\n]", tempName);
                printf("----------------------------------------------------------------------------------------\n" );

                // add ".txt" to end of desired file name to create text file.
                snprintf(fileName, sizeof(fileName), "%s.txt", tempName);

                // Open file
                fd = openFile(fileName);

                if (fd == -1){break;}

                do
                {
                    // check with user what they would like to do with open file.
                    printf("What would you like to do?\n");
                    printf("1) Read text from file\n");
                    printf("2) Add text to file\n");
                    printf("3) Main Menu\n\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice2);
                    scanf("%c", &c2); // get rid off the enter for next read.
                    printf("----------------------------------------------------------------------------------------\n" );

                    switch (choice2)
                    {
                        case 1:
                            readFile(fd, fileName);
                            break;
                        case 2:
                            writeFile(fd, fileName);
                            break;
                        case 3:
                            break;
                        default:
                            printf("Error! Invalid Input Detected.\n");
                            printf("----------------------------------------------------------------------------------------\n" );
                    }
                } while (choice2 != 3);

                close(fd);

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
