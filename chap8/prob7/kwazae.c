#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

extern char **environ;

int main(int argc, char *argv[])
{
    int opt;

    if (argc < 2) {
        printf("Usage: %s [-e [env_name]] [-u] [-g] [-i] [-p]\n", argv[0]);
        return 1;
    }

    while ((opt = getopt(argc, argv, "e::ugip")) != -1) {
        switch (opt) {
            case 'e':
                if (optarg) {
                    char *val = getenv(optarg);
                    if (val) {
                        printf("%s = %s\n", optarg, val);
                    } else {
                        printf("Environment variable %s not found.\n", optarg);
                    }
                } else if (optind < argc && argv[optind][0] != '-') {
                    char *val = getenv(argv[optind]);
                    if (val) {
                        printf("%s = %s\n", argv[optind], val);
                    } else {
                        printf("Environment variable %s not found.\n", argv[optind]);
                    }
                    optind++;
                } else {
                    for (char **env = environ; *env != NULL; env++) {
                        printf("%s\n", *env);
                    }
                }
                break;

            case 'u':
                printf("Real User ID : %d(%s)\n", getuid(), getpwuid(getuid())->pw_name);
                printf("Effective User ID : %d(%s)\n", geteuid(), getpwuid(geteuid())->pw_name);
                break;

            case 'g':
                printf("Real Group ID : %d(%s)\n", getgid(), getgrgid(getgid())->gr_name);
                printf("Effective Group ID : %d(%s)\n", getegid(), getgrgid(getegid())->gr_name);
                break;

            case 'i':
                printf("Process ID : [%d]\n", getpid());
                break;

            case 'p':
                printf("Parent Process ID : [%d]\n", getppid());
                break;

            default:
                break;
        }
    }

    return 0;
}
