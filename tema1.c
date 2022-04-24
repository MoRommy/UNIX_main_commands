#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesAndDirectories.c"
#include "commands.c"
#include "processInputLine.c"

int main () {
    char *buffer = malloc(MAX_INPUT_LINE_SIZE * sizeof(char));
    FILE *inputFile = stdin;
    fgets(buffer, MAX_INPUT_LINE_SIZE, inputFile);

    DirList home = createDirList(NULL, "home");
    DirList path = home;
	while (hasInput(buffer)) {
        processInputLine(buffer, &path);
        fgets(buffer, MAX_INPUT_LINE_SIZE, inputFile);
    }
    freeDir(home);
    free(buffer);
	return 0;
}
