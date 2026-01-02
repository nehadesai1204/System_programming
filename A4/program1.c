#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd1, fd2;
    char buf[100];
    int n;

    if (argc != 3)
    {
        printf("Usage: %s source destination\n", argv[0]);
        return 1;
    }

    fd1 = open(argv[1], O_RDONLY);
    if (fd1 < 0)
    {
        printf("Source file open error");
        return 1;
    }

    fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 < 0)
    {
        printf("Destination file open error");
        return 1;
    }

    while ((n = read(fd1, buf, sizeof(buf))) > 0)
    {
        write(fd2, buf, n);
    }    
    close(fd1);
    close(fd2);
    return 0;
}