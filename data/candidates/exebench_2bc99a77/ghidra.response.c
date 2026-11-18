int blkdev_get_geometry(int fd,uint *h,uint *s)

{
  int iVar1;
  hd_geometry geometry;
  uint *s_local;
  uint *h_local;
  int fd_local;
  int local_c;
  
  iVar1 = ioctl(fd,0x301,&geometry);
  if (iVar1 == 0) {
    *h = (uint)geometry.heads;
    *s = (uint)geometry.sectors;
    local_c = 0;
  }
  else {
    *h = 0;
    *s = 0;
    local_c = -1;
  }
  return local_c;
}