// -----------------------------------------------------------------------------------------------------------
// File Name: CSC210_Module7_Exam2.c
// Author: Alejandro Panotja-Zurita
// Date Created: November 1, 2025
// Class: CSC 210: System Programming
// Instructor: Tian Z. Ding
// Assignment: Module 7 - Exam 3: Memory Sharing
// Filename: logserver.c
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
#include<time.h>

#define BUF_SIZE 1024
#define SHM_KEY 0x1234

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
   printf("                                   File 1: logserver.c                                  \n" );
   printf("----------------------------------------------------------------------------------------\n" );
   printf("This program checks if there is a new messagge stored in the shared memory space, if    \n" );
   printf("there is a new message, the message will be saved in a log file for record purposes.    \n" );
   printf("----------------------------------------------------------------------------------------\n" );
}

// Function used to get time.
void getTime(char *timeStr, int size)
{
   // used the following refernce to set up time stamp: https://www.google.com/search?q=how+to+add+time+stap+to+.txt+file+in+c&sca_esv=9277d602da6ca830&ei=bSUGaaauEZrtptQPjcXGoQE&ved=0ahUKEwjmmNvEoNGQAxWatokEHY2iMRQQ4dUDCBM&uact=5&oq=how+to+add+time+stap+to+.txt+file+in+c&gs_lp=Egxnd3Mtd2l6LXNlcnAiJmhvdyB0byBhZGQgdGltZSBzdGFwIHRvIC50eHQgZmlsZSBpbiBjMgoQIRigARjDBBgKSMIKUNMEWNIIcAF4AJABAJgBYKABnAOqAQE1uAEDyAEA-AEBmAIFoALsAsICChAAGLADGNYEGEeYAwDiAwUSATEgQIgGAZAGCJIHATWgB_kbsgcBNLgH6ALCBwMyLjPIBwY&sclient=gws-wiz-serp
   time_t now;
   struct tm *timenow;

   time(&now); // get current time in seconds.
   timenow = localtime(&now); // convert to local time structure.

   strftime(timeStr, size, "%Y-%m-%d %I:%M:%S %p", timenow);
}

// Function used to write to file.
void writeFile(char *bufptr, int size)
{
   // pointer to a file.
   FILE *filePointer;

   char *fileName = "Exam3.log";
   char time[64];

   // open a file and add text to it. (append mode)
   filePointer = fopen(fileName, "a");

   // check if file fails to open
   if (filePointer == NULL)
   {
      printf("Error! failed to open %s file.\n", fileName);
      printf("----------------------------------------------------------------------------------------\n" );
   }
   else
   {
      // Add time stamp before message is added to file.
      getTime(time, sizeof(time));
      fwrite("[", sizeof(char), 1, filePointer);
      fwrite(time, sizeof(char), strlen(time), filePointer);
      fwrite("] ", sizeof(char), 2, filePointer);

      // Add message to file.
      fwrite(bufptr, sizeof(char), size, filePointer);

      // Add new line after message to file.
      fwrite("\n", sizeof(char), 1, filePointer);

      // notify user of completed task.
      printf("Text added to %s -\n", fileName);
      printf("----------------------------------------------------------------------------------------\n" );
   }

   // close the file
   fclose(filePointer);
}

int main(void) 
{
   // Declare IPC control variables.
   int shmid;
   struct shmseg *shmp;

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

   // Notify user of successful connection to share memory
   printf("Success! Now connected to shared memory.\n");
   printf("----------------------------------------------------------------------------------------\n");

   if (shmp == (void *) -1) 
   {
      perror("Shared memory attach");
      printf("----------------------------------------------------------------------------------------\n");
      return 1;
   }

   // Store message found in shared memory space into log file if new information is available.
   while(shmp->complete != 1)
   {
      if (shmp->new == 1) 
      {
         // Write message obtained from memory space into log life.
         writeFile(shmp->buf, shmp->cnt);

         // After the message is logged to file,  put the shmp->new to false
         shmp->new = 0;   
      }
      else
      {
         printf("Waiting for writting process...\n");
         printf("----------------------------------------------------------------------------------------\n");
         sleep(2);
      }
   }

   // Detach from the shared memory.
   if(shmdt(shmp) == -1)
	{
		perror("shmdt");
      printf("----------------------------------------------------------------------------------------\n");
		return 1;
	}
   
   // Marks the shared memory segment for deletion once all processes detach.
   if(shmctl(shmid, IPC_RMID, 0) == -1 )
	{
		perror("shmctl");
      printf("----------------------------------------------------------------------------------------\n");
		return 1;
	}

   // Notify user of successful termination.
	printf("server process terminated.");
   printf("----------------------------------------------------------------------------------------\n");

   return 0;
}