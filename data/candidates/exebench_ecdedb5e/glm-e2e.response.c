int read_double(int fd, double *out) {
    double temp;
    int bytes_read = read(fd, &temp, 8);
    *out = temp;
    return bytes_read;
}