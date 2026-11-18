int blkdev_get_geometry(int fd, unsigned int *heads, unsigned int *sectors)
{
 struct hd_geometry geom;
 int ret;

 if (!ioctl(fd, (0x0301), &geom)) {
  *heads = geom.heads;
  *sectors = geom.sectors;
  ret = 0;
 } else {
  *heads = 0;
  *sectors = 0;
  ret = -1;
 }

 return ret;
}