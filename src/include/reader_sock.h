#ifndef READER_SOCK_H
#define READER_SOCK_H

#include "reader_tty.h"
#include "reader_card.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define HOST "127.0.0.1"
#define PORT 9000

struct reader_tty_t;
struct reader_sock_t {
    struct sockaddr_in addr;
    int sockfd, newsock, opt, addrlen;
};

void reader_sock_connect(struct reader_sock_t *rsock);
void reader_sock_send(struct reader_sock_t *rsock, struct reader_tty_t *rtty);

#endif
