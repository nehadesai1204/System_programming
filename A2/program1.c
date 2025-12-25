#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char fname[100];
    char buffer[100];
    int fd, bytes, total = 0;

    printf("Enter file name : ");
    scanf("%s", fname);

    fd = open(fname, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return -1;
    }

    while ((bytes = read(fd, buffer, sizeof(buffer))) > 0)
    {
        write(1, buffer, bytes);   // print to console
        total += bytes;
    }

    printf("\nTotal bytes read : %d\n", total);

    close(fd);
    return 0;
}
