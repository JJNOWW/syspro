#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_stream(FILE *fp, int number_lines, int *line_count) {
    int c;
    int is_new_line = 1;
    
    while ((c = fgetc(fp)) != EOF) {
        if (number_lines && is_new_line) {
            printf("%6d ", (*line_count)++);
            is_new_line = 0;
        }
        putchar(c);
        if (c == '\n') {
            is_new_line = 1;
        }
    }
}

int main(int argc, char *argv[]) {
    int i;
    int number_lines = 0;
    int line_count = 1;
    int start_idx = 1;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        number_lines = 1;
        start_idx = 2;
    }

    if (start_idx == argc) {
        process_stream(stdin, number_lines, &line_count);
    } else {
        for (i = start_idx; i < argc; i++) {
            FILE *fp = fopen(argv[i], "r");
            if (fp == NULL) continue;
            
            process_stream(fp, number_lines, &line_count);
            fclose(fp);
        }
    }

    return 0;
}
