int wfaCtrlRecv(int socket_fd, uchar *buffer)
{
    return recv(socket_fd, buffer, 0x3ff, 0);
}