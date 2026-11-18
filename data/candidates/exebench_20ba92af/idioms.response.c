int blkdev_get_start(int fd, unsigned int *start)
{
  struct hd_geometry geometry;
  if (ioctl(fd, 0x00301, &geometry))
  {
    *start = 0;
    return -1;
  }
  else
  {
    *start = geometry.start;
    return 0;
  }
}