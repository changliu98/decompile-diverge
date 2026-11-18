int __cdecl write_buff(int fd, unsigned __int8 *data, ssize_t size)
{
  ssize_t remaining = size;
  ssize_t written;

  while (remaining > 0)
  {
    written = write(fd, data, remaining);
    if (written < 0)
      return -1;
    
    remaining -= written;
    data += written;
  }
  
  return size;
}