int i2c_multiple_writes(int fd,int num,uchar *Ptr_buff)

{
  ssize_t sVar1;
  int ret;
  uchar *Ptr_buff_local;
  int num_local;
  int fd_local;
  undefined4 local_c;
  
  sVar1 = write(fd,Ptr_buff,(long)num);
  local_c = (int)sVar1;
  if ((local_c == -1) || (local_c != num)) {
    local_c = -1;
  }
  return local_c;
}