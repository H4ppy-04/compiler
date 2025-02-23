/* See LICENSE file for copyright and license details. */

#include "compiler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Token
new_token(TokenType* type, void* data)
{
        Token token = {.type = type, .data = data};
        return token;
}

int
file_exists(const char* path)
{
        if (path == NULL) {
                return 0;
        }

        FILE* fd = fopen(path, "r");
        if (fd != NULL) {
                (void)fclose(fd);
                return 1;
        }

        return 0;
}

void
err(const char* msg, ...)
{
        if (msg == NULL) {
                return;
        }
        va_list args;
        fprintf(stderr, "ERROR: ");
        va_start(args, msg);
        (void)vfprintf(stderr, msg, args);
        va_end(args);
        fprintf(stderr, "\n");
        (void)fflush(stderr);
}

void
read_file(char* path, char* restrict contents)
{
        FILE* fd = NULL;
        char* retval = NULL;
        if (file_exists(path) == 1) {
                fd = fopen(path, "r");
                if (fd != NULL) {
                        retval = (char*)fgets(contents,
                                              (int)sizeof(contents) + 1, fd);
                        retval =
                            (void*)retval; /* retval is quite literally useless
                                              but fgets must return a value for
                                              this to pass linting */
                }
        } else {
                err("File does not exist");
        }
        if (fd != NULL) {
                (void)fclose(fd);
        }
}
