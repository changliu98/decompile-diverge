int read_double(int fd,double *out)

{
  ssize_t sVar1;
  int err;
  double d;
  double *out_local;
  int fd_local;
  
  out_local = out;
  fd_local = fd;
  sVar1 = read(fd,&d,8);
  *out_local = d;
  return (int)sVar1;
}