#include <stdio.h>
#include <unistd.h>

int main()
{
    char fname[100], perm;

    printf("Enter file name : ");
    scanf("%s", fname);

    printf("Enter permission to check (R/W/X) : ");
    scanf(" %c", &perm);

    int mode;
    if (perm == 'R' || perm == 'r')
        mode = R_OK;
    else if (perm == 'W' || perm == 'w')
        mode = W_OK;
    else if (perm == 'X' || perm == 'x')
        mode = X_OK;
    else
    {
        printf("Invalid permission\n");
        return -1;
    }

    if (access(fname, mode) == 0)
        printf("Accessible\n");
    else
        perror("Not Accessible");

    return 0;
}
