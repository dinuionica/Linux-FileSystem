# Linux File System 
------------------------

## Implementation:

To solve the topic we simulated a series of specific operations
a simple linked list to implement the file system
linux. Also, for a good modularization of the code the functions
are divided in multiple header files.


main-> In this function I have allocated memory for
input, I created the root and the current directory and called
command parsing function.


## FUNCTIONS.C:

create_root-> In this function I have allocated memory
for the structure, I assigned and created the name and redirected
pointers to NULL.

check_exist_directory-> In this function I went through the list
directories and we checked to see if there was a directory named
desired. If so, I returned true.

check_exist_file-> Similarly I went through the list of files
and I checked to see if there was already a file with the same name.

check_exist-> In this function I used the functions
implemented above to check if there is a directory
or a file with the desired name in the current directory.

touch-> In this function, we checked if it already exists
a file with the same name. If not, I allocated and created the structure
a file. Then I handled the case where the list of files is
empty, and if I did not go through the list to the end, and I added
the new file in the last position.

mkdir-> I did similar to the touch function, only the reasoning
was applied to the directory list.

ls-> In this function, I went through the list of subdirectories
and I displayed each directory and then went through the list
files and I also displayed each file.

rm-> In this function I checked if it already exists
a file with the same name in the current directory. Then I checked
if the file to be deleted is the head of the list, in which case I have
I deleted the file and I updated the head. In case of contract I went through
list and I searched for the desired item. If I found it I realized
the link between the previous and the next file, then I deleted
the current file, freeing up the allocated memory.

__rmdir-> In this function I went through each deputy director
from the current directory, and I called the recursive function for
each of them to delete the contents, then I deleted
the deputy director. In the end, I deleted every file that was there
in the current directory.

rmdir-> First we checked to see if there was a directory named
which we want to delete. If the directory is the head of the list,
I updated the head, I recursively deleted the content and then I deleted
and the director. Otherwise I went through the list of deputy directors and I
searched for the directory with the desired name. Similarly, I deleted the content and
then the director himself.

cd-> In this function we checked if the argument was transmitted
as parameter is "..", in which case I changed the current directory
with his father. Otherwise, I went through the list of deputy directors, I have
found the directory with the desired name and changed the current directory
with the director found.

pwd-> I used two strings to perform this function
in which I kept the name of the director. Starting from the end, I have
I went through the parent directories until I got to the root. Each
date, we reallocate the memory for the strings, we add in the auxiliary the string from the path,
then we add the name of the current directory, and at the end we add in the path what
which has just been added to the auxiliary string. When I got to the directory
root, I reallocated the memory, I added its name to the path, and I
released the memory allocated for the auxiliary string used.

stop-> In this function I went through the whole file list,
and I deleted each file, then similarly I deleted each
director. Finally I deleted the root directory.

tree-> We performed a recursive implementation of the function. I went through
the list of deputy directors and for each of them, I called
function recursively based on a level, to display its contents.
At the end I also displayed each file contained.

mv_file-> For starters, if there is only one file in the directory
current, I updated its name and turned off the function. Similarly
functions above, we have treated the case that needs to be modified
header file name, I updated the header and added the file
at the end of the lists. If not, I went through the file list, I updated
the position of the desired file, I changed its name and
I added it at the end.

mv_directory-> I did similarly to the mv_file function, only that
the reasoning was applied to the directors.

mv-> In this function, we checked if the file / directory exists
whose name we want to change or if there is already a directory
with the new desired name. Then depending on the existence of a file or directory,
I called the implemented functions: mv_file or mv_directory.

## COMMANDS.C:

split_commands-> In this I split the command string
transmitted as a parameter to get the necessary arguments
touch, mkdir, mv etc. functions.

parsing_commands-> In this function I read the input
from the keyboard, I determined the command and the necessary arguments and
I called the appropriate functions.

I used the DIE  macro for memory allocation errors
taken from the header utils.h
