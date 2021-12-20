/* Copyright 2021 Dinu Ion-Irinel */

#include "commands.h"
#include "functions.h"

int main(void) {
    /* memory allocation for the input */
    char* input = malloc(sizeof(char) * MAX_INPUT_LINE_SIZE);
    DIE(input == NULL, "Allocation error");

    /* create directory home */
    Dir* root_directory = create_root();

    /* create current directory */
    Dir* current_directory = root_directory;

    /* parsing commands */
    parsing_commands(root_directory, current_directory, input);

    return 0;
}
