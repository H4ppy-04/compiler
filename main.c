#include "parser.h"

int
main(int argc, char** argv)
{
        if (check_argc_gt_2(&argc, &argv) == 1) {
                return 1;
        }

        if (check_source_file(argv) == 1) {
                return 1;
        }

        return 0;
}
