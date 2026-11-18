int wfaTrafficRecv(int sock, char *buf, int bufLen)
{
    return recv(sock, buf, bufLen, 0);
}