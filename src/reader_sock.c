#include "reader_sock.h"

void reader_sock_new(struct reader_sock_t *rsock)
{
    rsock->opt = 1;
    rsock->addrlen = sizeof(rsock->addr);

    if ((rsock->sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket()");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(rsock->sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &rsock->opt, sizeof(rsock->opt))) {
        perror("Setsockopt()");
        exit(EXIT_FAILURE);
    }

    (rsock->addr).sin_family = AF_INET;
    (rsock->addr).sin_addr.s_addr = INADDR_ANY;
    (rsock->addr).sin_port = htons(PORT);

    if (bind(rsock->sockfd, (struct sockaddr *) &(rsock->addr), sizeof(rsock->addr)) < 0) {
        perror("Bind()");
        exit(EXIT_FAILURE);
    }

    if (listen(rsock->sockfd, 3) < 0) {
        perror("Listen()");
        exit(EXIT_FAILURE);
    }
}

void reader_sock_accept(struct reader_sock_t *rsock)
{
    if (rsock->newsock == 0 && (rsock->newsock = accept(rsock->sockfd, (struct sockaddr *) &(rsock->addr), (socklen_t *) &(rsock->addrlen))) < 0) {
        perror("Accept()");
        exit(EXIT_FAILURE);
    }
}

void reader_sock_send(int *newsock, const char *msg, int *size)
{
    send(*newsock, msg, *size, 0);
}
