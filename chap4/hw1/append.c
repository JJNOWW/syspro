#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp1, *fp2;
    int c;

    if (argc != 3) {
        exit(1);
    }

    if ((fp1 = fopen(argv[1], "r")) == NULL) {
    }
    if ((fp2 = fopen(argv[2], "a")) == NULL) {
        fclose(fp1);
        exit(3);
    }
    while ((c = fgetc(fp1)) != EOF) {
        fputc(c, fp2);
    }

    fclose(fp1);
    fclose(fp2);

    return 0;
}
