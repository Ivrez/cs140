#include <stdio.h>

int main() {
    FILE *file = stdin;  // stdin for input file

    int maxArraySize = 4096;
    char realProg[maxArraySize];

    int i = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF && i < maxArraySize - 1) {
        realProg[i++] = ch;
    }
    realProg[i] = '\0';

    printf("char prog[] = {\n");
	for(i = 0; realProg[i]; i++)
		printf("\t%d,%c", realProg[i], (i+1)%8==0 ? '\n' : ' ');
    printf("0 };\n");
    printf("%s", realProg);

    return 0;
}