// -----------------------------------------------------------------------------------------------------------
// File Name: CSC210_Module6_Assignment3.c
// Author: Alejandro Panotja-Zurita
// Date Created: October 3, 2025
// Class: CSC 210: System Programming
// Instructor: Tian Z. Ding
// Assignment: Module 6 - Assignment 3: Linked List with C Pointers
// Comments: This File is part of an assignment designed to get familiar with Linked List With C pointers
// -----------------------------------------------------------------------------------------------------------
// This program will be able to maintain a list of students in enrolled in a class offered by DTCC for a
// semester. The assignment is designed to demonstate an understanding of how to use dymamically allocated 
// memory to add an unlimited # of students to one class. With this program, the user can add/ delete students
// to the linked list and view all the students enrolled in this class. The linked list is a one-way linked
// structure, that contains data elements to store student information. 
// -----------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a student
typedef struct Student 
{
    char name[50];
    int id;
    int age;
    char major[50];
    float grade;
    struct Student* next;
} Student;

// Function used to create a new student node
Student* create_student(char* name, int id, int age, char* major, float grade)
{
    Student* new_student = (Student*)malloc(sizeof(Student));
    strcpy(new_student->name, name);
    new_student->id = id;
    new_student->age = age;
    strcpy(new_student->major, major);
    new_student->grade = grade;
    new_student->next = NULL;
    return new_student;
}

// Function used to create and add new student to the linked list.
void add_student(Student** leader, char* name, int id, int age, char* major, float grade)
{
    // Create a new student.
    Student* current = create_student(name, id, age, major, grade);

    // change pointer value to next student before cycling to next interation of loop.
    current->next = *leader; // previous leader is linked to the new user that was created.
    *leader = current; // new user is assigned role of leader in list.

    printf("\n----------------------------------------------------------------------------------------\n" );
    printf("- Student successfully added to list! -\n");
    printf("----------------------------------------------------------------------------------------\n" );
}

// Function used to remove student from list without 
void delete_student(Student** leader, int id)
{
    Student* current = *leader;
    Student* prev = NULL;
    
    while (current != NULL)
    {
        if (current->id == id) // check for ID match with current user in list
        {
            if (prev == NULL) // check if current leader of list is selected.
            {
                *leader = current->next; // assign new leader.
            }
            else
            {
                prev->next = current->next; // have 'previous->next' pointer skip over 'current' and move to 'current->next' instead.
            }

            free(current); // remove current user from list.
            printf("- Student successfully removed from list! -\n");
            printf("----------------------------------------------------------------------------------------\n" );
            return;
        }
        else
        {
            prev = current; // move 'current' to value 'previous' value
            current = current->next; // assign 'current' the value stored inside 'current->next' NODE
        }
    }

    printf("- No student found with ID: %d -\n", id);
    printf("----------------------------------------------------------------------------------------\n" );
}

// Function to print the list of students to the console. 
void print_students(Student* leader)
{
    Student* current = leader;

    printf("- Printing Student List -\n");
    printf("----------------------------------------------------------------------------------------\n" );

    while (current != NULL) 
    {
        printf("\nSTUDENT ID: \t%d\n", current->id);
        printf("STUDENT NAME: \t%s\n", current->name);
        printf("STUDENT AGE: \t%d\n", current->age);
        printf("MAJOR: \t\t%s\n", current->major);
        printf("CLASS GRADE: \t%.2f\n", current->grade);
        printf("\n----------------------------------------------------------------------------------------\n" );

        // change pointer value to next student in list
        current = current->next;
    }

    printf("- Student list successfully printed! -\n");
    printf("----------------------------------------------------------------------------------------\n" );
}

// Function used to free up memory used by the linked list before exiting the program.
void free_mem(Student *leader)
{
    // create temporary variables to free up linked list in a structured manner.
	struct Student  *ptrthis, *ptrfree;

	if (leader == NULL){return;}

	ptrthis = leader;

    // Loop created to clear memory for each student.
	do
	{
		ptrfree = ptrthis;
		ptrthis = ptrthis->next;
		free(ptrfree);
	} while (ptrthis != NULL);

    printf("- Terminating Program -\n");
    printf("----------------------------------------------------------------------------------------\n" );

	return;
}

// Function containing the program banner.
void programBanner()
{
    printf("----------------------------------------------------------------------------------------\n" );
    printf("                                Alejandro Pantoja-Zurita                                \n" );
    printf("                             (CSC 210 - System Programming)                             \n" );
    printf("                  Module 6 - Assignment 3: Linked List with C Pointers                  \n" );
    printf("----------------------------------------------------------------------------------------\n" );
    printf("This program will be able to maintain a list of students in enrolled in a class offered \n" );
    printf("by DTCC for a semester. The assignment is designed to demonstate an understanding of how\n" );
    printf("to use dynamically allocated memory to add an unlimited # of students to one class. With\n" );
    printf("this program, the user can add/ delete students to the linked list and view all the     \n" );
    printf("students enrolled in this class. The linked list is a one-way linked structure, that    \n" );
    printf("contains data elements to store student information.                                    \n" );
    printf("----------------------------------------------------------------------------------------\n" );
}

int main()
{
    // Define any variables needed to run program.
    Student* head = NULL;
    int choice;
    char name[50];
    int id;
    int age;
    char major[50];
    float grade;
    char c;

    // define student strucutres for testing purposes.
    add_student(&head, "Alejandro Pantoja", 8873891, 29, "Computer Science", 93.00);
    add_student(&head, "Kevin Vega", 1234567, 23, "Mechanical Engineering", 87.00);
    add_student(&head, "Dagan Johnson", 2223456, 18, "Biology", 94.00);
    add_student(&head, "Taylor Skibiky", 7892351, 20, "Architectural Engineering", 79.00);
    
    // Program Banner
    programBanner();

    while (1) 
    {
        printf("\n1) Add student\n");
        printf("2) Delete student\n");
        printf("3) List students\n");
        printf("4) Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        scanf("%c", &c); // get rid off the enter for next read.
        printf("\n----------------------------------------------------------------------------------------\n" );

        switch (choice) 
        {
            case 1:
                printf("- Adding student to list -\n");
                printf("----------------------------------------------------------------------------------------\n" );
                printf("\nEnter student name: ");
                scanf(" %[^\n]", name);
                printf("Enter student ID: ");
                scanf("%d", &id);
                printf("Enter student age: ");
                scanf("%d", &age);
                scanf("%c", &c);  // get rid off the enter for next read
                printf("Enter student major: ");
                scanf(" %[^\n]", major);
                printf("Enter student grade: ");
                scanf("%f", &grade);
                add_student(&head, name, id, age, major, grade);
                break;
            case 2:
                printf("- Removing student from list -\n");
                printf("----------------------------------------------------------------------------------------\n" );
                printf("\nEnter ID of student to delete: ");
                scanf("%d", &id);
                printf("\n----------------------------------------------------------------------------------------\n" );
                delete_student(&head, id);
                break;
            case 3:
                print_students(head);
                break;
            case 4:
                free_mem(head);
                return 0;
                break;
            default:
                printf("\n Error! Invalid Input Detected.\n");
                printf("\n----------------------------------------------------------------------------------------\n" );
        }
    }

    return 0;
}
