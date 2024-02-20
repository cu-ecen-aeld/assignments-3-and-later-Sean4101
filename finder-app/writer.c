#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        printf("Usage: %s <writefile> <writestr>\n", argv[0]);
        return 1;
    }

    FILE *file;

    file = fopen(argv[1], "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(file, "%s", argv[2]);

    fclose(file);

    return 0;
}
