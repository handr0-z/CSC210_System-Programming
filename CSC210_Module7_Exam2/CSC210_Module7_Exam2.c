// -----------------------------------------------------------------------------------------------------------
// File Name: CSC210_Module7_Exam2.c
// Author: Alejandro Panotja-Zurita
// Date Created: October 18, 2025
// Class: CSC 210: System Programming
// Instructor: Tian Z. Ding
// Assignment: Module 7 - Exam 2: File I/O
// Comments: Original file was provided by the instructor for Exam of the class.
// -----------------------------------------------------------------------------------------------------------
// This assignment is based on previous assignment for the following functinalities:
//
//      This program will be able to maintain a list of students in enrolled in a class offered by DTCC
//      for a semester. The assignment is designed to demonstate an understanding of how to use dymamically
//      allocated  memory to add an unlimited # of students to one class. With this program, the user can 
//      add/ delete students to the linked list and view all the students enrolled in this class. The
//      linked list is a one-way linked structure, that contains data elements to store student information. 
//
// The linked list created for Module6_Assignment3 could only exist in computer memory and was lost when the
// user exited the program. This program expands on the oringal, using file input & output APIs to save the 
// student information to a file on the hardware disk. The user will have the option to read the list from 
// the file, add/ delete student to the list with the linked list and Finally save the updated list list
// to the file.
// -----------------------------------------------------------------------------------------------------------

#include <stdlib.h> // Import standard library
#include <string.h> // Import string library
#include <stdio.h> // Import standard I/O library

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

    if (current == NULL)
    {
        printf("Error! Student List is currently Empty.\n");
        printf("----------------------------------------------------------------------------------------\n" );
    }
    else
    {
        while (current != NULL) 
        {
            printf("STUDENT ID: \t%d\n", current->id);
            printf("STUDENT NAME: \t%s\n", current->name);
            printf("STUDENT AGE: \t%d\n", current->age);
            printf("MAJOR: \t\t%s\n", current->major);
            printf("CLASS GRADE: \t%.2f\n", current->grade);
            printf("----------------------------------------------------------------------------------------\n" );

            // change pointer value to next student in list
            current = current->next;
        }
    }
}

// Function to save the list of students to a .txt file.
void saveFile(Student* head, const char* fileName) 
{
    // pointer to a file.
    FILE *filePointer;

    Student* current = head;

    // create a file and add text to it.
    filePointer = fopen(fileName, "w");

    if (filePointer == NULL) 
    {
        printf("Error! Failed to create the %s\n", fileName);
        printf("----------------------------------------------------------------------------------------\n" );
        return;
    }
    else
    {
        if (current == NULL)
        {  
            printf("Error! Student List is currently Empty.\n");
            printf("----------------------------------------------------------------------------------------\n" );
        }
        else
        {
            while (current != NULL) 
            {
                // Store Student ID
                fprintf(filePointer, "%d\n", current->id);

                // Store Student Name
                fprintf(filePointer, "%s\n", current->name);

                // Store Student Age
                fprintf(filePointer, "%d\n", current->age);

                // Store Student Major
                fprintf(filePointer, "%s\n", current->major);

                // Store Class Grade
                fprintf(filePointer, "%.2f\n", current->grade);

                // change pointer value to next student in list
                current = current->next;
            }

            printf("- student list saved to %s -\n", fileName);
            printf("----------------------------------------------------------------------------------------\n" );
        }
    }

    fclose(filePointer);
    return;
}

// Function used to clear existing linked list before populating with new information.
void clearList(Student **leader)
{
    // create temporary variables to free up linked list in a structured manner.
	struct Student  *ptrthis, *ptrfree;

	if (*leader == NULL){return;}

	ptrthis = *leader;

    // Loop created to clear memory
	do
	{
		ptrfree = ptrthis;
		ptrthis = ptrthis->next;
		free(ptrfree);
	} while (ptrthis != NULL);

    *leader = NULL; // Set head of linked list to NULL to create new linked list.

	return;
}

