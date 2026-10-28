#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char *, struct stat *, int, int, int);
int main(int argc, char **argv)
{
    DIR *dp;
    char *dir = ".";
    struct stat st;
    struct dirent *d;
    char path[BUFSIZ+1];
    int opt;
    int i = 0, p = 0, Q = 0;

    while ((opt = getopt(argc, argv, "ipQ")) != -1) {
        switch (opt) {
            case 'i':
                i = 1;
                break;
            case 'p':
                p = 1;
                break;
            case 'Q':
                Q = 1;
                break;
            default:
                fprintf(stderr, "How to use: %s [-i] [-p] [-Q] [directory]\n", argv[0]);
                exit(1);
        }
    }

    if (optind < argc)
        dir = argv[optind];

    if ((dp = opendir(dir)) == NULL) {
        perror(dir);
        exit(1);
    }

    while ((d = readdir(dp)) != NULL) {
        if (snprintf(path, sizeof(path), "%s/%s", dir, d->d_name)
            >= (int)sizeof(path))
            continue;

        if (lstat(path, &st) < 0)
            perror(path);
        else
            printStat(d->d_name, &st, i, p, Q);
    }

    closedir(dp);
    exit(0);
}

void printStat(char *file, struct stat *st, int i, int p, int Q)
{
    struct passwd *pw = getpwuid(st->st_uid);
    struct group *gr = getgrgid(st->st_gid);

    if (i)
        printf("%llu ", (unsigned long long)st->st_ino);

    printf("%5lld ", (long long)st->st_blocks);
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3lu ", (unsigned long)st->st_nlink);

    printf("%s %s ",
           pw ? pw->pw_name : "unknown",
           gr ? gr->gr_name : "unknown");

    printf("%9lld ", (long long)st->st_size);
    printf("%.12s ", ctime(&st->st_mtime)+4);

    if (Q)
        printf("\"");

    printf("%s", file);

    if (p && S_ISDIR(st->st_mode))
        printf("/");

    if (Q)
        printf("\"");

    printf("\n");
}
char type(mode_t mode)
{
    if (S_ISREG(mode)) return '-';
    if (S_ISDIR(mode)) return 'd';
    if (S_ISCHR(mode)) return 'c';
    if (S_ISBLK(mode)) return 'b';
    if (S_ISLNK(mode)) return 'l';
    if (S_ISFIFO(mode)) return 'p';
    if (S_ISSOCK(mode)) return 's';
    return '?';
}
char *perm(mode_t mode)
{
    static char perms[10];
    int i;

    strcpy(perms, "---------");

    for (i = 0; i < 3; i++) {
        if (mode & (S_IRUSR >> (i*3)))
            perms[i*3] = 'r';
        if (mode & (S_IWUSR >> (i*3)))
            perms[i*3+1] = 'w';
        if (mode & (S_IXUSR >> (i*3)))
            perms[i*3+2] = 'x';
    }

    return perms;
}
