// Header files
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

// Constants
#define NULL 0
#define BUFFSIZE 512
#define PMODE 0644 /* RW for owner, R for group, others */

main ( int argc, char *argv[])
{
	// Declare variables
	int f1, f2, f3; // file descriptors and byte count
	char buf[BUFFSIZE]; // 512-byte array used as a temporary buffer during copying.
	 
	// command line argument check
	if(argc != 3)
		// if the number of arguments is not 3 (including the program name argv[0]) it prints a message and exits.
		error("Usage: copy from to", NULL);

	// Open the source file for reading
	// open(argv[1], 0) is equivalent to open(argv[1], O_RDONLY).
	// Returns a file descriptor (f1)
	if(( f1 = open(argv[1], 0)) == -1)
		// if error, print error message and exit.
		error("copy can't open %s", argv[1]);

	// create destination file.
	// Creates the destination file (argv[2]) with permissions 0644.
	// If the file exists, it’s truncated (cleared).
	if(( f2 = creat(argv[2], PMODE)) == -1)
		// if error, print error message and exit.
		error("copy: can't create %s", argv[2]);
	
	// loop to copy contents of source file.
	while (( f3 = read(f1, buf, BUFFSIZE)) >0)
		// If write() returns a different number than f3, something went wrong (like disk full).
		if(write (f2, buf, f3) != f3)
			// if error, print error message and exit.
			error("copy: write error", NULL);
		
	exit(0);
	
}

 void error( char *s1, char *s2)
{
	printf(s1, s2);
	printf("\n");
	exit(1);
	
}