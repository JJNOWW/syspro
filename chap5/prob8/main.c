#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_LINES 100
#define MAX_BUF 256

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("File open error");
        exit(1);
    }

    printf("File read success\n");

    char savedText[MAX_LINES][MAX_BUF];
    char buf;
    int line = 0, col = 0;

    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            savedText[line][col] = '\0';
            line++;
            col = 0;
        } else {
            savedText[line][col++] = buf;
        }
    }
    
    if (col > 0) {
        savedText[line][col] = '\0';
        line++;
    }

    close(fd);

    int total_lines = line;
    printf("Total Line : %d\n", total_lines);
    printf("You can choose 1 ~ %d Line\n", total_lines);

    char input[50];
    printf("Pls 'Enter' the line to select : ");
    if (scanf("%s", input) != 1) return 0;

    if (strcmp(input, "*") == 0) {
        for (int i = 0; i < total_lines; i++) {
            printf("%s\n", savedText[i]);
        }
    } 
    else if (strchr(input, '-') != NULL) {
        int start, end;
        sscanf(input, "%d-%d", &start, &end);
        for (int i = start - 1; i < end && i < total_lines; i++) {
            if (i >= 0) printf("%s\n", savedText[i]);
        }
    } 
    else if (strchr(input, ',') != NULL) {
        char *ptr = strtok(input, ",");
        while (ptr != NULL) {
            int line_num = atoi(ptr);
            if (line_num >= 1 && line_num <= total_lines) {
                printf("%s\n", savedText[line_num - 1]);
            }
            ptr = strtok(NULL, ",");
        }
    } 
    else {
        int line_num = atoi(input);
        if (line_num >= 1 && line_num <= total_lines) {
            printf("%s\n", savedText[line_num - 1]);
        }
    }

    return 0;
}
