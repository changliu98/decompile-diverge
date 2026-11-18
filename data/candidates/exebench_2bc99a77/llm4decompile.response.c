int blkdev_get_geometry(int fd, unsigned int *heads, unsigned int *sectors)
{
 int ret;
 hd_geometry geometry;

 ret = ioctl(fd, 0x0301, &geometry);
 if (ret) {
  *heads = 0;
  *sectors = 0;
  return -1;
 }

 *heads = geometry.heads;
 *sectors = geometry.sectors;

 return 0;
}