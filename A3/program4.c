#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main()
{
    char dname[100], path[200];
    DIR *dp;
    struct dirent *entry;
    struct stat sb;
    int count = 0;

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
        stat(path, &sb);

        if (S_ISREG(sb.st_mode) && sb.st_size == 0)
        {
            unlink(path);
            printf("Deleted : %s\n", entry->d_name);
            count++;
        }
    }

    printf("Total files deleted : %d\n", count);

    closedir(dp);
    return 0;
}
