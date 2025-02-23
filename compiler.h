/* See LICENSE file for copyright and license details. */

#ifndef H_COMP__
#define H_COMP__

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
        char** path;
        char** contents;
} File;

typedef struct Token Token;
typedef enum {
        INT_LITERAL,
} TokenType;

struct Token {
        TokenType* type;
        void* data;
};

Token new_token(TokenType* type, void* data);

/* Determine if a file exists.
 *
 * Attempts to open a file in read mode. Does not attempt to read contents of
 * file.
 *
 * path - file path can be absolute or relative to executable.
 */
int file_exists(const char* path);

/* Print out an error message.
 *
 * 'Throw' an error, with an any optional number of arguments.
 *
 * msg - primary error message.
 */
void err(const char* msg, ...);

/* Read file to string.
 *
 * path - the path to read to.
 */
void read_file(char* path, char* contents);

#endif  // !H_COMP__
