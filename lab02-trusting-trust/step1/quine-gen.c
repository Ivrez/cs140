#include <stdio.h>

int main() {
    FILE *file = stdin;  // stdin for input file
    char line[1024];

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    return 0;
}