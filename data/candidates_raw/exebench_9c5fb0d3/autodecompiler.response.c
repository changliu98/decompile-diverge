int write_all(int fd, char *buffer, int bytes)
{
    int n;
    int sofar = 0;
    while (1) {
 if (sofar == bytes) return 0;
 n = write(fd, buffer + sofar, bytes - sofar);
 if (n <= 0) return -1;
 sofar += n;
    }
}