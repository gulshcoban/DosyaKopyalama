#include <stdio.h> /* Standard input/output definitions */
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv []) 
{
    size_t buffersize = (size_t)(8192);
    char buffer[buffersize];
    char source_file[200];
    char destination_file[200];  

    ssize_t bytes_read, bytes_written;
    int fdSource, fdDestination;

    mode_t mode = S_IRUSR | S_IWUSR;

    printf("\nEnter the name of the source file: ");
    scanf("%s", source_file);

    printf("\nEnter the name of the destination file: ");
    scanf("%s", destination_file);
    
    fdSource = open(source_file, O_RDONLY);
    if(fdSource < 0)
    {
	perror("\nNo such file or an error occurred in the source file.");
	return 1;
    }
    else
    {
    
    fdDestination = open(destination_file, O_CREAT | O_WRONLY,0644);
    if(fdDestination < 0)
    {
	perror("\nAn error occurred in the destination file.");
	return 1;    
    }
    else
    {
    while(bytes_read = read(fdSource, buffer, sizeof(buffer))>0)
    {
    
      bytes_written = write(fdDestination, buffer, (ssize_t) bytes_read);
      if(bytes_written != bytes_read)
      {
	 perror("\nAn error occurred during the copy operation.");
         return 1; 
      }

    }
    }
    }
    printf("\nThe copy operation was successful.\n");
    printf("\nContent of %s: %s\n", source_file,buffer); 
    fdDestination = open(destination_file, O_RDONLY);
    bytes_read = read(fdDestination, buffer, sizeof(buffer));
    printf("\nContent of %s: %s\n", destination_file,buffer);

    close(fdSource);
    close(fdDestination);

    return 0;
}