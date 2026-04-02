#include <stdio.h>
#include <string.h>

#define MAX_LINE 1024
#ifndef SRC_DIR
#define SRC_DIR "."
#endif

int main() {
    FILE *file = fopen(SRC_DIR, "r");
    if (!file) {
        perror("Could not open file");
        return 1;
    }

    char line[MAX_LINE];
    int implemented = 0;
    int not_implemented = 0;

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "@Implemented")) {
            implemented++;
        }
        if (strstr(line, "@NotImplemented")) {
            not_implemented++;
        }
    }

    fclose(file);

    int total = implemented + not_implemented;

    printf("Implemented: %d\n", implemented);
    printf("Not Implemented: %d\n", not_implemented);

    if (total > 0) {
        printf("Progress: %.2f%%\n",
               (implemented * 100.0) / total);
    } else {
        printf("No markers found.\n");
    }

    return 0;
}