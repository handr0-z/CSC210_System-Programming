// -----------------------------------------------------------------------------------------------------------
// File Name: CSC210_Module7_Exam2.c
// Author: Alejandro Panotja-Zurita
// Date Created: November 1, 2025
// Class: CSC 210: System Programming
// Instructor: Tian Z. Ding
// Assignment: Module 7 - Exam 3: Memory Sharing
// Filename: logclient.c
// Comments: Initial files files were provided by the instructor for Exam 3.
// -----------------------------------------------------------------------------------------------------------
// This assignment contains (2) files [logclient.c and logserver.c] that share the same memory space.
// logserver.c is used to log input information that is provided through logclient.c into a file.
// -----------------------------------------------------------------------------------------------------------

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

#define BUF_SIZE 1024 // 1kb for buffer size.
#define SHM_KEY 0x1234 // Key used to connect both files to the same memory space.

struct shmseg 
{
   char buf[BUF_SIZE];
   int cnt; // Number of bytes currently in buffer.
   int new; // Flag: 1 if new data is available.
   int complete; // Flag 1 if producer is done writing.
};

// Function containing the program banner.
void programBanner()
{
   printf("----------------------------------------------------------------------------------------\n" );
   printf("                                Alejandro Pantoja-Zurita                                \n" );
   printf("                             (CSC 210 - System Programming)                             \n" );
   printf("                            Module 9 - Exam 3: Memory Sharing                           \n" );
   printf("                                   File 2: logclient.c                                  \n" );
   printf("----------------------------------------------------------------------------------------\n" );
   printf("This program can be used to send messages to shared memory space. Afterwards, the server\n" );
   printf("process will store message in a log file that can be reviewed.                          \n" );
   printf("----------------------------------------------------------------------------------------\n" );
}

// Function used to obtain text from user.
void getText( char *bufptr)
{
   // Prompt user to enter text to be added to file.
   printf("Enter a message (or type QUIT to exit): ");
   fgets(bufptr, BUF_SIZE, stdin);

   // Remove \n added by fgets and add null terminator.
   bufptr[strcspn(bufptr, "\n")] = '\0';

   printf("----------------------------------------------------------------------------------------\n" );
}

int main(void) 
{
   // Declare IPC control variables - (rarely accessed).
   int shmid;
   struct shmseg *shmp;

   // Declare Working variables - (frequently accessed).
   char *bufptr;

   // Program Banner
   programBanner();

   // Create shared memory ID, if it doesnt exit. with read/ write permisions.
   shmid = shmget(SHM_KEY, sizeof(struct shmseg), 0666|IPC_CREAT);

   // Verify shared memory ID was created successfuly.
   if (shmid == -1) 
   {
      perror("Shared memory");
      printf("----------------------------------------------------------------------------------------\n");
      return 1;
   }
   
   // Attach to the segment to get a pointer to it.
   shmp = shmat(shmid, NULL, 0);

   if (shmp == (void *) -1) 
   {
      perror("Shared memory attach");
      printf("----------------------------------------------------------------------------------------\n");
      return 1;
   }

   // Notify user of successful connection to share memory
   printf("Success! Now connected to shared memory.\n");
   printf("----------------------------------------------------------------------------------------\n");

   // Transfer blocks of data from buffer to shared memory.
   bufptr = shmp->buf;

   do
   {
      // Promp user to enter a message.
      getText(bufptr);

      // Check if 'QUIT' keyword was provided to shared memory space.
      if (strncmp(bufptr, "QUIT", 4) == 0)
      {
         // Quit the process and terminate the logserver program.
         shmp->complete = 1;
      }
      else
      {
         // change value for number of bytes currently in buffer.
         shmp->cnt = strlen(shmp->buf);

         // Notify server process that new information is available
         shmp->new = 1;
      }
   } while (shmp->complete == 0);

   // Detach from the shared memory.
   if(shmdt(shmp) == -1)
	{
		perror("shmdt");
		return 1;
	}

   printf("Writing Process: Complete\n");
   printf("----------------------------------------------------------------------------------------\n");

   return 0;
}