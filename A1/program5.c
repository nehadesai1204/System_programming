#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    char fname[100];
    int fd, n;
    char buffer[1024];

    printf("Enter file name : ");
    scanf("%s", fname);

    printf("Enter number of bytes to read : ");
    scanf("%d", &n);

    fd = open(fname, O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return -1;
    }

    int bytesRead = read(fd, buffer, n);
    if (bytesRead == -1)
    {
        perror("Read error");
        close(fd);
        return -1;
    }

    buffer[bytesRead] = '\0';
    printf("Data Read:\n%s\n", buffer);

    close(fd);
    return 0;
}
