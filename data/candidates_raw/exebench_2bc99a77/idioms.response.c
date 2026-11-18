int get_hd_geometry(int fd, unsigned int *heads, unsigned int *sectors)
{
  struct hd_geometry geometry;
  if (ioctl(fd, 0x00301, &geometry)) {
    *heads = 0;
    *sectors = 0;
    return -1;
  }
  *heads = geometry.heads;
  *sectors = geometry.sectors;
  return 0;
}