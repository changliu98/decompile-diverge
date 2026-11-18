ssize_t __cdecl read_data(int fd, void *buf, size_t buf_len)
{
  ssize_t bytes_read;   // Number of bytes read in the current iteration
  size_t remaining;     // Number of bytes left to read

  if (fd < 0)
    return -1;

  for (remaining = buf_len; remaining; remaining -= bytes_read)
  {
    bytes_read = read(fd, buf, remaining);
    
    // If read() fails (returns -1) or hits EOF prematurely (returns 0)
    if (bytes_read <= 0)
      return -1;
      
    // Advance the buffer pointer by the number of bytes just read
    buf = (void *)((unsigned char *)buf + bytes_read);
  }
  
  return buf_len;
}