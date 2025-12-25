#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
    char srcdir[100], destdir[100];
    char srcpath[200], destpath[200];
    DIR *dp;
    struct dirent *entry;
    struct stat sb;
    int count = 0;

    printf("Enter source directory : ");
    scanf("%s", srcdir);

    printf("Enter destination directory : ");
    scanf("%s", destdir);

    dp = opendir(srcdir);
    if (dp == NULL)
    {
        perror("opendir failed");
        return -1;
    }

    while ((entry = readdir(dp)) != NULL)
    {
        sprintf(srcpath, "%s/%s", srcdir, entry->d_name);
        stat(srcpath, &sb);

        if (S_ISREG(sb.st_mode))
        {
            sprintf(destpath, "%s/%s", destdir, entry->d_name);
            rename(srcpath, destpath);
            count++;
        }
    }

    printf("Total files moved : %d\n", count);

    closedir(dp);
    return 0;
}
