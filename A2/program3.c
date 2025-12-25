#include <stdio.h>
#include <dirent.h>

int main()
{
    char dname[100];
    DIR *dp;
    struct dirent *entry;

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
        if (entry->d_name[0] != '.')
            printf("%s\n", entry->d_name);
    }

    closedir(dp);
    return 0;
}
