#ifndef READER_TTY_H
#define READER_TTY_H

#include "reader_sock.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <memory.h>

struct reader_tty_t {
    int fd, res;
    struct termios tty;
    char buf[255];
};

void reader_tty_init(const char *device);

static void reader_tty_setflags(struct termios *tty);
static void reader_tty_cc_init(struct termios *tty);

#endif
