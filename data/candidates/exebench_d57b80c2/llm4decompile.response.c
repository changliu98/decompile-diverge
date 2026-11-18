int i2c_multiple_writes(int fd, int num, unsigned char* buff)
{
 int ret = write(fd, buff, num);
 if(ret == -1 || ret != num)
  return -1;
 return ret;
}