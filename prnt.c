#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Declarations of helping functions.
 */
int check(char* first, char* second, int size);
void print_file(FILE* file);


int main(int argc, char** argv)  {
    /**
     * vars:
     *      i, for loop.
     *      windows, to mark in which operating system the program runs in (0
     *       for Linux and 1 for Windows).
     *      file, a pointer to hold the file.
     *      str, a string to hold argv[0].
     *      name, a string to hold the file name.
     *      exe, to help check the operating system.
     * 
     */
    int i = 0, windows = 0;
    FILE* file;
    char* str;
    char* name;
    char* exe = ".exe";

   if(argc != 1) {
      printf("ERROR in number of arguments\n");
      exit(0);
   }

    str = argv[0];

    /* checks if file ends with .exe -> operating system is windows */
    for (i = 0; i < strlen(str); i++) {
        if (str[i] == '.' && check(&str[i], exe, strlen(exe))) {
            windows = 1;
        }
    }

    /* allocate space for file name and set it.
        handles it based on the operating system. */
    if (windows) {
        name = (char*)malloc((strlen(str)-2) * sizeof(char));
        if (!name) {/* failed to alllocate space for name */
            printf("ERROR in memory allocation\n");
            exit(0);
        }

        for (i = 0; i < strlen(str); i ++) {
            if (i == (strlen(str)-3)) {
                name[i] = 'c';
                break;
            }
            name[i] = str[i];
        }        
    } else {/* LINUX */
        name = (char*)malloc((strlen(str)+2) * sizeof(char));
        if (!name) {/* failed to alllocate space for name */
            printf("ERROR in memory allocation\n");
            exit(0);
        }

        for (i = 0; i < strlen(str); i ++) {
            name[i] = str[i];
        }
        name[strlen(str)] = '.';
        name[strlen(str)+1] = 'c';
    }
    
    file = fopen(name, "r");
    if (!file) {/* failed to open file */
        printf("name is: %s\n", name);
        perror("ERROR in opening file\n");
        free(name);
        exit(0);
    }

    print_file(file);

    fclose(file);
    free(name);
    return 0;
}

/**
 * @brief: checks if the 2 strings are the same for the part of size length.
 * 
 * @param first - first string.
 * @param second - second string.
 * @param size - size of the shorter string.
 *
 * @return: 1, if strings are the same.
 *          2, if are different.
 */
int check(char* first, char* second, int size) {
    int i = 0;
    for (i = 0; i < size; i++) {
        if (first[i] != second[i]) {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief: prints the entire content of the file.
 * 
 * @param file - pointer to file. 
 */
void print_file(FILE* file) {
    char c;
    while(1) {
        c = fgetc(file);
        if (feof(file)) {
            break;
        }
        putchar(c);
    }
    putchar('\n');/* making sure that doesn't overlap */
}
