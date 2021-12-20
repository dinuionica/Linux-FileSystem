/* Copyright 2021 Dinu Ion-Irinel */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define NAME_SIZE_ROOT 5
#define MAX_INPUT_LINE_SIZE 300
#define PATH_SIZE 100

struct Dir;
struct File;

/* struct of a directory */
typedef struct Dir {
    char* name;
    struct Dir* parent;
    struct File* head_children_files;
    struct Dir* head_children_dirs;
    struct Dir* next;
} Dir;

/* struct of a file */
typedef struct File {
    char* name;
    struct Dir* parent;
    struct File* next;
} File;

Dir* create_root();

int check_exist_directory(Dir* parent, char* name);

int check_exist_file(Dir* parent, char* name);

int check_exist(Dir* parent, char* name);

void touch(Dir* parent, char* name);

void mkdir(Dir* parent, char* name);

void ls(Dir* parent);

void rm(Dir* parent, char* name);

void __rmdir(Dir* parent);

void rmdir(Dir* parent, char* name);

void cd(Dir** target, char* name);

char* pwd(Dir* target);

void tree(Dir* target, int level);

void mv(Dir* parent, char* oldname, char* newname);

void stop(Dir* target);

#endif /* FUNCTIONS_H_ */
