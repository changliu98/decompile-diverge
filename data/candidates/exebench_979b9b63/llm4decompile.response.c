int openI2CBus(int *fd, char *device) {
  *fd = open(device, 2);
  if (*fd < 0) {
    return -1;
  }
  return 0;
}