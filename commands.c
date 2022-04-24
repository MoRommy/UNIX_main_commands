int fileAlreadyExists(Dir* parent, char *name) {
	File* childrenFiles = parent->head_children_files;
	while (childrenFiles) {
		if (strcmp(childrenFiles->name, name) == 0)
			return 1;
		childrenFiles = childrenFiles->next;
	}
	return 0;
}

int dirAlreadyExists(Dir* parent, char *name) {
	Dir* childrenDirs = parent->head_children_dirs;
	while (childrenDirs) {
		if (strcmp(childrenDirs->name, name) == 0)
			return 1;
		childrenDirs = childrenDirs->next;
	}
	return 0;
}

FileList getLastFileChildren(DirList parent) {
	FileList childrenFiles = parent->head_children_files;
	FileList last = childrenFiles;
	while (childrenFiles) {
		last = childrenFiles;
		childrenFiles = childrenFiles->next;
	}
	return last;
}

DirList getLastDirChildren(DirList parent) {
	DirList childrenDirs = parent->head_children_dirs;
	DirList last = childrenDirs;
	while (childrenDirs) {
		last = childrenDirs;
		childrenDirs = childrenDirs->next;
	}
	return last;
}

void touch (Dir* parent, char* name) {
	if (!parent) {
		printf("Cannot touch in a NULL path: %p\n", parent);
		return;
	}

	if (fileAlreadyExists(parent, name)) {
		printf("File already exists\n");
		return;
	}

	FileList file = createFileList(parent, name);
	if (parent->head_children_files == NULL) {
		parent->head_children_files = file;
		return;
	}
	getLastFileChildren(parent)->next = file;

}

void mkdir (Dir* parent, char* name) {
	if (!parent) {
		printf("Cannot mkdir in a NULL path: %p\n", parent);
		return;
	}

	if (dirAlreadyExists(parent, name)) {
		printf("Directory already exists\n");
		return;
	}

	DirList dir = createDirList(parent, name);
	if (parent->head_children_dirs == NULL) {
		parent->head_children_dirs = dir;
		return;
	}
	getLastDirChildren(parent)->next = dir;
}

void ls (Dir* parent) {
	printDirList(parent);
	printFileList(parent);
}

void rm (Dir* parent, char* name) {
	if (!parent) {
		printf("Cannot rm from NULL parent\n");
		return;
	}
	if (!fileAlreadyExists(parent, name)) {
		printf("Could not find the file\n");
		return;
	}
	removeFileFromList(&parent->head_children_files, name);
}

void rmdir (Dir* parent, char* name) {
	if (!parent) {
		printf("Cannot rmdir from NULL parent\n");
		return;
	}
	if (!dirAlreadyExists(parent, name)) {
		printf("Could not find the dir\n");
		return;
	}
	removeDirFromList(&parent->head_children_dirs, name);
}

Dir* getDir(Dir* parent, char *name) {
	Dir *childrenDirs = parent->head_children_dirs;
	while(childrenDirs) {
		if (strcmp(childrenDirs->name, name) == 0)
			return childrenDirs;
		childrenDirs = childrenDirs->next;
	}
	return NULL;
}

FileList getFile(Dir* parent, char *name) {
	FileList childrenFiles = parent->head_children_files;
	while(childrenFiles) {
		if (strcmp(childrenFiles->name, name) == 0)
			return childrenFiles;
		childrenFiles = childrenFiles->next;
	}
	return NULL;
}

void cd(Dir** target, char *name) {
	if (strcmp(name, "..") == 0) {
		if ((*target)->parent != NULL)
			*target = (*target)->parent;
		return;
	}
	if (!dirAlreadyExists(*target, name)) {
		printf("No directories found!\n");
		return;
	}
	*target = getDir(*target, name);
}

char *pwd (Dir* target) {
	if (target) {
		pwd(target->parent);
		printf("/%s", target->name);
	}
    return 0;
}

void stop (Dir* target) {}

void tree (Dir* parent, int level) {
	DirList childrenDirs = parent->head_children_dirs;
	while (childrenDirs) {
		for (int i = 0; i < level; i++)
			printf("    ");
		printf("%s\n", childrenDirs->name);
		tree(childrenDirs, level + 1);
		childrenDirs = childrenDirs->next;
	}

	FileList childrenFiles = parent->head_children_files;
	while (childrenFiles) {
		for (int i = 0; i < level; i++)
			printf("    ");
		printf("%s\n", childrenFiles->name);
		childrenFiles = childrenFiles->next;
	}
}

Dir *addDir(Dir* childrenDirs, Dir* dir) {
	if (childrenDirs == NULL)
		return dir;
	Dir *head = childrenDirs;
	while (childrenDirs->next)
		childrenDirs = childrenDirs->next;
	childrenDirs->next = dir;
	return head;
}

void mvDir(Dir* parent, DirList dir, char *newname) {
	strcpy(dir->name, newname);
	Dir *childrenDirs = parent->head_children_dirs;
	if (childrenDirs == dir) {
		parent->head_children_dirs = addDir(childrenDirs->next, dir);
		dir->next = NULL;
		return;
	}

	Dir *head = childrenDirs;
	Dir *last = childrenDirs;
	while (childrenDirs != dir) {
		last = childrenDirs;
		childrenDirs = childrenDirs->next;
	}
	last->next = childrenDirs->next;
	parent->head_children_dirs = addDir(head, dir);
	dir->next = NULL;
}


FileList addFile(FileList files, FileList file) {
	if (files == NULL)
		return file;
	FileList head = files;
	while (files->next)
		files = files->next;
	files->next = file;
	return head;
}

void mvFile(Dir* parent, FileList file, char *newname) {
	strcpy(file->name, newname);
	FileList files = parent->head_children_files;
	if (files == file) {
		parent->head_children_files = addFile(files->next, file);
		file->next = NULL;
		return;
	}

	FileList tmp = files;
	FileList last = files;
	while (tmp != file) {
		last = tmp;
		tmp = tmp->next;
	}
	last->next = tmp->next;
	parent->head_children_files = addFile(files, file);
	file->next = NULL;
}



void mv(Dir* parent, char *oldname, char *newname) {
	if (fileAlreadyExists(parent, newname) || dirAlreadyExists(parent, newname)) {
		printf("File/Director already exists\n");
		return;
	}
	DirList dir = getDir(parent, oldname);
	FileList file = getFile(parent, oldname);
	if (dir) {
		mvDir(parent, dir, newname);
		return;
	}
	if (file) {
		mvFile(parent, file, newname);
		return;
	}
	printf("File/Director not found\n");
}
