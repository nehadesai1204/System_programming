#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

void print_tree(const char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat sb;
    char path[1024];

    dp = opendir(dir);
    if (!dp) return;

    while ((entry = readdir(dp)) != NULL)
    {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);
        lstat(path, &sb);

        for (int i = 0; i < depth; i++)
            printf("  ");

        if (S_ISDIR(sb.st_mode))
        {
            printf("[D] %s\n", entry->d_name);
            print_tree(path, depth + 1);
        }
        else if (S_ISREG(sb.st_mode))
        {
            printf("[F] %s\n", entry->d_name);
        }
        else if (S_ISLNK(sb.st_mode))
        {
            printf("[L] %s\n", entry->d_name);
        }
    }

    closedir(dp);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s directory\n", argv[0]);
        return 1;
    }

    printf("%s/\n", argv[1]);
    print_tree(argv[1], 1);
    return 0;
}
