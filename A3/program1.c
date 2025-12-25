#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    char src[100], dest[100];
    int fdsrc, fddest;
    char buffer[1024];
    int bytes;
    struct stat sb;

    printf("Enter source file : ");
    scanf("%s", src);

    printf("Enter destination file : ");
    scanf("%s", dest);

    fdsrc = open(src, O_RDONLY);
    if (fdsrc == -1)
    {
        perror("Source open failed");
        return -1;
    }

    stat(src, &sb);

    fddest = open(dest, O_WRONLY | O_CREAT | O_TRUNC, sb.st_mode);
    if (fddest == -1)
    {
        perror("Destination open failed");
        close(fdsrc);
        return -1;
    }

    while ((bytes = read(fdsrc, buffer, sizeof(buffer))) > 0)
    {
        write(fddest, buffer, bytes);
    }

    printf("File copied successfully\n");

    close(fdsrc);
    close(fddest);
    return 0;
}
