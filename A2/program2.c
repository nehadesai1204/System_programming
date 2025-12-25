#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char fname[100];
    char data[200];
    int fd, bytes;

    printf("Enter file name : ");
    scanf("%s", fname);

    printf("Enter string : ");
    scanf(" %[^\n]", data);

    fd = open(fname, O_WRONLY | O_APPEND | O_CREAT, 0777);
    if (fd == -1)
    {
        perror("Error opening file");
        return -1;
    }

    bytes = write(fd, data, strlen(data));
    printf("Bytes written : %d\n", bytes);

    close(fd);
    return 0;
}
