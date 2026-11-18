For HDIO_GETGEO and hd_geometry

int __cdecl blkdev_get_start(int fd, unsigned int *s)
{
  hd_geometry geometry;

  // 0x301 is HDIO_GETGEO: get disk geometry
  if (ioctl(fd, HDIO_GETGEO, &geometry) != 0)
  {
    *s = 0;
    return -1;
  }

  *s = geometry.start;
  return 0;
}