#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
    char dname[100], path[200];
    DIR *dp;
    struct dirent *entry;
    struct stat sb;

    printf("Enter directory name : ");
    scanf("%s", dname);

    dp = opendir(dname);
    if (dp == NULL)
    {
        perror("opendir failed");
        return -1;
    }

    while ((entry = readdir(dp)) != NULL)
    {
        sprintf(path, "%s/%s", dname, entry->d_name);
        lstat(path, &sb);

        printf("%s : ", entry->d_name);

        if (S_ISREG(sb.st_mode)) printf("Regular File\n");
        else if (S_ISDIR(sb.st_mode)) printf("Directory\n");
        else if (S_ISLNK(sb.st_mode)) printf("Link\n");
        else if (S_ISFIFO(sb.st_mode)) printf("FIFO\n");
        else if (S_ISSOCK(sb.st_mode)) printf("Socket\n");
        else if (S_ISCHR(sb.st_mode)) printf("Char Device\n");
        else if (S_ISBLK(sb.st_mode)) printf("Block Device\n");
    }

    closedir(dp);
    return 0;
}
