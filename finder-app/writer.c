#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(int argc, char *argv[]) {

    openlog(NULL, 0, LOG_USER);
    
    if (argc != 3) {
        syslog(LOG_ERR, "Usage: %s <file> <content>", argv[0]);
        return 1;
    }

    syslog(LOG_INFO, "Writing %s to file %s", argv[2], argv[1]);

    FILE *file;

    file = fopen(argv[1], "w");

    if (file == NULL) {
        syslog(LOG_ERR, "Error opening file %s", argv[1]);
        return 1;
    }

    fprintf(file, "%s", argv[2]);

    fclose(file);

    return 0;
}
