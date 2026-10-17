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

    for (int i = line - 1; i >= 0; i--) {
        printf("%s\n", savedText[i]);
    }

    return 0;
}
