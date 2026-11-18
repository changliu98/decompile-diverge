int connectToServer(int *sockfd, const char *ip, unsigned short port) {
    struct sockaddr_in addr;

    *sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (*sockfd == -1) {
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip);
    addr.sin_port = htons(port);

    if (connect(*sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        close(*sockfd);
        return -1;
    }

    return 0;
}