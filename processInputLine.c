#define MAX_INPUT_LINE_SIZE 300
#define MAX_COMMAND_SIZE 50
#define MAX_PARAMETER_SIZE 50

int getNumberOfParameters(const char *buffer) {
    int k = 0;
    for (int i = 0; i < strlen(buffer); i++)
        if (buffer[i] == ' ')
            k++;
    return k;
}

char **getParameters(int numberOfParameters) {
    char *p;
    char **parameters = malloc(numberOfParameters * sizeof(char*));
    for (int i = 0; i < numberOfParameters; i++) {
        p = strtok(NULL, " \n");
        parameters[i] = malloc(MAX_PARAMETER_SIZE * sizeof(char));
        strcpy(parameters[i], p);
    }
    return parameters;
}

char *getCommand(char *buffer) {
    char *command = malloc(MAX_COMMAND_SIZE);
    char *p = strtok(buffer, " \n");
    strcpy(command, p);
    return command;
}

void freeInput(char *command, char **parameters, int numberOfParameters) {
    for (int i = 0; i < numberOfParameters; i++)
        free(parameters[i]);
    free(parameters);
    free(command);
}
char hasInput(char *buffer) {
    if (strcmp(buffer, "stop\n") == 0)
        return 0;
    return 1;
}

void run(DirList *path, char *command, char **parameters) {
    if (strcmp(command, "touch") == 0) {
        touch(*path, parameters[0]);
    }
    else if (strcmp(command, "mkdir") == 0) {
        mkdir(*path, parameters[0]);
    }
    else if (strcmp(command, "ls") == 0) {
        ls(*path);
    }
    else if (strcmp(command, "rm") == 0) {
        rm(*path, parameters[0]);
    }
    else if (strcmp(command, "rmdir") == 0) {
        rmdir(*path, parameters[0]);
    }
    else if (strcmp(command, "cd") == 0) {
        cd(path, parameters[0]);
    }
    else if (strcmp(command, "tree") == 0) {
        tree(*path, 0);
    }
    else if (strcmp(command, "pwd") == 0) {
        pwd(*path);
    }
    else if (strcmp(command, "mv") == 0) {
        mv(*path, parameters[0], parameters[1]);
    }
}

void processInputLine(char *buffer, DirList *path) {
    int numberOfParameters = getNumberOfParameters(buffer);
    char *command = getCommand(buffer);
    char **parameters = getParameters(numberOfParameters);

    run(path, command, parameters);

    freeInput(command, parameters, numberOfParameters);
}
