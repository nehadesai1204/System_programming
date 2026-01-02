#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd_out, fd_in;
    char buf[1024];
    int n, i;

    if (argc < 3)
    {
        printf("Usage: %s output file1 file2 ...\n", argv[0]);
        return 1;
    }

    fd_out = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    for (i = 2; i < argc; i++)
    {
        fd_in = open(argv[i], O_RDONLY);

        while ((n = read(fd_in, buf, sizeof(buf))) > 0)
        {
            write(fd_out, buf, n);
        }
        close(fd_in);
    }

    close(fd_out);
    return 0;
}