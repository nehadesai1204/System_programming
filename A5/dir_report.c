#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

long total_files = 0;
long total_dirs = 0;
long total_size = 0;
long max_size = 0;
char largest_file[1024];

void scan_dir(const char *dir)
{
    DIR *dp;
    struct dirent *entry;
    struct stat sb;
    char path[1024];

    dp = opendir(dir);
    if (!dp) return;

    total_dirs++;

    while ((entry = readdir(dp)) != NULL)
    {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
        {
            continue;
        }
        
        snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);
        lstat(path, &sb);

        if (S_ISDIR(sb.st_mode))
        {
            scan_dir(path);
        }
        else if (S_ISREG(sb.st_mode))
        {
            total_files++;
            total_size += sb.st_size;

            if (sb.st_size > max_size)
            {
                max_size = sb.st_size;
                strcpy(largest_file, entry->d_name);
            }
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

    scan_dir(argv[1]);

    printf("\nFiles: %ld\n", total_files);
    printf("Dirs : %ld\n", total_dirs);
    printf("Total Size: %ld bytes\n", total_size);
    printf("Largest: %s (%ld bytes)\n", largest_file, max_size);

    return 0;
}
