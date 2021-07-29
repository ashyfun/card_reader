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

    reader_card_reverse(card, &cardlen);

    return card;
}

void reader_card_reverse(char *card, const int *len)
{
    char copy[*len];
    strcpy(copy, card);

    for (int i = *len - 1, j = 0; i >= 0; --i, ++j) {
        if (j % 2 == 0) {
            card[j] = copy[i - 1];
        }
        else {
            card[j] = copy[i + 1];
        }
    }
}
