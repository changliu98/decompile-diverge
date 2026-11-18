int __cdecl blkdev_get_geometry(int fd, unsigned int *h, unsigned int *s)
{
  hd_geometry geometry; // [rsp+8h] [rbp-28h] BYREF
  unsigned int *sa; // [rsp+18h] [rbp-18h]
  unsigned int *ha; // [rsp+20h] [rbp-10h]
  int fda; // [rsp+28h] [rbp-8h]

  fda = fd;
  ha = h;
  sa = s;
  if ( ioctl(fd, 0x301uLL, &geometry) )
  {
    *ha = 0;
    *sa = 0;
    return -1;
  }
  else
  {
    *ha = geometry.heads;
    *sa = geometry.sectors;
    return 0;
  }
}