// Function used to obtain student from existing .txt file.
void readFile(Student** head, const char* fileName) 
{
    // Pointer to a file.
    FILE *filePointer;

    // Variables needed within funciton.
    char line[100];
    char nameTmp[50];
    int idTmp;
    int ageTmp;
    char majorTmp[50];
    float gradeTmp;
    
    // open a file and read (read mode) text from it.
    filePointer = fopen(fileName, "r");

    if (filePointer == NULL) 
    {
        printf("Error! Failed to open %s\n", fileName);
        printf("----------------------------------------------------------------------------------------\n" );

        return;
    }
    else
    {
        // Clear existing linked list if needed
        clearList(head);

        // Loop to obtain student info from file and create a linked list
        while(fgets(line, sizeof(line), filePointer) != NULL)
        {
            // Store Student ID
            line[strcspn(line, "\n")] = '\0'; // Remove newline from line read using strcspn[]
            idTmp = atoi(line);

            // Store Student Name
            fgets(line, sizeof(line), filePointer);
            line[strcspn(line, "\n")] = '\0'; // Remove newline from line read using strcspn[]
            strcpy(nameTmp, line);

            // Store Student Age
            fgets(line, sizeof(line), filePointer);
            line[strcspn(line, "\n")] = '\0'; // Remove newline from line read using strcspn[]
            ageTmp = atoi(line);

            // Store Student Major
            fgets(line, sizeof(line), filePointer);
            line[strcspn(line, "\n")] = '\0'; // Remove newline from line read using strcspn[]
            strcpy(majorTmp, line);

            // Store Class Grade
            fgets(line, sizeof(line), filePointer);
            line[strcspn(line, "\n")] = '\0'; // Remove newline from line read using strcspn[]
            gradeTmp = atof(line);

            add_student(head, nameTmp, idTmp, ageTmp, majorTmp, gradeTmp);
        }

        printf("- Student list created using %s -\n", fileName);
        printf("----------------------------------------------------------------------------------------\n" );
    }

    // Close file 
    fclose(filePointer);

    return;
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
    printf("                              Module 7 - Exam 2: File I/O                               \n" );
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
    char tempName[100];
    char fileName[105];
    char *found;

    // define student structures for testing purposes.
    // add_student(&head, "Alejandro Pantoja", 8873891, 29, "Computer Science", 93.00);
    // add_student(&head, "Kevin Vega", 1234567, 23, "Mechanical Engineering", 87.00);
    // add_student(&head, "Dagan Johnson", 2223456, 18, "Biology", 94.00);
    // add_student(&head, "Taylor Skibiky", 7892351, 20, "Architectural Engineering", 79.00);

    // Program Banner
    programBanner();

    while (1) 
    {
        printf("1) Add Student\n");
        printf("2) Delete Student\n");
        printf("3) View Student List\n");
        printf("4) Save File w/ Student Info\n");
        printf("5) Open File w/ Student Info\n");
        printf("6) Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        scanf("%c", &c); // get rid off the enter for next read.
        printf("----------------------------------------------------------------------------------------\n" );

        switch (choice) 
        {
            case 1:
                printf("- Adding student to list -\n");
                printf("----------------------------------------------------------------------------------------\n" );
                printf("Enter student name: ");
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

                printf("\n----------------------------------------------------------------------------------------\n" );
                printf("- Student successfully added to list! -\n");
                printf("----------------------------------------------------------------------------------------\n" );
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
                printf("- Saving student list to file -\n");
                printf("----------------------------------------------------------------------------------------\n" );
                printf("Enter name of .txt file: ");
                scanf(" %[^\n]", tempName);
                printf("----------------------------------------------------------------------------------------\n" );

                // Check if '.txt' is in filename provided.
                found =  strstr(tempName, ".txt");

                if (found != NULL)
                {
                    // copy string to correct variable to proper use, do not add '.txt' to end of it.
                    strcpy(fileName, tempName);
                }
                else
                {
                   // add ".txt" to end of desired filename to open correct file.
                    snprintf(fileName, sizeof(fileName), "%s.txt", tempName); 
                }

                saveFile(head, fileName);

                break;
            case 5:
                printf("- Obtaining student list from file -\n");
                printf("----------------------------------------------------------------------------------------\n" );
                printf("Enter name of .txt file: ");
                scanf(" %[^\n]", tempName);
                printf("----------------------------------------------------------------------------------------\n" );

                // Check if '.txt' is in filename provided.
                found =  strstr(tempName, ".txt");

                if (found != NULL)
                {
                    // copy string to correct variable to proper use, do not add '.txt' to end of it.
                    strcpy(fileName, tempName);
                }
                else
                {
                   // add ".txt" to end of desired filename to open correct file.
                    snprintf(fileName, sizeof(fileName), "%s.txt", tempName); 
                }

                readFile(&head, fileName);
                break;
            case 6:
                free_mem(head);
                return 0;
                break;
            default:
                printf("Error! Invalid Input Detected.\n");
                printf("----------------------------------------------------------------------------------------\n" );
        }
    }

    return 0;
}
