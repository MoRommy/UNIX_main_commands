struct Dir;
struct File;

typedef struct Dir {
    char *name;
    struct Dir* parent;
    struct File* head_children_files;
    struct Dir* head_children_dirs;
    struct Dir* next;
} Dir, *DirList;

typedef struct File {
    char *name;
    struct Dir* parent;
    struct File* next;
} File, *FileList;

FileList createFileList(Dir* parent, char *name) {
    FileList fileList = (FileList) malloc(sizeof(File));
    fileList->name = malloc(sizeof(name) + 1);
    strcpy(fileList->name, name);
    fileList->parent = parent;
    fileList->next = NULL;
    return fileList;
}

DirList createDirList(Dir* parent, char *name) {
    DirList dirList = (DirList) malloc(sizeof(Dir));
    dirList->name = malloc(sizeof(name) + 1);
    strcpy(dirList->name, name);
    dirList->parent = parent;
    dirList->head_children_dirs = NULL;
    dirList->head_children_files = NULL;
    dirList->next = NULL;
    return dirList;
}

void freeFile(FileList node) {
    if (node) {
        free(node->name);
        free(node);
    }
}

void freeFileList(FileList fileList) {
    if (fileList) {
        freeFileList(fileList->next);
        freeFile(fileList);
    }
}

void freeDir(DirList node);
void freeDirList(DirList dirList) {
    if (dirList) {
        free(dirList->name);
        freeFileList(dirList->head_children_files);
        freeDirList(dirList->head_children_dirs);
        freeDirList(dirList->next);
        free(dirList);
    }
}

void freeDir(DirList node) {
    if (node) {
        free(node->name);
        freeFileList(node->head_children_files);
        freeDirList(node->head_children_dirs);
        free(node);
    }
}

void removeFileFromList(FileList *fileList, char *fileName) {
    if (strcmp((*fileList)->name, fileName) == 0) {
        FileList tmp = *fileList;
        *fileList = (*fileList)->next;
        freeFile(tmp);
        return;
    }

    FileList current = *fileList, last = *fileList;
    while (current) {
        if (strcmp(current->name, fileName) == 0) {
            FileList tmp = current->next;
            freeFile(current);
            last->next = tmp;
            return;
        }
        last = current;
        current = current->next;
    }
}

void removeDirFromList(DirList *fileList, char *fileName) {
    if (strcmp((*fileList)->name, fileName) == 0) {
        DirList tmp = *fileList;
        *fileList = (*fileList)->next;
        freeDir(tmp);
        return;
    }

    DirList current = *fileList, last = *fileList;
    while (current) {
        if (strcmp(current->name, fileName) == 0) {
            DirList tmp = current->next;
            freeDir(current);
            last->next = tmp;
            return;
        }
        last = current;
        current = current->next;
    }
}

void printFileListHelper(FileList fileList) {
    if (fileList) {
        printf("%s\n", fileList->name);
        printFileListHelper(fileList->next);
    }
}

void printFileList(DirList parent) {
    if (parent)
        printFileListHelper(parent->head_children_files);
}

void printDirListHelper(DirList dirList) {
    if (dirList) {
        printf("%s\n", dirList->name);
        printDirListHelper(dirList->next);
    }
}

void printDirList(DirList parent) {
    if (parent)
        printDirListHelper(parent->head_children_dirs);
}

