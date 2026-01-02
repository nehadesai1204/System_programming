#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd1, fd2;
    char buf[100];
    int n = 0, offset = 0;

    if (argc != 4)
    {
        printf("Usage: %s source destination offset\n", argv[0]);
        return 1;
    }

    offset = atoi(argv[3]);

    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    lseek(fd1, offset, SEEK_SET);

    while ((n = read(fd1, buf, sizeof(buf))) > 0)
    {
        write(fd2, buf, n);
    }
    close(fd1);
    close(fd2);
    return 0;
}