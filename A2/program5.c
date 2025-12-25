#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
    char dname[100], path[200], maxfile[100] = "";
    DIR *dp;
    struct dirent *entry;
    struct stat sb;
    long maxsize = 0;

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

        if (S_ISREG(sb.st_mode))
        {
            if (sb.st_size > maxsize)
            {
                maxsize = sb.st_size;
                strcpy(maxfile, entry->d_name);
            }
        }
    }

    printf("Largest File : %s\n", maxfile);
    printf("Size : %ld bytes\n", maxsize);

    closedir(dp);
    return 0;
}
