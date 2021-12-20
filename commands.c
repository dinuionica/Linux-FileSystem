/* Copyright 2021 Dinu Ion-Irinel */

#include "commands.h"

/* the function that divides a command into arguments */
char* split_command(char* command) {
    char* argument = command;
    if (argument != NULL) {
        argument = strtok(NULL, " ");
    }
    return argument;
}

/* the function that parses the commands received as input */
void parsing_commands(Dir* root, Dir* current_directory, char* input) {
    while (fgets(input, MAX_INPUT_LINE_SIZE, stdin)) {
        /* check if the last character is '\n' */
        if (input[strlen(input) - 1] == '\n') {
            input[strlen(input) - 1] = '\0';
        }
        /* parsing commands */
        char* command = strtok(input, " ");

        if (strcmp(command, "touch") == 0) {
            char* argument = split_command(command);
            touch(current_directory, argument);
        }

        if (strcmp(command, "mkdir") == 0) {
            char* argument = split_command(command);
            mkdir(current_directory, argument);
        }

        if (strcmp(command, "ls") == 0) {
            ls(current_directory);
        }

        if (strcmp(command, "rm") == 0) {
            char* argument = split_command(command);
            rm(current_directory, argument);
        }

        if (strcmp(command, "rmdir") == 0) {
            char* argument = split_command(command);
            rmdir(current_directory, argument);
        }

        if (strcmp(command, "cd") == 0) {
            char* argument = split_command(command);
            cd(&current_directory, argument);
        }

        if (strcmp(command, "pwd") == 0) {
            char* path = pwd(current_directory);
            printf("%s\n", path);
            free(path);
        }

        if (strcmp(command, "tree") == 0) {
            tree(current_directory, 0);
        }

        if (strcmp(command, "mv") == 0) {
            char* argument = split_command(command);
            char* second_argument = split_command(argument);
            mv(current_directory, argument, second_argument);
        }

        if (strcmp(command, "stop") == 0) {
            free(input);
            stop(root);
            break;
        }
    }
}
