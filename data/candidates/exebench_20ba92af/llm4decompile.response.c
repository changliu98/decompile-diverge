int blkdev_get_start(int fd, unsigned *start)
{
 hd_geometry geometry;
 int ret;

 ret = ioctl(fd, 0x0301, &geometry);

 if (ret) {
  *start = 0;
  return -1;
 }

 *start = geometry.start;

 return 0;
}