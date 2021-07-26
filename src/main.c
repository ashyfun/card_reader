#include "reader_tty.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Too few arguments\n");
        exit(EXIT_FAILURE);
    }

    reader_tty_init(argv[1]);

    return 0;
}
