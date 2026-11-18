int i2c_multiple_writes(int fd, int num, unsigned char *Ptr_buff)
{
 int ret = 0;
 ret = write(fd, Ptr_buff, num);
 if((ret == -1) || (ret != num))
  return -1;
 else
  return(ret);
}