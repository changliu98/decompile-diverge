int __cdecl i2c_multiple_writes(int fd, int num, unsigned __int8 *Ptr_buff)
{
  int ret; // [rsp+4h] [rbp-1Ch]

  ret = write(fd, Ptr_buff, num);
  if ( ret != -1 && ret == num )
    return ret;
  else
    return -1;
}