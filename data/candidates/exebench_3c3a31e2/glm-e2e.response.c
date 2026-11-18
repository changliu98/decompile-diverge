int wfaCtrlRecv(int sockfd, void *buf) {
    int bytes_received = 0;
    bytes_received = recv(sockfd, buf, 1023, 0);
    return bytes_received;
}