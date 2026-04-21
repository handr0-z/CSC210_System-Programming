// -----------------------------------------------------------------------------------------------------------
// File Name: CSC210_Module7_Lab1.c
// Author: Alejandro Panotja-Zurita
// Date Created: October 25, 2025
// Class: CSC 210: System Programming
// Instructor: Tian Z. Ding
// Assignment: Module 9 - Assignment 4: Copy Program with Memory Mapping
// Comments: This File is part of an assignment designed to get familiar with Memory Mapping.
// -----------------------------------------------------------------------------------------------------------
// This lab was completed with the help of the sample code that was provided by the instructor for this
// assignment.
// -----------------------------------------------------------------------------------------------------------

#include <stdlib.h> // Import standard library
#include <string.h> // Import string library
#include <stdio.h> // Import standard I/O library
#include <sys/types.h> // defines system data types (off_t, size_t, etc.)
#include <sys/stat.h> // provides struct stat and macros for file info.
#include <fcntl.h> // for file control operations
#include <unistd.h> // for POSIX functions close(), fstat()
#include <sys/mman.h> // defines memory mapping functions and related constants.
#include <errno.h>

// Function containing the program banner.
void programBanner()
{
    printf("----------------------------------------------------------------------------------------\n");
    printf("                                Alejandro Pantoja-Zurita                                \n");
    printf("                             (CSC 210 - System Programming)                             \n");
    printf("                Module 9 - Assignment 4: Copy Program with Memory Mapping               \n");
    printf("----------------------------------------------------------------------------------------\n");
    printf("This program can be used to copy the contents of a file onto a second file as requested \n");
    printf("by the user. User MUST provide extension of file to be opened when using program.       \n");
    printf("----------------------------------------------------------------------------------------\n");
}

// Function used to obtain file name.
void obtainFileName(char *file, size_t size, const char *fileType)
{
    // Declare any variables needed to run program
    char *found;
    char tempName[100];

    // Prompt user to enter file name.
    printf("Enter name of %s file: ", fileType);
    scanf(" %[^\n]", tempName);
    printf("----------------------------------------------------------------------------------------\n");

    // Removed section that ensures .txt file is added to user input, this allows program to copy any file.    
    // // Check if '.txt' is in filename provided.
    // found =  strstr(tempName, ".txt");

    // if (found != NULL)
    // {
    //     // copy string to correct variable to proper use, do not add '.txt' to end of it.
    //     strncpy(file, tempName, size - 1);
    //     file[size-1] = '\0'; // ensure null termination instead of overflow.
    // }
    // else
    // {
    //     // add ".txt" to end of desired filename to open correct file.
    //     snprintf(file, size, "%s.txt", tempName); 
    // }

    //  copy string to correct variable to proper use, do not add '.txt' to end of it.
    strncpy(file, tempName, size - 1);
    file[size-1] = '\0'; // ensure null termination instead of overflow.
}

// Function used to write information from a file.
void writeFile(char *fileName, char *originalFile, struct stat *sb)
{
    // open file and assign it a descriptor
    // Permissions set to 0644 (rw-r--r--)
	int fd = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	
    // checks if file was able to be opened successfully
	if (fd == -1)
	{
		// prints the numeric error code.
		printf("Error Number %d\n\n", errno);
		
		// print program detail "Success or failure"
		// "Program: ..." (information here is obtained based on error code.)
		perror("Program");
        printf("Error! file: %s was unable to be opened.\n", fileName);
        printf("----------------------------------------------------------------------------------------\n");
        return;
	}

    size_t copyTotal = 0; // total bytes written

    while (copyTotal < sb->st_size) // compare original file size to amount copied into new new file (copyTotal)
    {
        ssize_t copyCount = write(fd, originalFile + copyTotal, sb->st_size - copyTotal);

        // If error, print out message and exit loop.
        if (copyCount == -1) 
        {
            perror("write");
            printf("----------------------------------------------------------------------------------------\n");
            break;
        }

        copyTotal += copyCount; // update total copied and before continuing.
    } 

    // Close the file descriptor for the destination file.
    if(close(fd) == -1)
    {
        perror("close");
        printf("----------------------------------------------------------------------------------------\n");
    }
}

int main()
{
    // Declare any variables needed for program.
    char originFileName[105];
    char destinationFileName[105];

    int fd; // The file descriptor returned by open()
    int unmapStatusOrigin; // Stores the result of munmap() for original file.
    char *file; // A pointer that will point to the memory-mapped region.
	struct stat sb; // a struct stat used to hold information about the original file (size, permissions, type, etc.)

    // Program Banner
    programBanner();

    // Obtain origin file name.
    obtainFileName(originFileName, sizeof(originFileName), "original");

    // Obtain destination file name.
    obtainFileName(destinationFileName, sizeof(destinationFileName), "destination");

    // Open original file
	fd = open(originFileName, O_RDONLY);

    // Check to ensure file opened successfully
	if(fd == -1)
	{
		// If error print system error message and exit program.
		perror("open");
        printf("----------------------------------------------------------------------------------------\n");
	    return 1;
	}

    // Find the size of the first file
    // Use fstat() to get file information for the open descriptor 'fd'.
    // The file size is stored in sb.st_size, which is needed for mmap().
	if(fstat(fd, &sb) == -1)
	{
		// If error, print system error message and exit program.
		perror("fstat");
        printf("----------------------------------------------------------------------------------------\n");
		return 1;
	}

    // Check if its a regular file (not a directory, device, etc.)
    if(!S_ISREG(sb.st_mode))
    {
        // If not regular file, print system error message and exit program.
        fprintf(stderr, "%s is not a file.\n", originFileName);
        printf("----------------------------------------------------------------------------------------\n");
        return 1;
    }

    // Memory map the original file.
	file = mmap(0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0); // On success returns a pointer to the mapped memory. on failure, returns MAP_FAILED.

    // Check if mapping succeeded.
    if(file == MAP_FAILED)
    {
        // If error print system error message and exit program.
        perror("mmap");
        printf("----------------------------------------------------------------------------------------\n");
        return 1;
    }

    // Close the file descriptor for the original file. Once the file is mapped, we no longer need the file descriptor.
    // The mapping remains valid even after closing the descriptor. This saves a system resource (the open file handle).
    if(close(fd) == -1)
    {
        perror("close");
        printf("----------------------------------------------------------------------------------------\n");
        return 1;
    }

    // Copy file contents to new file.
    writeFile(destinationFileName, file, &sb);

    // unmap the original file.
    unmapStatusOrigin = munmap(file, sb.st_size);
   
    if (unmapStatusOrigin == -1) 
    {
        // On failure, print error message and exit
        perror("munmap failure");
        printf("----------------------------------------------------------------------------------------\n");
        return 1;
    }

    // Inform user that the program has executed succesfully.
    printf("Done!\n");
    printf("%s has been successfully copied to %s.\n", originFileName, destinationFileName);
    printf("----------------------------------------------------------------------------------------\n");

    return 0;
}
