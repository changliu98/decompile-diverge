int __cdecl sendcw(int fd, unsigned __int8 *buff)
{
  int *v2; // rax

  if ( send(fd, buff, 0x12uLL, 0) != -1 )
    return 1;
  v2 = __errno_location();
  syslog(3, "ca.so: Send cw failed %d", (unsigned int)*v2);
  return 0;
}