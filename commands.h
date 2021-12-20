/* Copyright 2021 Dinu Ion-Irinel */

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include "functions.h"

char *split_command(char *command);

void parsing_commands(Dir *root_directory, Dir *current_directory, char *input);

#endif /* COMMANDS_H_ */
