int blkdev_get_geometry(int fd, unsigned int *cyl, unsigned int *head) {
  struct hd_geometry geo;
  int ret;
  ret = ioctl(fd, 0x301, &geo);
  if (ret) {
    *cyl = 0;
    *head = 0;
    return -1;
  }
  *cyl = geo.cylinders;
  *head = geo.heads;
  return 0;
}