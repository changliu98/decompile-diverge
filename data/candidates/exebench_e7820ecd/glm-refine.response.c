int __cdecl read_all(int fd, unsigned __int8 *buf, int count)
{
  int n;

  do
  {
    n = read(fd, buf, count);
    
    if (n > 0)
    {
      count -= n;
      buf += n;
    }
  }
  while (n > 0 && count > 0);

  return n;
}