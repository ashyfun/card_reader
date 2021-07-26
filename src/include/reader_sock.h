#ifndef READER_SOCK_H
#define READER_SOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

#define PORT 9000

struct reader_sock_t {
    struct sockaddr_in addr;
    int sockfd, newsock, opt, addrlen;
};

void reader_sock_new(struct reader_sock_t *rsock);
void reader_sock_accept(struct reader_sock_t *rsock);
void reader_sock_send(int *newsock, const char *msg, int *size);

#endif
