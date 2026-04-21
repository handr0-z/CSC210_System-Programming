// -----------------------------------------------------------------------------------------------------------
// File Name: CSC210_Module5_Assignment1
// Author: Alejandro Panotja-Zurita
// Date Created: September 24, 2025
// Class: CSC 210: System Programming
// Instructor: Tian Z. Ding
// Assignment: Module 5 - Assignment 1: Sorting with pointer
// Comments: This File is part of an assignment designed to get familiar with C programming in Linux
// -----------------------------------------------------------------------------------------------------------

#include <stdio.h>

// *************************************************************************
// This is the sample code for insert sorting. 
// *************************************************************************
// void insertionSort(int arr[], int n) 
// { 
//     // Declare variables
//     int i, j; // variables used for loop.
//     int key; // Value being sorted.
//     // For loop created to sort array
//     for (i = 1; i < n; i++) 
//     { 
//         key = arr[i];
//         j = i - 1;
//         while (j >= 0 && arr[j] > key)
//         { 
//             arr[j + 1] = arr[j];
//             j = j - 1; 
//         } 
//         arr[j + 1] = key; 
//     } 
// }

// *************************************************************************
// Please convert the above c insertion sorting code to use c pointer
// *************************************************************************
 void insertionSort (int *prt, int n)
 {
    // Declare variables
    int i, j; // variables used for loop.
    int key; // Value used as reference

    // For loop created to sort array
    for (i = 1; i < n; i++) 
    { 
        key = *(prt + i); // obtain value being compared to from pointer
        j = i - 1; // j is located (1) address below i.

        while (j >= 0 && *(prt + j) > key) // While j is greater than 0 (starting index value) & value of index is greater than value of key.
        { 
            *(prt + j + 1) = *(prt + j); // index value shifts to the right if index value is bigger than key value.
            j = j - 1; // After shifting value to right, check value to the left of value that was shifted.
        } 

        *(prt + j + 1) = key; // Value of key is stored within array list in correct location (in relation to value that was checked.)
    } 
 }

// A utility function to print an array of size (n) 
void printArray(int *arr, int n) 
{ 
    for (int i = 0; i < n; i++) {printf("%d ", *(arr + i));}
    printf("\n\n");
} 
  
// Driver program to test insertion sort
int main() 
{ 
    // Define array with values
    int arr[] = { 12, 11, 13, 5, 6, 10, 7, 1, 8, 10 };

    // Size of Array (bytes) divided by Size of (1) Array index value = Total # of Index Values.
    int n = sizeof(arr) / sizeof(arr[0]);

    // Display original Array for Comparison
    printf("Initial Array Order:\n");
    printArray(arr, n);
    
    // function to sort out array.
    insertionSort(arr, n);

    // Display Array after sorting for comparison.
    printf("Final Array Order:\n");
    printArray(arr, n); 

    return 0; 
} 