int write_sock(int sockhandle, unsigned char *buf, int length)
{
    int bytes_written = write(sockhandle, buf, (size_t)length);
    return length - bytes_written;
}