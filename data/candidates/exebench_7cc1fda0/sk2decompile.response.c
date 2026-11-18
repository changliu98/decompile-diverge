static int write_buff(int fd, unsigned char *buff, long len) {
  long left, written;
  left = len;
  while (left > 0) {
    written = write(fd, buff, left);
    if (written < 0) return -1;
    left -= written;
    buff += written;
  }
  return len;
}