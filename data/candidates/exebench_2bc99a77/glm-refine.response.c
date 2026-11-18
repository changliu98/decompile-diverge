int __cdecl blkdev_get_geometry(int fd, unsigned int *h, unsigned int *s)
{
  hd_geometry geometry;

  if (ioctl(fd, HDIO_GETGEO, &geometry) != 0)
  {
    *h = 0;
    *s = 0;
    return -1;
  }
  else
  {
    *h = geometry.heads;
    *s = geometry.sectors;
    return 0;
  }
}