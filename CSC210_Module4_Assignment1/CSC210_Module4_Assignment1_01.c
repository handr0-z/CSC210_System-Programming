// -----------------------------------------------------------------------------------------------------------
// File Name: CSC210_Module4_Assignment1_01
// Author: Alejandro Panotja-Zurita
// Date Created: September 22, 2025
// Class: CSC 210: System Programming
// Instructor: Tian Z. Ding
// Assignemnt: Module 4 - Assignment 1: C Programming with Raspberry Pi
// Comments: This File is part of an assignment designed to get familiar with C programmin in Linux
// -----------------------------------------------------------------------------------------------------------

#include <stdio.h>

int main(void)
{
    // Declare any variables needed to run program.
    int temp[31];
    int days;
    int avg = 0;
    int max = 0;
    int min = 200;
    int i = 0;

    // Program Banner
    printf("                                Alejandro Pantoja-Zurita                                \n" );
    printf("----------------------------------------------------------------------------------------\n" );
    printf("                             (CSC 210 - System Programming)                             \n" );
    printf("                Module 4 - Assignment 1: C Programming with Raspberry Pi                \n" );
    printf("----------------------------------------------------------------------------------------\n" );

    // Prompt user to confirm the # of days in the month
    printf("How many days in the month? " );
    scanf("%d", &days);
    printf("----------------------------------------------------------------------------------------\n" );

    // Get temperature for each day in the month
    for(i=0; i<days; i++)
    {
        printf("Enter temperature at noon for day %d: ", i+1);
        scanf("%d", &temp[i]);
    }

    // find average temperature for the month
    for(i=0; i < days; i++){avg = avg + temp[i];}

    //find min and max temperature for the month
    for(i=0; i < days; i++)
    {
        if(min > temp[i]){min = temp[i];}
        if(max < temp[i]){max = temp[i];}
    }

    // Print out results
    printf("----------------------------------------------------------------------------------------\n" );
    printf("Average temperature: %d\n", avg/days);
    printf("Minimum temperature: %d\n", min);
    printf("Maximum temperature: %d\n", max);
    printf("----------------------------------------------------------------------------------------\n\n" );

    return 0;
}