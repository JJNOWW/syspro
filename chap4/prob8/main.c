#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    FILE *fp;

    if (argc != 2) {
        fprintf(stderr, "How to use: %s [stdin|stdout|stderr|FileName]\n", argv[0]);
        exit(1);
    }

    if (strcmp(argv[1], "stdin") == 0) {
        fp = stdin;
        fgetc(fp);
    } else if (strcmp(argv[1], "stdout") == 0) {
        fp = stdout;
        fputc(' ', fp);
    } else if (strcmp(argv[1], "stderr") == 0) {
        fp = stderr;
        fputc(' ', fp);
    } else {
        fp = fopen(argv[1], "r");
        if (fp == NULL) {
            fprintf(stderr, "Error Open File\n");
            exit(2);
        }
        fgetc(fp);
    }

    if (fp->_flags & 0x0002) {
        printf("Unbuffered\n");
    } else if (fp->_flags & 0x0200) {
        printf("Line buffered\n");
    } else {
        printf("Fully buffered\n");
    }

    if (fp != stdin && fp != stdout && fp != stderr) {
        fclose(fp);
    }

    return 0;
}
