// -----------------------------------------------------------------------------------------------------------
// File Name: CSC210_Module5_Assignment2
// Author: Alejandro Panotja-Zurita
// Date Created: September 27, 2025
// Class: CSC 210: System Programming
// Instructor: Tian Z. Ding
// Assignemnt: Module 5 - Assignment 2: Process Arrays with C Pointers
// Comments: This File is part of an assignment designed to get familiar with Pointer in C programming
// -----------------------------------------------------------------------------------------------------------
// The following is a list of referenes used while working on this assignment for help on pointers.
// https://youtu.be/2GDiXG5RfNE?si=8pyq18nh5e8kDLqF
// https://youtu.be/f_uWOWViYc0?si=mG8JjFOFNrChIv7z
// -----------------------------------------------------------------------------------------------------------

#include "stdio.h"

// Declare any variables needed to run program.
void sort(int n, int* ptr);
int lowest_temperature(int n, int* ptr);
int highest_temperatur(int n, int* ptr);
int average_temperature(int n, int* ptr);
void printArray(int n, int* ptr);

int main()
{
    // Declare any variables needed to run program.
    int temp[31];
    int days;
    int avg = 0;
    int max = 0;
    int min = 0;

    // Program Banner
    printf("                                Alejandro Pantoja-Zurita                                \n" );
    printf("----------------------------------------------------------------------------------------\n" );
    printf("                             (CSC 210 - System Programming)                             \n" );
    printf("                 Module 5 - Assignment 2: Process Arrays with C Pointers                \n" );
    printf("----------------------------------------------------------------------------------------\n" );
    printf("This program can be used to obtain the average, minimum and maximum temperature in a    \n" );
    printf("month. User needs to input daily temperatures to calculate information.                 \n" );
    printf("----------------------------------------------------------------------------------------\n" );

    // Prompt user to confirm the # of days in the month
    printf("How many days in the month? " );
    scanf("%d", &days);
    printf("----------------------------------------------------------------------------------------\n" );

    // Get temperature for each day in the month
    for(int i = 0; i < days; i++)
    {
        printf("Enter temperature at noon for day %d: ", i+1);
        scanf("%d", &temp[i]);
    }

    // Find average temperature.
    avg = average_temperature(days, temp);

    // Find lowest temperature.
    min = lowest_temperature(days, temp);

    // Find highest temperature.
    max = highest_temperatur(days, temp);

    // Print out results
    printf("----------------------------------------------------------------------------------------\n" );
    printf("Average temperature: %d\n\n", avg);
    printf("Minimum temperature: %d\n\n", min);
    printf("Maximum temperature: %d\n", max);
    printf("----------------------------------------------------------------------------------------\n" );

    // Display array before sorting.
    printf("Initial Array Order:\n\n");
    printArray(days, temp);

    // Sort array from lowest to highest.
    sort(days, temp);

    // Dislay Array after sorting for comparison.
    printf("Final Array Order:\n\n");
    printArray(days, temp);
    printf("----------------------------------------------------------------------------------------\n\n" );

    return 0;
}

// Funcion used to sort out the values within an array using pointers.
void sort(int n, int* ptr)
{
    // Declare variables needed to execute function
    int key;
    int i, j;

    // For loop created to sort array
    for (i = 1; i < n; i++) 
    { 
        key = *(ptr + i);
        j = i - 1;

        while (j >= 0 && *(ptr + j) > key)
        { 
            *(ptr + j + 1) = *(ptr +j);
            j = j - 1;
        } 

        *(ptr + j + 1) = key;
    } 
}

// Function used to calculate the average value within an array using pointers
int average_temperature(int n, int* ptr)
{
    // Declare variables needed to execute function
    int avg = 0;

    // For loop to add up all values within array together.
    for(int i = 0; i < n; i++){avg = avg + *(ptr + i);}

    // find average temperature based on number of days
    avg = avg / n;

    return avg;
}

// Function used to calculate the lowest temperature within an array using pointers.
int lowest_temperature(int n, int* ptr)
{
    // Declare variables needed to execute function
    int min;
    min = *ptr;

    //find min and max temperature for the month
    for(int i = 0; i < n; i++)
    {
        if(min > *(ptr + i)){min = *(ptr + i);}
    }

    return min;
}

// Function used to calculate the highest temperature within an array using pointers.
int highest_temperatur(int n, int* ptr)
{
        // Declare variables needed to execute function
    int max;
    max = *ptr;

    //find min and max temperature for the month
    for(int i = 0; i < n; i++){if(max < *(ptr + i)){max = *(ptr + i);}} 

    return max;
}

// Function used to display the values within an array using pointers.
void printArray(int n, int* ptr)
{
    for (int i = 0; i < n; i++) {printf("%d ", *(ptr + i));}
    printf("\n\n");
}
