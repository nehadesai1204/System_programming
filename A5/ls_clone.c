#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

void print_permissions(mode_t mode)
{
    char perm[11];

    perm[0] = S_ISDIR(mode) ? 'd' :
              S_ISLNK(mode) ? 'l' : '-';

    perm[1] = (mode & S_IRUSR) ? 'r' : '-';
    perm[2] = (mode & S_IWUSR) ? 'w' : '-';
    perm[3] = (mode & S_IXUSR) ? 'x' : '-';
    perm[4] = (mode & S_IRGRP) ? 'r' : '-';
    perm[5] = (mode & S_IWGRP) ? 'w' : '-';
    perm[6] = (mode & S_IXGRP) ? 'x' : '-';
    perm[7] = (mode & S_IROTH) ? 'r' : '-';
    perm[8] = (mode & S_IWOTH) ? 'w' : '-';
    perm[9] = (mode & S_IXOTH) ? 'x' : '-';
    perm[10] = '\0';

    printf("%s", perm);
}

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *entry;
    struct stat sb;
    char path[1024];

    if (argc != 2)
    {
        printf("Usage: %s directory_path\n", argv[0]);
        return 1;
    }

    dp = opendir(argv[1]);
    if (dp == NULL)
    {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dp)) != NULL)
    {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
        {
            continue;
        }
        snprintf(path, sizeof(path), "%s/%s", argv[1], entry->d_name);

        lstat(path, &sb);

        printf("\nName: %s\n", entry->d_name);

        if (S_ISREG(sb.st_mode)) printf("Type: File\n");
        else if (S_ISDIR(sb.st_mode)) printf("Type: Directory\n");
        else if (S_ISLNK(sb.st_mode)) printf("Type: Symlink\n");
        else printf("Type: Other\n");

        printf("Size: %ld bytes\n", sb.st_size);
        printf("Permissions: ");
        print_permissions(sb.st_mode);

        printf("\nLast Modified: %s", ctime(&sb.st_mtime));
    }

    closedir(dp);
    return 0;
}
