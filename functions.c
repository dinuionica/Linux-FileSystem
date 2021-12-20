/* Copyright 2021 Dinu Ion-Irinel */

#include "functions.h"

/* the function that creates root directory */
Dir* create_root() {
    /* memory allocation for root directory */
    Dir* root = malloc(sizeof(*root));
    DIE(root == NULL, "Allocation error");

    /* memory allocation and name creation for the directory */
    root->name = malloc(sizeof(char) * NAME_SIZE_ROOT);
    DIE(root->name == NULL, "Allocation error");
    memcpy(root->name, "home", NAME_SIZE_ROOT);

    /* redirecting pointers */
    root->parent = NULL;
    root->head_children_dirs = NULL;
    root->head_children_files = NULL;

    return root;
}

/* the function that checks if a directory exists in another directory */
int check_exist_directory(Dir* parent, char* name) {
    /* we go through the list of directories and if 
     * we find the desired directory we return true
     */
    Dir* current_directory = parent->head_children_dirs;
    while (current_directory != NULL) {
        if (strcmp(current_directory->name, name) == 0) {
            return 1;
        }
        current_directory = current_directory->next;
    }
    /* return false if we didn't find the directory */
    return 0;
}

/* the function that checks if a file exists in a directory */
int check_exist_file(Dir* parent, char* name) {
    /* we go through the list of directories and if 
     * we find the desired file we return true
     */
    File* current_file = parent->head_children_files;
    while (current_file != NULL) {
        if (strcmp(current_file->name, name) == 0) {
            return 1;
        }
        current_file = current_file->next;
    }
    /* return false if we didn't find the file */
    return 0;
}

/* the function that checks if a file or a directory exists in a directory */
int check_exist(Dir* parent, char* name) {
    int exist_file = check_exist_file(parent, name);
    int exist_directory = check_exist_directory(parent, name);

    /* if there is a file or directory with the desired name we return true */
    if (exist_file == 1 || exist_directory == 1) {
        return 1;
    }
    return 0;
}

/* the function that creates a new file in the current directory */
void touch(Dir* parent, char* name) {
    /* check if there is a file or directory with the same name */
    if (check_exist(parent, name) == 1) {
        printf("File already exists\n");
        return;
    }
    /* creating the structure for new file */
    File* new_file = malloc(sizeof(*new_file));
    DIE(new_file == NULL, "Allocation error");

    /* memory allocation for the name of the file */
    new_file->name = malloc(sizeof(char) * (strlen(name) + 1));
    DIE(new_file->name == NULL, "Allocation error");
    memcpy(new_file->name, name, (strlen(name) + 1));

    /* redirecting pointers */
    new_file->next = NULL;
    new_file->parent = parent;

    /* if the file list does not contain any files, 
     * the current file becomes the head of the list
     */
    if (parent->head_children_files == NULL) {
        parent->head_children_files = new_file;
        return;
    } else {
        File* current_file = parent->head_children_files;
        while (current_file->next != NULL) {
            current_file = current_file->next;
        }
        /* if the list contains items, we add the file to the end of the list */
        current_file->next = new_file;
    }
}

/* the function that creates a new directory in the current directory */
void mkdir(Dir* parent, char* name) {
    /* check if there is a file or directory with the same name */
    if (check_exist(parent, name) == 1) {
        printf("Directory already exists\n");
        return;
    }
    /* creating the structure for new directory */
    Dir* new_directory = malloc(sizeof(*new_directory));
    DIE(new_directory == NULL, "Allocation error");

    /* memory allocation for the new name of directory */
    new_directory->name = malloc(sizeof(char) * (strlen(name) + 1));
    DIE(new_directory->name == NULL, "Allocation error");
    memcpy(new_directory->name, name, (strlen(name) + 1));

    /* redirecting pointers */
    new_directory->parent = parent;
    new_directory->head_children_files = NULL;
    new_directory->next = NULL;
    new_directory->head_children_dirs = NULL;

    /* if the directory list does not contain any directories
     * the current directory becomes the head of the list
     */
    if (parent->head_children_dirs == NULL) {
        parent->head_children_dirs = new_directory;
    } else {
        Dir* current_directory = parent->head_children_dirs;
        while (current_directory->next != NULL) {
            current_directory = current_directory->next;
        }
        /* if the list contains directories, we add the directory to the end */
        current_directory->next = new_directory;
    }
}

