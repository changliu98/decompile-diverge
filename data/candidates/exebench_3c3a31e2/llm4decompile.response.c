int wfaCtrlRecv(int sock, unsigned char *buf, int size)
{
    int bytesRecvd;

    bytesRecvd = recv(sock, buf, 1024 -1, 0);
    return bytesRecvd;
}