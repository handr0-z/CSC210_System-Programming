#include <stdio.h> // standard I/O library
#include <sys/types.h> // deines system data types (off_t, size_t, etc.)
#include <sys/stat.h> // provides struct sat and macros for file info.
#include <fcntl.h> // for file control operations
#include <unistd.h> // for POSIX functions close(), fstat()
#include <sys/mman.h> // defines memory mapping functions and related constants.

int main(int argc, char *argv[])
{
	// Declare variables
	struct stat sb; // a struct stat used to hold information about the file (size, permissions, type, etc.)
	off_t len; // Used to iterate over the file's length
	char *p; // A pinter that will point to the memory-mappped region.
	int fd; // The file descriptor returned by open()
	
	// Argument check
	// Check that the user passed a filename as an argument.
	// if(argc < 2)
	// {
	//   	fprintf(stderr, "usage: %s <file>\n", argv[0]);
	//  	return 1;
	// }
	
	// Open file
	fd = open("mapping.c", O_RDONLY);

	// Check to ensure file opened successfully
	if(fd == -1)
	{
		// If error print system error message and exit program.
		perror("open");
		return 1;
	}
	
	// Get file information.
	// fstat() fills in the sb structure with information about the open file.
	// sb.st_size gives the file size, which is needed for mmap().
	if(fstat(fd, &sb) == -1)
	{
		// If error print system error message and exit program.
		perror("fstat");
		return 1;
	}
	
	// Check if its a regular file (not a directory, device, etc.)
	if(!S_ISREG(sb.st_mode))
	{
		// not regular file print system error message and exit program.
		fprintf(stderr, "%s is not a file\n", argv[1]); // argv[1] would be file name obtained earlier in program.
		return 1;
	}
	
	// Memory map the file.
	// On success returns a poitner to the mapped memory. on failure, returns MAP_FAILED.
	p = mmap(0, sb.st_size, PROT_READ, MAP_SHARED, fd, 0);
	
	// Check if mapping succeeded.
	if(p == MAP_FAILED)
	{
		// If error print system error message and exit program.
		perror("mmap");
		return 1;
	}
	
	// Close the file descriptor
	// Once the file is mapped, we no longer need the file descriptor.
	// The mapping remains valid even after closing the descriptor.
	// This saves a system resource (the open file handle).
	if(close(fd) == -1)
	{
		perror("close");
		return 1;
	}
	
	// Print file contents from memory.
	for(len = 0; len < sb.st_size; len++)
	{
		putchar(p[len]);
	}
	
	// Unmap memory
	if(munmap(p, sb.st_size) == -1)
	{
		// if it fails (rare, but possible), it prints an error.
		perror("munmap");
		return 1;
	}
	
	return 0;
}