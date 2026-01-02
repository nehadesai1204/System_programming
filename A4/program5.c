#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd;
    char ch;
    off_t size;

    if (argc != 2)
    {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    size = lseek(fd, 0, SEEK_END);

    while (size > 0)
    {
        lseek(fd, size = size-1, SEEK_SET);
        read(fd, &ch, 1);
        write(1, &ch, 1);
    }

    close(fd);
    return 0;
}