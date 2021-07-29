#include "reader_sock.h"

void reader_sock_connect(struct reader_sock_t *rsock)
{
    close(rsock->newsock);
    memset(rsock, 0, sizeof(*rsock));

    rsock->opt = 1;
    rsock->addrlen = sizeof(rsock->addr);

    if ((rsock->sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket()");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(rsock->sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &rsock->opt, sizeof(rsock->opt))) {
        perror("Setsockopt()");
        exit(EXIT_FAILURE);
    }

    (rsock->addr).sin_family = AF_INET;
    (rsock->addr).sin_addr.s_addr = inet_addr(HOST);
    (rsock->addr).sin_port = htons(PORT);

    if (connect(rsock->sockfd, (struct sockaddr *) &(rsock->addr), sizeof(rsock->addr)) < 0) {
        perror("Connect()");
        exit(EXIT_FAILURE);
    }
}

void reader_sock_send(struct reader_sock_t *rsock, struct reader_tty_t *rtty)
{
    char *card = reader_card_extract(rtty);

    if (send(rsock->newsock, card, strlen(card), 0) < 0) {
        perror("Send()");
        exit(EXIT_FAILURE);
    }

    free(card);
}
