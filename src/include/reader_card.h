#ifndef READER_CARD_H
#define READER_CARD_H

#include "reader_tty.h"

#include <string.h>

struct reader_tty_t;

char *reader_card_extract(const struct reader_tty_t *rtty);

#endif
