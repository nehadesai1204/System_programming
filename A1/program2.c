#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char fname[100], mode;
    int fd, flags;

    printf("Enter file name : ");
    scanf("%s", fname);

    printf("Enter mode (R/W/A) : ");
    scanf(" %c", &mode);

    if (mode == 'R' || mode == 'r')
        flags = O_RDONLY;
    else if (mode == 'W' || mode == 'w')
        flags = O_WRONLY | O_CREAT;
    else if (mode == 'A' || mode == 'a')
        flags = O_WRONLY | O_APPEND | O_CREAT;
    else
    {
        printf("Invalid mode\n");
        return -1;
    }

    fd = open(fname, flags, 0777);
    if (fd == -1)
    {
        perror("Error opening file");
        return -1;
    }

    printf("File opened successfully\n");
    printf("File Descriptor : %d\n", fd);

    close(fd);
    return 0;
}