/* the function that displays all files and directories */
void ls(Dir* parent) {
    /* if the directory list is not empty,the list
     * is scrolled and each element is displayed
     */
    if (parent->head_children_dirs != NULL) {
        Dir* current_directory = parent->head_children_dirs;
        while (current_directory != NULL) {
            printf("%s\n", current_directory->name);
            current_directory = current_directory->next;
        }
    }

    /* if the file list is not empty, the list
     * is scrolled and each element is displayed
     */
    if (parent->head_children_files != NULL) {
        File* current_file = parent->head_children_files;
        while (current_file != NULL) {
            printf("%s\n", current_file->name);
            current_file = current_file->next;
        }
    }
}

/* the function that removes a file from current directory */
void rm(Dir* parent, char* name) {
    /* check if there is a file or directory with the desired name */
    if (check_exist_file(parent, name) == 0) {
        printf("Could not find the file\n");
        return;
    }

    /* if the desired file is at the beggining, the list
     * header is updated and the memory is freed
     */
    if (strcmp(parent->head_children_files->name, name) == 0) {
        File* temp_file = parent->head_children_files;
        parent->head_children_files = temp_file->next;
        free(temp_file->name);
        temp_file->next = NULL;
        temp_file->parent = NULL;
        free(temp_file);
    } else {
        /* otherwise, the list is scrolled, the desired
         * element is removed and the memory is freed
         */
        File* current_file = parent->head_children_files;
        File* prev_file = NULL;
        while (current_file != NULL) {
            if (strcmp(current_file->name, name) == 0) {
                /* reconnect pointers */
                prev_file->next = current_file->next;
                /* free the desired file */
                free(current_file->name);
                current_file->next = NULL;
                current_file->parent = NULL;
                free(current_file);
                return;
            }
            prev_file = current_file;
            current_file = current_file->next;
        }
    }
}

/* the recursive function that removes a directory and its contents */
void __rmdir(Dir* parent) {
    if (parent->head_children_dirs != NULL) {
        /* go through each directory */
        Dir* current_directory = parent->head_children_dirs;
        while (current_directory != NULL) {
            Dir* temp_directory = current_directory;
            current_directory = current_directory->next;
            /* the recursive function is called for the desired directory */
            __rmdir(temp_directory);
            /* free memory for the current directory */
            free(temp_directory->name);
            temp_directory->next = NULL;
            temp_directory->parent = NULL;
            temp_directory->head_children_dirs = NULL;
            temp_directory->head_children_files = NULL;
            free(temp_directory);
        }
    }

    /* go through each files and remove it */
    File* current_file = parent->head_children_files;
    while (current_file != NULL) {
        File* temp_file = current_file;
        current_file = temp_file->next;
        /* free memory for the current file */
        free(temp_file->name);
        temp_file->next = NULL;
        temp_file->parent = NULL;
        free(temp_file);
    }
}

/* the function that removes a directory */
void rmdir(Dir* parent, char* name) {
    /* check if there is a file or directory with the same name */
    if (check_exist_directory(parent, name) == 0) {
        printf("Could not find the dir\n");
        return;
    }

    Dir* current_directory = parent->head_children_dirs;
    /* if the desired file is the head of the list, we update the 
     * head, then we recursively delete everything it contains
     * and at the end we free the memory allocated for it 
     */
    if (strcmp(current_directory->name, name) == 0) {
        parent->head_children_dirs = current_directory->next;
        __rmdir(current_directory);

        free(current_directory->name);
        free(current_directory);
        return;
    }

    /* otherwise, the list is scrolled to find the desired directory */
    Dir* previous_directory = NULL;
    while (current_directory != NULL) {
        if (strcmp(current_directory->name, name) == 0) {
            break;
        }
        previous_directory = current_directory;
        current_directory = current_directory->next;
    }

    previous_directory->next = current_directory->next;
    /* we recursively delete everything it contains the current
     * directory and we free the memory allocated for it */
    __rmdir(current_directory);
    free(current_directory->name);
    free(current_directory);
}

