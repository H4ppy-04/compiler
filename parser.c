#include "parser.h"

#include "compiler.h"

int
check_argc_gt_2(int* argc, char*** argv)
{
        if (*argc < 2) {
                fprintf(stderr, "Usage: %s <filename>\n", *argv[0]);
                (void)fflush(stdin);
                return 1;
        }
        return 0;
}

int
check_source_file(char** argv)
{
        const char file = *argv[1];
        if (file_exists(&file) != 1) {
                err("Failed to open file: %s\n", file);
                return 1;
        }
        return 0;
}
