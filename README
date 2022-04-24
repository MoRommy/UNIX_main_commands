# Homework_1_IOCLA

#### Implementing files and directories - filesAndDirectories.c

##### Files

creteFileList - The function that allocates memory for a file, sets its parent directory, and then returns a pointer to it.
 
 freeFile - A function that takes a pointer to a file as a parameter and frees its name from memory, and then its structure.
 
freeFileList - Recursive function that receives a pointer to a list of files and releases the next file from it, then the current one.
 
removeFileFromList - A function that removes a file with a given name from a list. For this we considered two cases: The first: the one in which the first element in the list is the one sought. In this case, I typed the address of the next item in the list and deleted the current file. In the second case, the one in which the searched file was not the first in the list, I searched for it, and when I found it, I deleted it in a similar way.
 
printFileList - A function that displays in stdout the names of all files in a parent.

##### Directories

creatDirList - The function that allocates memory for a directory, sets its parent directory, and then returns a pointer to it.
 
freeDirList - Recursive function that receives a pointer to a list of directories and releases the first list of files, the list of child directories, the next directories in the list, and then the current directory. The function may seem complicated at first glance, but for an easier understanding I recommend following the algorithm on a graphical example.
 
freeDir - Function that takes as a parameter a pointer to a directory and frees from memory its name, the files it contains, the child directories (recursively through freeDirList), and then the related structure. I used this function during the theme, and that's why every time I say that I'm deleting a directory, I'll refer to this function.
 
removeDirFromList - A function that removes a file with a given name from a list. For this we considered two cases: The first: the one in which the first element in the list is the one sought. In this case, I typed the address of the next item in the list and deleted the current directory. In the second case, the one in which the searched directory was not the first in the list, I searched for it, and when I found it, I deleted it in a similar way.
 
printDirList - Function that displays in stdout the names of all child directories in a parent.

processInputLine - splits the line read from the keyboard into the command and parameters, and then executes the input.


#### Implementing processInputLine.c data reading

hasInput - if the line read differs from the stop command, then it returns 1, otherwise 0.

getNumberOfParameters - returns the number of parameters in the line read.

getCommand - returns the first word in the line read.

getParameters - returns the parameters of the line read

run - executes the given command, each time sending to the command its parameters and location in the file tree.


#### Main

In main I created the main directory "home", using the function "createDirList". The path variable points to this directory at the beginning, and will change its value along the way (when calling the "cd" function). So, as long as I was reading data from the keyboard (hasInput), I was processing it.


#### OS commands - commands.c

touch - I checked if the file already exists in the parent directory, and if not, I created the file and put it at the end of the parent list.

mkdir - I checked if the directory already exists in the parent directory, and if not, I created the directory and put it at the end of the parent list.
 
ls - I displayed the directory list with and the file list with printDir / FileList

rm - I checked if the file already exists in the parent directory, then I called the removeFileFromList function on the parent file list.
 
rmdir - I checked if the directory already exists in the parent directory, then I called the removeDirFromList function on the parent directory list.
 
cd - I changed the path variable, based on the address obtained by getDir.

pwd - A recursive function that calls itself the parent directory and then prints the name of the current directory.

stop - I replaced the implementation of the stop function with while (hasInput) in main

tree - I displayed all the directories, and for each one I called tree (thisChild, level + 1), to recursively call the function in all the directories in the system. Then I displayed all the files in that directory. \
 
mvFile - Function that receives a parent directory, the file address and its new name. First I update the file name, delete it from the starting position, and then add it to the end of the parent file list.
 
mvDir - Function that receives a parent directory, the directory address and its new name. First I update the principal's name, delete it from the starting position, and then add it to the end of the parent directory list.

mv - I checked if the file / directory already exists in the parent directory, and if not, I saved the corresponding address in a variable, using getDir and getFile, and called mvDir / mvFile on it.
