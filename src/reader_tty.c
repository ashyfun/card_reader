#include "reader_tty.h"

void reader_tty_init(const char *device)
{
    int sockfd;
    struct reader_tty_t rtty;
    struct reader_sock_t rsock = {0};

    if ((rtty.fd = open(device, O_RDWR | O_NOCTTY)) < 0) {
        perror(device);
        exit(EXIT_FAILURE);
    }

    memset(&(rtty.tty), '\0', sizeof(rtty.tty));

    reader_tty_setflags(&(rtty.tty));
    reader_tty_cc_init(&(rtty.tty));

    tcflush(rtty.fd, TCIFLUSH);
    tcsetattr(rtty.fd, TCSANOW, &(rtty.tty));

    while (1) {
        rtty.res = read(rtty.fd, rtty.buf, sizeof(rtty.buf));
        rtty.buf[rtty.res] = 0;

        if (rtty.res > 1 && strcmp(rtty.buf, "No card\n") != 0) {
            reader_sock_connect(&rsock);

            reader_sock_send(&rsock, &rtty);
            printf("Sended to %s:%d: %s", HOST, PORT, rtty.buf);
        }
    }
}

static void reader_tty_setflags(struct termios *tty)
{
    tty->c_cflag = B9600 | CRTSCTS | CS8 | CLOCAL | CREAD;
    tty->c_iflag = IGNPAR | ICRNL;
    tty->c_oflag = 0;
    tty->c_lflag = ICANON;
}

static void reader_tty_cc_init(struct termios *tty)
{
    tty->c_cc[VINTR] = 0;
    tty->c_cc[VQUIT] = 0;
    tty->c_cc[VERASE] = 0;
    tty->c_cc[VKILL] = 0;
    tty->c_cc[VEOF] = 4;
    tty->c_cc[VTIME] = 0;
    tty->c_cc[VMIN] = 1;
    tty->c_cc[VSWTC] = 0;
    tty->c_cc[VSTART] = 0;
    tty->c_cc[VSTOP] = 0;
    tty->c_cc[VSUSP] = 0;
    tty->c_cc[VEOL] = 0;
    tty->c_cc[VREPRINT] = 0;
    tty->c_cc[VDISCARD] = 0;
    tty->c_cc[VWERASE] = 0;
    tty->c_cc[VLNEXT] = 0;
    tty->c_cc[VEOL2] = 0;
}
