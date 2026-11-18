int __cdecl read_data(int fd, unsigned __int8 *buf, int size)
{
  int bytes_read;
  int total_bytes = 0;

  while (total_bytes != size)
  {
    bytes_read = read(fd, &buf[total_bytes], size - total_bytes);
    if (bytes_read <= 0)
      return -1;

    total_bytes += bytes_read;
  }

  return 0;
}