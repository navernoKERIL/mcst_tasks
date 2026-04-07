#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd = open("file.txt", O_RDONLY);
    
    if (fd == -1){
        // Способ 1: значение errno
        fprintf(stderr, "Errno = %d\n", errno);
        
        // Способ 2: strerror (современный аналог sys_errlist)
        fprintf(stderr, "strerror: %s\n", strerror(errno));
        
        // Способ 3: perror
        perror("perror");
        
        exit(errno);
    }
    
    close(fd);
    return 0;
}