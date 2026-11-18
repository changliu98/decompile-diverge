int blkdev_get_start(int fd,uint *s)

{
  int iVar1;
  hd_geometry geometry;
  uint *s_local;
  int fd_local;
  int local_c;
  
  iVar1 = ioctl(fd,0x301,&geometry);
  if (iVar1 == 0) {
    *s = (uint)geometry.start;
    local_c = 0;
  }
  else {
    *s = 0;
    local_c = -1;
  }
  return local_c;
}