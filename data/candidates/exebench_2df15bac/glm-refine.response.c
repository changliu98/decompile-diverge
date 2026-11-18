signature

int force_write(int fd, unsigned char *buf, int sz)
{
  int bytes_written;
  int total_written = 0;

  while (sz > 0)
  {
    bytes_written = write(fd, buf, sz);
    
    // write() returns -1 on error, or 0 on EOF. Break on either.
    if (bytes_written <= 0)
      break;

    total_written += bytes_written;
    buf += bytes_written;
    sz -= bytes_written;
  }
  
  return total_written;
}