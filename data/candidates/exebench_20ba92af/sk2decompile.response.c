int blkdev_get_start(int fd, unsigned int *start) {
  struct floppy_raw_cmd raw_cmd;
  int ret;
  ret = ioctl(fd, 0x301, &raw_cmd);
  if (ret) {
    *start = 0;
    return -1;
  }
  *start = raw_cmd.track;
  return 0;
}