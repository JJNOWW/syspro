C
#include <stdio.h>
#include <string.h>
#include "copy.h"

#define MAXLINE 1000

int main() {
    char lines[5][MAXLINE];
    char temp[MAXLINE];
    int i = 0, j = 0;

    while (i < 5 && gets(lines[i]) != NULL) {
        i++;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4 - i; j++) {
            if (strlen(lines[j]) < strlen(lines[j+1])) {
                copy(lines[j], temp);
                copy(lines[j+1], lines[j]);
                copy(temp, lines[j+1]);
            }
        }
    }

    for (i = 0; i < 5; i++) {
        printf("%s\n", lines[i]);
    }

    return 0;
}
