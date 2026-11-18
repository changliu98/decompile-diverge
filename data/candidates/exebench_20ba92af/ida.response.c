int __cdecl blkdev_get_start(int fd, unsigned int *s)
{
  hd_geometry geometry; // [rsp+0h] [rbp-20h] BYREF
  unsigned int *sa; // [rsp+10h] [rbp-10h]
  int fda; // [rsp+18h] [rbp-8h]

  fda = fd;
  sa = s;
  if ( ioctl(fd, 0x301uLL, &geometry) )
  {
    *sa = 0;
    return -1;
  }
  else
  {
    *sa = geometry.start;
    return 0;
  }
}