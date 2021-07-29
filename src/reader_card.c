#include "reader_card.h"

char *reader_card_extract(const struct reader_tty_t *rtty)
{
    int start = 0, end = 0;
    for (int i = 0; i < rtty->res; ++i) {
        if ((rtty->buf)[i] == '[') {
            start = i + 1;
        }

        if ((rtty->buf)[i] == ']') {
            end = i;
            break;
        }
    }

    const int cardlen = end - start;
    char *card = malloc(cardlen);
    strncpy(card, rtty->buf + start, end - start);
    card[cardlen] = 0;

    return card;
}
