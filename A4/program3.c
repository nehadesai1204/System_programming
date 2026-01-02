#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd1, fd2;
    char buf[100];
    int n;
    off_t offset = 0;

    if (argc != 3)
    {
        printf("Usage: %s source destination\n", argv[0]);
        return 1;
    }

    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    while ((n = pread(fd1, buf, sizeof(buf), offset)) > 0)
    {
        pwrite(fd2, buf, n, offset);
        offset = offset + n;
    }

    close(fd1);
    close(fd2);
    return 0;
}