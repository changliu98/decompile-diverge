int wfaCtrlRecv(int sock, unsigned char *buf)
{
    int bytesRecvd = 0;

    bytesRecvd = recv(sock, buf, 1024 -1, 0);

    return bytesRecvd;
}