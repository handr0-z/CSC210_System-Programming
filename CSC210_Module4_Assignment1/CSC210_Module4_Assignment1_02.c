// -----------------------------------------------------------------------------------------------------------
// File Name: CSC210_Module4_Assignment1_02
// Author: Alejandro Panotja-Zurita
// Date Created: September 22, 2025
// Class: CSC 210: System Programming
// Instructor: Tian Z. Ding
// Assignemnt: Module 4 - Assignment 1: C Programming with Raspberry Pi
// Comments: This File is part of an assignment designed to get familiar with C programmin in Linux
// -----------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>

int main(void)
{

    // Declare any variables needed to run program.
    int numbers[10];
    int i = 0;

    // Program Banner
    printf("                                Alejandro Pantoja-Zurita                                \n" );
    printf("----------------------------------------------------------------------------------------\n" );
    printf("                             (CSC 210 - System Programming)                             \n" );
    printf("                Module 4 - Assignment 1: C Programming with Raspberry Pi                \n" );
    printf("----------------------------------------------------------------------------------------\n" );
    printf("This program stores 10 numbers from the user and checks if any of them match.\n" );
    printf("----------------------------------------------------------------------------------------\n\n" );

    // Prompt user to Enter 10 numbers and store them in an array
    for (int i = 0; i < 10; i++)
    {
        printf("[%d/10] Enter number to store: ", i + 1);
        scanf("%d", &numbers[i]);
        printf("\n");
    }
    printf("----------------------------------------------------------------------------------------\n" );

    //Compare the numbers in the array to check if any of them match
    for (i = 0; i < 10; i++)
    {
        for (int j = i + 1; j < 10; j++)
        {
            numbers[i] == numbers[j];

            // Display Message if numbers match.
            if (numbers[i] == numbers[j])
            {
                printf("Numbers %d & %d match!\n\n", i + 1, j + 1);
                printf("Matching number is: %d\n", numbers[i]);
                printf("----------------------------------------------------------------------------------------\n" );
            }
        }    
    }    
}