int __cdecl sendline(int fd, const void *buf, size_t len)
{
  write(fd, buf, len);
  return len;
}