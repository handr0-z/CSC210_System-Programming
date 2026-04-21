// Client.c - Reader & Signal Sender
// This process attaches to the same shared memory and reads teh message.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHSIZE 100

int main (int argc, char * argv[])
{
	
	int shmid;
	key_t key;
	char *shm;
	char *s;
	
	key = 9876; // key identifies the shared memory segment (same as in server1.c)
	
	shmid = shmget(key, SHSIZE, IPC_CREAT | 0666); // Create shared memory ID if it doesnt exist with read/ write permissions for everyone. - Normally the server runs first.

	if(shmid < 0)
	{
		perror("shmget");
		exit(1);
	}
	
	shm = shmat(shmid, NULL,0); // attaches the segement to the clients address space.
	
	if(shm == (char *) -1)
	{
		perror("shmat");
		exit(1);
	}
	
	
	for(s = shm; *s != 0; s++) // Reads and prints the chracters written by the server until it hits \0.
		printf("%c", *s);

	printf("\n");
	*shm = '*'; // Set the first byte of the shared memory to '*' to signal the server its done.
	
	if(shmdt(shm) == -1) // Detaches from the shared memory.
	{
		perror("shmdt");
		return 1;
	}
	
	printf("client is closed !"); // Notify user.

	return 0;
}