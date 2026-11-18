int Serial_WriteData(int fd, unsigned char *data, int size) {
  int n;
  n = write(fd, data, size);
  return n;
}