/* the function that changes the current directory */
void cd(Dir** target, char* name) {
    if (strcmp(name, "..") == 0) {
        /* if the argument is .. we change the current directory with parent */
        if ((*target)->parent != NULL) {
            (*target) = (*target)->parent;
            return;
        }
    } else {
        /* check if there is a file or directory with the desired name */
        if (check_exist_directory((*target), name) == 0) {
            printf("No directories found!\n");
            return;
        }

        /* the list is scrolled item by item */
        Dir* current_directory = (*target)->head_children_dirs;
        while (current_directory != NULL) {
            if (strcmp(current_directory->name, name) == 0) {
                /* change of director */
                (*target) = current_directory;
                return;
            }
            current_directory = current_directory->next;
        }
    }
}

/* the function that displays the current path */
char* pwd(Dir* target) {
    /* memory allocation for the string path */
    /* get size of the current directory */
    int size = strlen(target->name) + 1;
    char* path = malloc(sizeof(char) * (size + 1));
    DIE(path == NULL, "Allocation error");
    path[0] = '\0';

    /* memory allocation for the auxiliary string path */
    char* aux_path = malloc(sizeof(char) * (size + 1));
    DIE(aux_path == NULL, "Allocation error");
    aux_path[0] = '\0';

    /* while the current directory isn't root we 
     * add to the path the name of the current directory
     */
    while (target->parent != NULL) {
        /* we keep the current path in the auxiliary */
        /* memory reallocation */
        aux_path = realloc(aux_path, size + 1);
        strcpy(aux_path, path);

        /* memory reallocation */
        path = realloc(path, size + strlen(target->name) + 2);
        size = size + strlen(target->name) + 1;
        strcpy(path, "");
        strcat(path, "/");
        /* we add the new directory name */
        strcat(path, target->name);
        /* we concatenate the strings */
        strcat(path, aux_path);
        target = target->parent;
    }
    /* at the end we add the name of the root directory */
    /* memory reallocation */
    aux_path = realloc(aux_path, size + 1);
    strcpy(aux_path, path);
    /* memory reallocation */
    path = realloc(path, size + sizeof("/home") + 1);
    strcpy(path, "/home");
    strcat(path, aux_path);
    /* free memory for the auxiliary string path */
    free(aux_path);
    return path;
}

/* the function that frees the memory and stops the program */
void stop(Dir* target) {
    /* delete each element in the file list */
    if (target->head_children_files != NULL) {
        File* current_file = target->head_children_files;
        while (current_file != NULL) {
            File* temp_file = current_file;
            current_file = current_file->next;
            free(temp_file->name);
            temp_file->next = NULL;
            temp_file->parent = NULL;
            free(temp_file);
        }
    }

    /* delete each element in the directory list */
    if (target->head_children_dirs != NULL) {
        Dir* current_directory = target->head_children_dirs;
        while (current_directory != NULL) {
            Dir* temp_directory = current_directory;
            current_directory = current_directory->next;
            rmdir(target, temp_directory->name);
        }
    }

    /* delete root directory */
    free(target->name);
    free(target);
}

/* the function that displays elements in a tree form */
void tree(Dir* target, int level) {
    Dir* current_directory = target->head_children_dirs;
    while (current_directory != NULL) {
        /* display of directories in the desired form */
        for (int i = 0; i < level; ++i) {
            printf("    ");
        }
        printf("%s\n", current_directory->name);
        /* change level and call the function recursively */
        level++;
        tree(current_directory, level);
        --level;
        current_directory = current_directory->next;
    }
    /* display of files in the desired form */
    File* current_file = target->head_children_files;
    while (current_file != NULL) {
        for (int i = 0; i < level; ++i) {
            printf("    ");
        }
        printf("%s\n", current_file->name);
        current_file = current_file->next;
    }
}

