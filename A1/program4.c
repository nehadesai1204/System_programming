#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main()
{
    char fname[100];
    struct stat sb;

    printf("Enter file name : ");
    scanf("%s", fname);

    if (stat(fname, &sb) == -1)
    {
        perror("stat failed");
        return -1;
    }

    printf("File Size    : %ld bytes\n", sb.st_size);
    printf("Inode No     : %ld\n", sb.st_ino);
    printf("Hard Links   : %ld\n", sb.st_nlink);
    printf("User ID      : %d\n", sb.st_uid);
    printf("Group ID     : %d\n", sb.st_gid);

    printf("File Type    : ");
    if (S_ISREG(sb.st_mode))
        printf("Regular File\n");
    else if (S_ISDIR(sb.st_mode))
        printf("Directory\n");
    else
        printf("Other\n");

    printf("Last Access  : %s", ctime(&sb.st_atime));
    printf("Last Modify  : %s", ctime(&sb.st_mtime));

    return 0;
}
