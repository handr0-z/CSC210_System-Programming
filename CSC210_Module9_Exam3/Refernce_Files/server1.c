// Server1.c - Creator and Writer
// This process creates the shared memory, writes "hello world" into it, and wiats for the client to signal that its done.


// Running server1.c & client.c
// 1) Compile both files
// 2) Start the server1.c in one terminal
// 3) Start the client.c in another terminal
// 4) Afteer client.c finishes server1.c will cleanup and print.



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHSIZE 100

int main (int argc, char * argv[])
{
	
	int shmid;
	key_t key;
	char *shm;
	char *s;
	
	key = 9876; // key identifies the shared memory segment. same client.c

	shmid = shmget(key, SHSIZE, IPC_CREAT | 0666); // Create shared memory ID if it doesnt exist with read/ write permissions for everyone.

	if(shmid < 0)
	{
		perror("shmget");
		exit(1);
	}
	
	shm =shmat(shmid, NULL,0); // Attaches the segment to the server's address space. Returns a pointer which point to the beginning of the shared memory block.
	
	if(shm == (char *) -1)
	{
		perror("shmat");
		exit(1);
	}
	
	memcpy(shm, "hello world", 11); // Write Hello world into the shared memory segment. Then add a null terminator \0 so the client can treat it like a C string.
	
	s = shm, // make 's' point to the start of the shared memory.
	s += 11; // move the pointer forward 11 bytes. (right after the "hello world" text thast was just copied in.)
	*s = 0; // Write a 0 (that is, a null terminator '\0') at that position.

	while(*shm != '*') // Wait until the client changes the first character to '*'. (This is a simple synchornoixation mechanism. - A "poor man's semaphore")
		sleep(1);

	if(shmdt(shm) == -1) // detach shared memory space.
	{
		perror("shmdt");
		return 1;
	}

	if(shmctl(shmid, IPC_RMID, 0) == -1 ) // marks the shared memory segment for deletion once all processes detach.
	{
		perror("shmctl");
		return 1;
	}

	printf("server process terminated."); // Notify user.

	return 0;
}