void mv_file(Dir* parent, char* oldname, char* newname) {
    /* if the list contains only one item, we change its name */
    if (parent->head_children_files->next == NULL) {
        strcpy(parent->head_children_files->name, newname);
        return;
    }

    /* if the desired file is at the top of the list, we update
     * the header and add the modified file to the end of the file list
     */
    if (strcmp(parent->head_children_files->name, oldname) == 0) {
        File* current_file = parent->head_children_files;
        while (current_file->next != NULL) {
            current_file = current_file->next;
        }

        /* change head */
        File* temp_file = parent->head_children_files;
        parent->head_children_files = temp_file->next;
        /* change name */
        strcpy(temp_file->name, newname);
        /* add file to the end of the list */
        current_file->next = temp_file;
        temp_file->next = NULL;
        return;
    }

    /* otherwise, we go through the list and move
     * the desired file to the end of the list
     */
    File* current_file = parent->head_children_files;
    File* previous_file = NULL;
    File* desired_file = NULL;

    /* access and deletion of the desired file from the list */
    while (current_file != NULL) {
        if (strcmp(current_file->name, oldname) == 0) {
            previous_file->next = current_file->next;
            current_file->next = NULL;
            desired_file = current_file;
            break;
        }
        previous_file = current_file;
        current_file = current_file->next;
    }

    current_file = parent->head_children_files;
    while (current_file->next != NULL) {
        current_file = current_file->next;
    }
    /* change name */
    strcpy(desired_file->name, newname);
    /* add file to the end of the list */
    current_file->next = desired_file;
    desired_file->next = NULL;
}

void mv_directory(Dir* parent, char* oldname, char* newname) {
    /* if the list contains only one item, we change its name */
    if (parent->head_children_dirs->next == NULL) {
        strcpy(parent->head_children_dirs->name, newname);
        return;
    }

    /* if the desired directory is at the top of the list, we update
     * the header and add the modified directory to the end of the list
     */
    if (strcmp(parent->head_children_dirs->name, oldname) == 0) {
        Dir* current_directory = parent->head_children_dirs;
        while (current_directory->next != NULL) {
            current_directory = current_directory->next;
        }

        /* change head */
        Dir* temp_directory = parent->head_children_dirs;
        parent->head_children_dirs = temp_directory->next;
        /* change name */
        strcpy(temp_directory->name, newname);
        /* add directory to the end of the list */
        current_directory->next = temp_directory;
        temp_directory->next = NULL;
        return;
    }

    /* otherwise, we go through the list and move
     * the desired directory to the end of the list
     */
    Dir* current_directory = parent->head_children_dirs;
    Dir* previous_directory = NULL;
    Dir* temp_directory = NULL;

    /* access and deletion of the desired directory from the list */
    while (current_directory != NULL) {
        if (strcmp(current_directory->name, oldname) == 0) {
            previous_directory->next = current_directory->next;
            current_directory->next = NULL;
            temp_directory = current_directory;
            break;
        }
        previous_directory = current_directory;
        current_directory = current_directory->next;
    }

    current_directory = parent->head_children_dirs;
    while (current_directory->next != NULL) {
        current_directory = current_directory->next;
    }

    /* change name */
    strcpy(temp_directory->name, newname);
    /* add directory to the end of the list */
    current_directory->next = temp_directory;
    temp_directory->next = NULL;
}

void mv(Dir* parent, char* oldname, char* newname) {
    /* check if there is a file or directory with the oldname */
    if (check_exist(parent, oldname) == 0) {
        printf("File/Director not found\n");
        return;
    }
    /* check if there is a file or directory with the newname */
    if (check_exist(parent, newname) == 1) {
        printf("File/Director already exists\n");
        return;
    }
    /* call of the function that changes the name of the file */
    if (check_exist_file(parent, oldname) == 1) {
        mv_file(parent, oldname, newname);
    }
    /* call of the function that changes the name of the directory */
    if (check_exist_directory(parent, oldname) == 1) {
        mv_directory(parent, oldname, newname);
    }
}
